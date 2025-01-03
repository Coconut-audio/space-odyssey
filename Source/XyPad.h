/*
  ==============================================================================

    XyPad.h
    Created: 2 Jan 2025 5:14:52pm
    Author:  vivek

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class XyPad  : public juce::Component, public juce::Slider::Listener
{
public:
    XyPad();
    ~XyPad() override;

    void paint (juce::Graphics&) override;
    void resized() override;

    void mouseDown(const juce::MouseEvent&) override;
    void mouseDrag(const juce::MouseEvent&) override;
    void sliderValueChanged(juce::Slider*) override;

private:
    juce::Rectangle<float> backgroundRect;
    juce::Rectangle<float> xyPadRect;

    // shadow and light
    juce::DropShadow shadow;
    juce::DropShadow light;

    // Variables
    float strokeThickness = 2.0f;
    float cornerSize = 10.0f;

    // Thumb
    juce::Point<float> thumbPos[2];
    float thumbRadius = 10.0f;
    int draggedThumb = -1;

    // Sliders
    juce::Slider panSlider[2];
    juce::Slider delaySlider[2];
    //std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> panAttachment[2];
    //std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> delayAttachment[2];

    // Slider ranges
    float minPan = -100.0f;
    float maxPan = 100.0f;
    float minDelay = 0.0f;
    float maxDelay = 60.0f;

    // Custom font
    juce::Typeface::Ptr typeface = juce::Typeface::createSystemTypefaceFor(BinaryData::DotGothic16Regular_ttf, BinaryData::DotGothic16Regular_ttfSize);

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (XyPad)
};
