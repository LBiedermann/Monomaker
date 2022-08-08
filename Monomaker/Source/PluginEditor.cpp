/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
MonomakerAudioProcessorEditor::MonomakerAudioProcessorEditor (MonomakerAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p),
    verticalGradientMeterM([&]() {return audioProcessor.getMidSide().getRMSLevelMid(); }),
    verticalGradientMeterS([&]() {return audioProcessor.getMidSide().getRMSLevelSide(); })
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.

    setSize (420, 420);
    bgImage = ImageCache::getFromMemory(BinaryData::background_png, BinaryData::background_pngSize);
    grill = ImageCache::getFromMemory(BinaryData::raster_png, BinaryData::raster_pngSize);

    addAndMakeVisible(verticalGradientMeterM);
    addAndMakeVisible(verticalGradientMeterS);

    addAndMakeVisible(midMute);
    midMute.setButtonText("Mid");
    midMute.setClickingTogglesState(true);
    midMute.setColour(juce::TextButton::ColourIds::buttonOnColourId, juce::Colours::red);
    //midMute.setColour(juce::TextButton::ColourIds::textColourOffId, juce::Colours::dimgrey);
    audioProcessor.getMidSide().setMidState(&midMute);
    midMuteAttachment = std::make_unique<AudioProcessorValueTreeState::ButtonAttachment>(audioProcessor.apvts, "MM", midMute);

    addAndMakeVisible(sideMute);
    sideMute.setButtonText("Side");
    sideMute.setClickingTogglesState(true);
    sideMute.setColour(juce::TextButton::ColourIds::buttonOnColourId, juce::Colours::red);
    //sideMute.setColour(juce::TextButton::ColourIds::textColourOffId, juce::Colours::dimgrey);
    audioProcessor.getMidSide().setSideState(&sideMute);
    sideMuteAttachment = std::make_unique<AudioProcessorValueTreeState::ButtonAttachment>(audioProcessor.apvts, "SM", sideMute);


    addRotaries();
}

MonomakerAudioProcessorEditor::~MonomakerAudioProcessorEditor()
{
}

//==============================================================================
void MonomakerAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.drawImage(bgImage, getLocalBounds().toFloat());
}
void MonomakerAudioProcessorEditor::paintOverChildren(juce::Graphics& g)
{
    g.drawImageAt(grill, 0, 0);
}
void MonomakerAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..

    verticalGradientMeterM.setBounds(281, 60, 30, 300);
    verticalGradientMeterS.setBounds(331, 60, 30, 300);

    midMute.setBounds(276, 30, 40, 20);
    sideMute.setBounds(326, 30, 40, 20);

}
//


void MonomakerAudioProcessorEditor::addRotaries() {
    //Hpf Slider
    hpfSlider = std::make_unique<Slider>(Slider::SliderStyle::RotaryHorizontalVerticalDrag, Slider::NoTextBox);
    hpfSlider->setBounds(42, 50.4, 243, 214);
    hpfSlider->setLookAndFeel(&largeKnob);
    addAndMakeVisible(hpfSlider.get());
    hpfAttachment = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts, "HPF", *hpfSlider);


    //StereoWidth Slider
    stereoWidthSlider = std::make_unique<Slider>(Slider::SliderStyle::RotaryHorizontalVerticalDrag, Slider::NoTextBox );
    stereoWidthSlider->setBounds(63, 243.6, 189, 155);
    stereoWidthSlider->setLookAndFeel(&smallKnob); 
    addAndMakeVisible(stereoWidthSlider.get());
    stereoWidthAttachment = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts, "STE", *stereoWidthSlider);
}