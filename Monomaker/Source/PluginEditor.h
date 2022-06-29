/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "Components/LargeKnob.h"
#include "Components/SmallKnob.h"

//==============================================================================
/**
*/
class MonomakerAudioProcessorEditor  : public juce::AudioProcessorEditor, Slider::Listener
{
public:
    MonomakerAudioProcessorEditor (MonomakerAudioProcessor&);
    ~MonomakerAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;
    void sliderValueChanged(Slider* slider) override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    MonomakerAudioProcessor& audioProcessor;

    Image bgImage;

    Slider knob1, knob2;
    //Classes for LookAndFeel
    LargeKnob largeKnob;
    SmallKnob smallKnob;

    LookAndFeel_V4 lookAndFeelV3;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MonomakerAudioProcessorEditor)
};
