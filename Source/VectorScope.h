/*
  ==============================================================================

    VectorScope.h
    Created: 2 Jan 2025 5:15:54pm
    Author:  vivek

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class VectorScope  : public juce::Component
{
public:
    VectorScope();
    ~VectorScope() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (VectorScope)
};
