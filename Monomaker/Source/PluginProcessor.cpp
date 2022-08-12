/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
MonomakerAudioProcessor::MonomakerAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                       ), apvts(*this, nullptr, "Parameters", createParameters())
#endif
{
    apvts.state.addListener(this);
}

MonomakerAudioProcessor::~MonomakerAudioProcessor()
{
    apvts.state.removeListener(this);
}

//==============================================================================
const juce::String MonomakerAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool MonomakerAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool MonomakerAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool MonomakerAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double MonomakerAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int MonomakerAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int MonomakerAudioProcessor::getCurrentProgram()
{
    return 0;
}

void MonomakerAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String MonomakerAudioProcessor::getProgramName (int index)
{
    return {};
}

void MonomakerAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void MonomakerAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
    

    midSide.setSamplerate(sampleRate);
    updateParameters();
    reset();
    isActive = true;
}

void MonomakerAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool MonomakerAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    // Some plugin hosts, such as certain GarageBand versions, will only
    // load plugins that support stereo bus layouts.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void MonomakerAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    if (!isActive)
        return;
    if (mustUpdateProcessing) {
        mustUpdateProcessing = false;
        updateParameters();
    }

    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();


    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

    
    midSide.processStereoWidth(buffer);

}

//==============================================================================
bool MonomakerAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* MonomakerAudioProcessor::createEditor()
{
    return new MonomakerAudioProcessorEditor (*this);
    //return new juce::GenericAudioProcessorEditor(*this);
}

//==============================================================================
void MonomakerAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.

    //ValueTree copyState = apvts.copyState();
    //std::unique_ptr<XmlElement> xml = copyState.createXml();
    //copyXmlToBinary(*xml.get(), destData);

    juce::MemoryOutputStream mos(destData, true);
    apvts.state.writeToStream(mos);
}

void MonomakerAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.

    //std::unique_ptr<XmlElement> xml = getXmlFromBinary(data,
    //    sizeInBytes);
    //ValueTree copyState = ValueTree::fromXml(*xml.get());
    //apvts.replaceState(copyState);

    auto tree = juce::ValueTree::readFromData(data, sizeInBytes);

    if (tree.isValid())
    {
        apvts.replaceState(tree);
        updateParameters();
    }
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new MonomakerAudioProcessor();
}
//-------------------------------------------------------------------------------
void MonomakerAudioProcessor::userChangedParameter()
{
    mustUpdateProcessing = true;
}
juce::AudioProcessorValueTreeState::ParameterLayout
MonomakerAudioProcessor::createParameters()
{
    std::vector<std::unique_ptr<juce::RangedAudioParameter>> parameters;
    // Create your parameters
    //float value returns as a string w a mx length of 4 characters
    std::function<juce::String(float, int)> valueToTextFunction = [](float x, int l) { return juce::String(x, 2); };

    //value to text function
    std::function<float(const juce::String&)> textToValueFunction = [](const juce::String& str) {return str.getFloatValue(); };


    parameters.push_back(std::make_unique<juce::AudioParameterFloat >("HPF",
        "Monomaker",
        juce::NormalisableRange<float>(20.0f, 20000.0f, 1.0f, 0.3f),
        20.f, "Hz",
        juce::AudioProcessorParameter::genericParameter,
        valueToTextFunction, textToValueFunction));

    parameters.push_back(std::make_unique<juce::AudioParameterFloat >("STE", 
        "StereoWidth", 
        juce::NormalisableRange<float>(0.f, 2.f), 
        1.f, "", 
        juce::AudioProcessorParameter::genericParameter, 
        valueToTextFunction, textToValueFunction));

    parameters.push_back(std::make_unique<juce::AudioParameterBool>("MM", "MidMute", false));
    parameters.push_back(std::make_unique<juce::AudioParameterBool>("SM", "SideMute", false));
    return { parameters.begin(), parameters.end() };
}

void MonomakerAudioProcessor::updateParameters()
{
   
    midSide.setStereowidthValue(apvts.getRawParameterValue("STE"));
    midSide.updateCutFilter(apvts.getRawParameterValue("HPF"));
    bool midBtn = *apvts.getRawParameterValue("MM");
    bool sideBtn = *apvts.getRawParameterValue("SM");

    midSide.setMidState(midBtn);
    midSide.setSideState(sideBtn);

}
void MonomakerAudioProcessor::reset() {
    midSide.reset();
}