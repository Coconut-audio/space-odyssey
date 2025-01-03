/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "XyPad.h"
#include "VectorScope.h"

//==============================================================================
/**
*/
class SpaceodysseyAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    SpaceodysseyAudioProcessorEditor (SpaceodysseyAudioProcessor&);
    ~SpaceodysseyAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    SpaceodysseyAudioProcessor& audioProcessor;

    // components
    XyPad xyPad;
    VectorScope vectorScope;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SpaceodysseyAudioProcessorEditor)
};
