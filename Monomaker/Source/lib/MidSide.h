/*
  ==============================================================================

    MidSide.h
    Created: 29 Jun 2022 11:47:43am
    Author:  Lukas

  ==============================================================================
*/
#include <JuceHeader.h>
#pragma once

class MidSide {

public:

    void processStereoWidth(float& L, float& R);
    void processStereoWidth(float* leftChannel, float* rightChannel, const int N);
    void processStereoWidth(juce::AudioBuffer<float>& buffer);

    void midSideEncode(const float& L, const float& R, float& M, float& S);
    void midSideDecode(const float& M, const float& S, float& L, float& R);

    void setStereowidthValue(std::atomic<float> *newWidth) {
        stereoWidth = *newWidth;
    }
    void setSamplerate(double newSamplerate) {
        sampleRate = newSamplerate;
    }

    void updateCutFilter(std::atomic<float>* newFrequency) {
        //frequenzy = *newFrequency;
        iirFilter[0].setCoefficients(juce::IIRCoefficients::makeLowPass
        (sampleRate, newFrequency->load()));
        iirFilter[1].setCoefficients(juce::IIRCoefficients::makeLowPass
        (sampleRate, newFrequency->load()));
    }

    void filterReset() {
        iirFilter[0].reset();
        iirFilter[1].reset();
    }
private:

    double sampleRate = 48000;
    float stereoWidth = 1.0f;
    float frequenzy = 20.f;
    juce::IIRFilter iirFilter[2];

};