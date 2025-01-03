/*
  ==============================================================================

    XyPad.cpp
    Created: 2 Jan 2025 5:14:52pm
    Author:  vivek

  ==============================================================================
*/

#include <JuceHeader.h>
#include "XyPad.h"

//==============================================================================
XyPad::XyPad()
{
    shadow = juce::DropShadow(juce::Colour::fromRGBA(0x00, 0x00, 0x00, 0x66), 15, juce::Point<int>(2, 2));
    light = juce::DropShadow(juce::Colour::fromRGBA(0x80, 0x60, 0x40, 0x15), 15, juce::Point<int>(-2, -2));

    // Set slider properties
    for (int i = 0; i < 2; i++)
    {
        panSlider[i].setSliderStyle(juce::Slider::RotaryVerticalDrag);
        panSlider[i].setRange(minPan, maxPan, 0.0f);
        panSlider[i].setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);
        panSlider[i].addListener(this);

        delaySlider[i].setSliderStyle(juce::Slider::RotaryVerticalDrag);
        delaySlider[i].setRange(minDelay, maxDelay, 0.0f);
        delaySlider[i].setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);
        delaySlider[i].addListener(this);
    }
}

XyPad::~XyPad()
{
}

void XyPad::paint (juce::Graphics& g)
{
    juce::Path clipRegion;
    clipRegion.addRoundedRectangle(backgroundRect, cornerSize);
    g.saveState();
    g.reduceClipRegion(clipRegion);

    g.setColour(juce::Colour::fromRGB(0x3D, 0x0E, 0x2E));
    g.fillAll();

    // Draw grid lines
    g.setColour(juce::Colour::fromRGBA(0xDE, 0x1C, 0x7C, 0x1A));

    for (float i = minPan; i <= maxPan; i += 20.0f) {
        float x = juce::jmap<float>(i, minPan, maxPan, xyPadRect.getX(), xyPadRect.getRight());
        g.drawLine(x, backgroundRect.getBottom(), x, backgroundRect.getY(), strokeThickness);
    }

    for (int i = minDelay; i <= maxDelay; i += 10) {
        float y = juce::jmap<float>(i, minDelay, maxDelay, xyPadRect.getBottom(), xyPadRect.getY());
        g.drawLine(backgroundRect.getX(), y, backgroundRect.getRight(), y, strokeThickness);
    }

    // Draw thumbs
    float xLeft = juce::jmap<float>(panSlider[0].getValue(), minPan, maxPan, xyPadRect.getX(), xyPadRect.getRight());
    float yLeft = juce::jmap<float>(delaySlider[0].getValue(), maxDelay, minDelay, xyPadRect.getY(), xyPadRect.getBottom());
    thumbPos[0] = juce::Point<float>(xLeft, yLeft);
    g.setColour(juce::Colour::fromRGB(0x00, 0x54, 0xC2));
    g.fillEllipse(thumbPos[0].x - thumbRadius, thumbPos[0].y - thumbRadius, thumbRadius * 2, thumbRadius * 2);
    g.setColour(juce::Colours::white);
    g.setFont(typeface);
    g.setFont(16);
    g.drawFittedText("L", thumbPos[0].x - 4, thumbPos[0].y - 5, 10, 10, juce::Justification::centred, 1);

    float xRight = juce::jmap<float>(panSlider[1].getValue(), minPan, maxPan, xyPadRect.getX(), xyPadRect.getRight());
    float yRight = juce::jmap<float>(delaySlider[1].getValue(), maxDelay, minDelay, xyPadRect.getY(), xyPadRect.getBottom());
    thumbPos[1] = juce::Point<float>(xRight, yRight);
    g.setColour(juce::Colour::fromRGB(0x41, 0x92, 0x00));
    g.fillEllipse(thumbPos[1].x - thumbRadius, thumbPos[1].y - thumbRadius, thumbRadius * 2, thumbRadius * 2);
    g.setColour(juce::Colours::white);
    g.drawFittedText("R", thumbPos[1].x - 4, thumbPos[1].y - 5, 10, 10, juce::Justification::centred, 1);

    // Draw grid labels
    g.setColour(juce::Colours::white);
    g.setFont(12);

    for (float i = minPan + 20.0f; i < maxPan; i += 20.0f) {
        float x = juce::jmap<float>(i, minPan, maxPan, xyPadRect.getX(), xyPadRect.getRight());
        g.drawText(juce::String(i), x - 25, backgroundRect.getBottom() - 20, 50, 20, juce::Justification::centred, true);
        g.drawText(juce::String(i), x - 25, backgroundRect.getY(), 50, 20, juce::Justification::centred, true);
    }

    for (int i = minDelay + 10; i < maxDelay; i += 10) {
        float y = juce::jmap<float>(i, minDelay, maxDelay, xyPadRect.getBottom(), xyPadRect.getY());
        g.drawText(juce::String(i), backgroundRect.getX() + 10, y - 10, 50, 20, juce::Justification::left, true);
        g.drawText(juce::String(i), backgroundRect.getRight() - 60, y - 10, 50, 20, juce::Justification::right, true);
    }

    // Draw shadow and light for frame
    juce::Path frame;
    juce::PathStrokeType strokeType(5.0f * strokeThickness);
    strokeType.createStrokedPath(frame, clipRegion);
    shadow.drawForPath(g, frame);
    light.drawForPath(g, frame);

    g.restoreState();
}

void XyPad::resized()
{
    backgroundRect = getLocalBounds().toFloat();
    xyPadRect = backgroundRect.reduced(10.0f);

    //panSlider[0].setBounds(10, 10, 50, 50);
    //delaySlider[0].setBounds(10, 40, 50, 50);
    //panSlider[1].setBounds(60, 10, 50, 50);
    //delaySlider[1].setBounds(60, 40, 50, 50);
}

void XyPad::mouseDown(const juce::MouseEvent& event)
{
    if (thumbPos[0].getDistanceFrom(juce::Point<float>(event.position.getX(), event.position.getY())) < thumbRadius) {
        draggedThumb = 0;
    }
    else if (thumbPos[1].getDistanceFrom(juce::Point<float>(event.position.getX(), event.position.getY())) < thumbRadius) {
        draggedThumb = 1;
    }
    else {
        draggedThumb = -1;
    }
}

void XyPad::mouseDrag(const juce::MouseEvent& event)
{
	if (draggedThumb != -1) {
		juce::Point<float> newPos = event.position.toFloat();

        newPos.x = juce::jlimit<float>(xyPadRect.getX(), xyPadRect.getRight(), newPos.x);
        newPos.y = juce::jlimit<float>(xyPadRect.getY(), xyPadRect.getBottom(), newPos.y);

        if (draggedThumb == 0) {
            panSlider[0].setValue(juce::jmap<float>(newPos.x, xyPadRect.getX(), xyPadRect.getRight(), minPan, maxPan), juce::NotificationType::dontSendNotification);
            delaySlider[0].setValue(juce::jmap<float>(newPos.y, xyPadRect.getY(), xyPadRect.getBottom(), maxDelay, minDelay), juce::NotificationType::dontSendNotification);
        }
        else if (draggedThumb == 1) {
			panSlider[1].setValue(juce::jmap<float>(newPos.x, xyPadRect.getX(), xyPadRect.getRight(), minPan, maxPan), juce::NotificationType::dontSendNotification);
			delaySlider[1].setValue(juce::jmap<float>(newPos.y, xyPadRect.getY(), xyPadRect.getBottom(), maxDelay, minDelay), juce::NotificationType::dontSendNotification);
		}
	}

    repaint();
}

void XyPad::sliderValueChanged(juce::Slider* slider)
{
    if (slider == &panSlider[0]) {
        thumbPos[0].x = juce::jmap<float>(panSlider[0].getValue(), minPan, maxPan, xyPadRect.getX(), xyPadRect.getRight());
    }
    else if (slider == &delaySlider[0]) {
		thumbPos[0].y = juce::jmap<float>(delaySlider[0].getValue(), maxDelay, minDelay, xyPadRect.getBottom(), xyPadRect.getY());
	}
	else if (slider == &panSlider[1]) {
		thumbPos[1].x = juce::jmap<float>(panSlider[1].getValue(), minPan, maxPan, xyPadRect.getX(), xyPadRect.getRight());
	}
	else if (slider == &delaySlider[1]) {
		thumbPos[1].y = juce::jmap<float>(delaySlider[1].getValue(), maxDelay, minDelay, xyPadRect.getBottom(), xyPadRect.getY());
	}

    repaint();
}