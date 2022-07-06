/*
  ==============================================================================

    VerticalGradientMeter.h
    Created: 6 Jul 2022 3:14:02pm
    Author:  Lukas

  ==============================================================================
*/

#pragma once
using namespace juce;

#include <JuceHeader.h>
namespace Gui {

    class VerticalGradientMeter : public Component, public Timer {

    public:
  
        VerticalGradientMeter(std::function<float()>&& valueFunction) : valueSupplier(std::move(valueFunction)) {
            startTimer(30);
        }

        void paint(Graphics& g) override {
            const auto level = valueSupplier();

            auto bounds = getLocalBounds().toFloat();
            g.setColour(Colours::black);
            g.fillRect(bounds);

            g.setGradientFill(gradient);
            const auto scaledY =
                jmap(level, -60.f, 6.f, 0.f, static_cast<float>(getHeight()));
            g.fillRect(bounds.removeFromBottom(scaledY));
        }

        void resized() override {

            auto bounds = getLocalBounds().toFloat();
            ColourGradient gradient{
                Colours::green,
                bounds.getBottomLeft(),
                Colours::red,
                bounds.getTopLeft(),
                false
            };
            gradient.addColour(0.5, Colours::yellow);
        }

        void timerCallback() override {
            repaint();
        }

    private:
        std::function<float()> valueSupplier;
        ColourGradient gradient{};
    };
}
