/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
SpaceodysseyAudioProcessorEditor::SpaceodysseyAudioProcessorEditor (SpaceodysseyAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    setSize (600, 300);

    addAndMakeVisible (xyPad);
    addAndMakeVisible(vectorScope);
}

SpaceodysseyAudioProcessorEditor::~SpaceodysseyAudioProcessorEditor()
{
}

//==============================================================================
void SpaceodysseyAudioProcessorEditor::paint (juce::Graphics& g)
{
    g.setColour(juce::Colour::fromRGB(0x4D, 0x0E, 0x2E));
    g.fillAll();
}

void SpaceodysseyAudioProcessorEditor::resized()
{
    juce::Rectangle<float> xyPadRect = getLocalBounds().toFloat();
    xyPadRect.setRight(300.0f);
    xyPadRect = xyPadRect.reduced(10.0f);
    xyPad.setBounds(xyPadRect.toNearestInt());

    juce::Rectangle<float> vectorScopeRect = getLocalBounds().toFloat();
    vectorScopeRect.setLeft(300.0f);
    vectorScopeRect = vectorScopeRect.reduced(10.0f);
    vectorScope.setBounds(vectorScopeRect.toNearestInt());
}
