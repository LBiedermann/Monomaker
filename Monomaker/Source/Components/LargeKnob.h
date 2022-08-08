#ifndef LARGEKNOB_H_INCLUDED
#define LARGEKNOB_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"
using namespace juce;

class LargeKnob : public LookAndFeel_V4
{
public:
    Image sprite = ImageCache::getFromMemory(BinaryData::knob_big_png, BinaryData::knob_big_pngSize);
    double customSkew = 0.3;
    void drawRotarySlider(Graphics& g, int x, int y, int width, int height, float sliderPos, const float rotaryStartAngle, const float rotaryEndAngle, Slider& slider);
};

#endif /* LARGEKNOB_H_INCLUDED */


