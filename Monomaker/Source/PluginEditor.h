/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "Components/VerticalGradientMeter.h"

//==============================================================================
/**
*/
class MonomakerAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    MonomakerAudioProcessorEditor (MonomakerAudioProcessor&);
    ~MonomakerAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;
    void addRotaries();


private:

    MonomakerAudioProcessor& audioProcessor;

    Image bgImage;

    //Slider knob1, knob2;
    //Classes for LookAndFeel
    //LargeKnob largeKnob;
    //SmallKnob smallKnob;

    std::unique_ptr<Slider> stereoWidthSlider, hpfSlider;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> stereoWidthAttachment, hpfAttachment;
    
    Gui::VerticalGradientMeter verticalGradientMeterM, verticalGradientMeterS;


    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MonomakerAudioProcessorEditor)
};
