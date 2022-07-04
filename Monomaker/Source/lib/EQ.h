/*
  ==============================================================================

    EQ.h
    Created: 4 Jul 2022 12:47:00pm
    Author:  Lukas

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#pragma once

class EQ {

public:
    //inline auto makeLowCutFilter(float freq, double sampleRate)
    //{
    //    return  juce::dsp::FilterDesign<float>::designIIRHighpassHighOrderButterworthMethod(freq, sampleRate, 2); //2 * (chainSettings.lowCutSlope + 1)); --> slope 12db/O
    //}
    //void updateLowCutFilters(float freq, double sampleRate)
    //{
    //    auto lowCutCoefficients = makeLowCutFilter(freq, sampleRate);

    //    auto& leftLowCut = leftChain.get<ChainPositions::LowCut>();
    //    auto& rightLowCut = rightChain.get<ChainPositions::LowCut>();


    //    updateCutFilter(leftLowCut, lowCutCoefficients, chainSettings.lowCutSlope);
    //    updateCutFilter(rightLowCut, lowCutCoefficients, chainSettings.lowCutSlope);
    //}

private:


};