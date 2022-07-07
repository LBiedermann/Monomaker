/*
  ==============================================================================

    MidSide.cpp
    Created: 29 Jun 2022 11:47:43am
    Author:  Lukas

  ==============================================================================
*/

#include "MidSide.h"

void MidSide::midSideEncode(const float& L, const float& R, float& M, float& S) {
    M = L + R;
    S = L - R;
}

void MidSide::midSideDecode(const float& M, const float& S, float& L, float& R) {
    L = 0.5f * (M + S);
    R = 0.5f * (M - S);
}

void MidSide::processStereoWidth(float& L, float& R) {
    float M = 0.f;
    float S = 0.f;

    // LR --> MS
    midSideEncode(L, R, M, S);

    if (midMute)
        M = 0.f;
    else{
        //width --> 0 to 2
        M *= (2.f - stereoWidth);
        //store Sum for RMS
        sumMid += M * M;
    }
    
    if (sideMute) 
        S = 0.f;
    else{
        //monomaker
        S = iirFilter.processSingleSampleRaw(S);

        //width --> 0 to 2
        S *= stereoWidth;

        //store Sum for RMS
        sumSide += S * S;
    }

    midSideDecode(M, S, L, R);
}

void MidSide::processStereoWidth(float* leftChannel, float* rightChannel, const int N) {
    sumMid = 0.f;
    sumSide = 0.f;

    for (int n = 0; n < N; n++)
    {
        float L = leftChannel[n];
        float R = rightChannel[n];
        processStereoWidth(L, R);
        leftChannel[n] = L;
        rightChannel[n] = R;
    }

    calcRMSLevel(N);
}

void MidSide::processStereoWidth(juce::AudioBuffer<float> &buffer) {

    float* leftChannel = buffer.getWritePointer(0);
    float* rightChannel = buffer.getWritePointer(1);
    int N = buffer.getNumSamples();
    processStereoWidth(leftChannel, rightChannel, N);
}

void MidSide::calcRMSLevel(int N) {

    rmsLevelMid.skip(N);
    rmsLevelSide.skip(N);
    {
        const auto midValue = juce::Decibels::gainToDecibels(std::sqrt(sumMid / N));
        if (midValue < rmsLevelMid.getCurrentValue())
            rmsLevelMid.setTargetValue(midValue);
        else
            rmsLevelMid.setCurrentAndTargetValue(midValue);
    }

    {
        const auto sideValue = juce::Decibels::gainToDecibels(std::sqrt(sumSide / N));
        if (sideValue < rmsLevelSide.getCurrentValue())
            rmsLevelSide.setTargetValue(sideValue);
        else
            rmsLevelSide.setCurrentAndTargetValue(sideValue);
    }

}

