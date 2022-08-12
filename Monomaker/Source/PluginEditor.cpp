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
    midImage = ImageCache::getFromMemory(BinaryData::MID_btn_png, BinaryData::MID_btn_pngSize);
    midLightImage = ImageCache::getFromMemory(BinaryData::MID_Light_png, BinaryData::MID_Light_pngSize);
    sideImage = ImageCache::getFromMemory(BinaryData::SIDE_btn_png, BinaryData::SIDE_btn_pngSize);
    sideLightImage = ImageCache::getFromMemory(BinaryData::SIDE_Light_png, BinaryData::SIDE_Light_pngSize);

    addAndMakeVisible(verticalGradientMeterM);
    addAndMakeVisible(verticalGradientMeterS);

    addAndMakeVisible(midMute);
    midMute.setImages(false,false,false,midImage,1.0f,{}, midImage, 1.0f,{},midLightImage,1.0f,{},{});
    midMute.setClickingTogglesState(true);
    midMute.setMouseCursor(MouseCursor::PointingHandCursor);
    audioProcessor.getMidSide().setMidState(&midMute);
    midMuteAttachment = std::make_unique<AudioProcessorValueTreeState::ButtonAttachment>(audioProcessor.apvts, "MM", midMute);

    addAndMakeVisible(sideMute);
    sideMute.setClickingTogglesState(true);
    sideMute.setImages(true, false, false, sideImage, 1.0f, {}, sideImage, 1.0f, {}, sideLightImage, 1.0f, {}, {});
    sideMute.setMouseCursor(MouseCursor::PointingHandCursor);
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

    midMute.setBounds(273, 28, 46, 25);
    sideMute.setBounds(323, 28, 46, 25);

}
//


void MonomakerAudioProcessorEditor::addRotaries() {


    //Hpf Slider
    hpfSlider = std::make_unique<Slider>(Slider::SliderStyle::RotaryHorizontalVerticalDrag, Slider::TextBoxAbove);
    hpfSlider->setBounds(42, 50.4, 243, 214);
    hpfSlider->setLookAndFeel(&largeKnob);
    hpfSlider->setMouseCursor(MouseCursor::PointingHandCursor);
    addAndMakeVisible(hpfSlider.get());
    hpfAttachment = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts, "HPF", *hpfSlider);


    //StereoWidth Slider
    stereoWidthSlider = std::make_unique<Slider>(Slider::SliderStyle::RotaryHorizontalVerticalDrag, Slider::NoTextBox );
    stereoWidthSlider->setBounds(50.4, 235.2, 189, 155);
    stereoWidthSlider->setLookAndFeel(&smallKnob); 
    stereoWidthSlider->setMouseCursor(MouseCursor::PointingHandCursor);
    addAndMakeVisible(stereoWidthSlider.get());
    stereoWidthAttachment = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts, "STE", *stereoWidthSlider);
}