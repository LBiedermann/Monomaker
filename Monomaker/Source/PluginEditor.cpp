/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
MonomakerAudioProcessorEditor::MonomakerAudioProcessorEditor (MonomakerAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (420, 420);
    bgImage = ImageCache::getFromMemory(BinaryData::background_png, BinaryData::background_pngSize);


    knob1.addListener(this);
    knob1.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    knob1.setBounds(50, 50, 200, 200);
    knob1.setTextBoxStyle(Slider::NoTextBox, false, 0, 0);
    knob1.setLookAndFeel(&largeKnob);
    addAndMakeVisible(knob1);


    knob2.addListener(this);
    knob2.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    knob2.setBounds(85, 300, 100, 100);
    knob2.setTextBoxStyle(Slider::NoTextBox, false, 0, 0);
    knob2.setLookAndFeel(&smallKnob);
    addAndMakeVisible(knob2);
}

MonomakerAudioProcessorEditor::~MonomakerAudioProcessorEditor()
{
}

//==============================================================================
void MonomakerAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.drawImageAt(bgImage, 0, 0);
}

void MonomakerAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
}

void MonomakerAudioProcessorEditor::sliderValueChanged(Slider * slider) {

}