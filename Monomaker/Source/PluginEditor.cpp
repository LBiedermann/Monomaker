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


    ////knob1.addListener(this);
    //knob1.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    //knob1.setBounds(30, 20, 200, 200);
    //knob1.setRange(20.f, 20000.f, 0.1f);
    //knob1.setValue(1.f);
    //knob1.setTextBoxStyle(Slider::TextBoxAbove, false, 75, 25);
    //knob1.setLookAndFeel(&lookAndFeelV4);
    //addAndMakeVisible(knob1);

    //
    ////knob2.addListener(this);
    //knob2.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    //knob2.setBounds(55, 220, 150, 150);
    //knob2.setRange(0.f, 2.f, 0.1f);
    //knob2.setValue(1.f);
    //knob2.setTextBoxStyle(Slider::TextBoxAbove, false, 75, 25);
    //knob2.setLookAndFeel(&lookAndFeelV4);
    //addAndMakeVisible(knob2);
    addRotaries();
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
//
//void MonomakerAudioProcessorEditor::sliderValueChanged(Slider * slider) {
//    if (slider == &knob1) {
//    }
//}

void MonomakerAudioProcessorEditor::addRotaries() {
    //Hpf Slider
    hpfSlider = std::make_unique<Slider>(Slider::SliderStyle::RotaryHorizontalVerticalDrag,Slider::TextBoxAbove);
    hpfSlider->setBounds(30, 20, 200, 200);
    hpfSlider->setLookAndFeel(&lookAndFeelV4);
    addAndMakeVisible(hpfSlider.get());
    //hpfAttachment = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts, "HPF", *hpfSlider);

    //StereoWidth Slider
    stereoWidthSlider = std::make_unique<Slider>(Slider::SliderStyle::RotaryHorizontalVerticalDrag,Slider::TextBoxAbove);
    stereoWidthSlider->setBounds(55, 220, 150, 150);
    stereoWidthSlider->setLookAndFeel(&lookAndFeelV4);
    addAndMakeVisible(stereoWidthSlider.get());
    //stereoWidthAttachment = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts, "STE", *stereoWidthSlider);
}