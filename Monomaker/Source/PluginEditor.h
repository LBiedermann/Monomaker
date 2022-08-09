/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "Components/VerticalGradientMeter.h"
#include "Components/LargeKnob.h"
#include "Components/SmallKnob.h"

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
    void paintOverChildren(juce::Graphics&) override;
    void resized() override;
    void addRotaries();

    bool getMidMuteState() {
        return midMute.getToggleState();
    }

    bool getSideMuteState() {
        return sideMute.getToggleState();
    }
private:

    MonomakerAudioProcessor& audioProcessor;

    Image bgImage, grill, midImage, midLightImage, sideImage, sideLightImage;

    //Slider knob1, knob2;
    //Classes for LookAndFeel
    LargeKnob largeKnob;
    SmallKnob smallKnob;



    std::unique_ptr<Slider> stereoWidthSlider, hpfSlider;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> stereoWidthAttachment, hpfAttachment;
    
    Gui::VerticalGradientMeter verticalGradientMeterM, verticalGradientMeterS;

    ImageButton midMute, sideMute;
    std::unique_ptr<AudioProcessorValueTreeState::ButtonAttachment> midMuteAttachment, sideMuteAttachment;


    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MonomakerAudioProcessorEditor)
};
