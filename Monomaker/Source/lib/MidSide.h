/*
  ==============================================================================

    MidSide.h
    Created: 29 Jun 2022 11:47:43am
    Author:  Lukas

  ==============================================================================
*/
#include <JuceHeader.h>
//#include "EQ.h"

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


    void updateCutFilter(std::atomic<float>* newFrequency) {
        iirFilter.setCoefficients(juce::IIRCoefficients::makeHighPass
        (sampleRate, newFrequency->load()));
    }

    void filterReset() {
        iirFilter.reset();
    }
    void setSamplerate(double newSamplerate) {
        sampleRate = newSamplerate;
    }


private:

    
    float stereoWidth = 1.0f;
    
    double sampleRate = 48000;
    float frequenzy = 20.f;
    juce::IIRFilter iirFilter;
};