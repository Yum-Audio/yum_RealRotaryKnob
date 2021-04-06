#include "yum_RealRotaryKnob.h"

namespace YumAudio
{

RealRotaryKnob::RealRotaryKnob (Slider* sliderToLink)
:
linkedSlider (sliderToLink)
{
    setSliderStyle(Slider::Rotary);
    setTextBoxStyle(Slider::NoTextBox, true, 0, 0);
    
    setVelocityBasedMode(true);
    setVelocityModeParameters(0.15, 0, 0.0, false);
    setSliderSnapsToMousePosition(false);

    
    currentSliderValue = Slider::getValue();
    
    addListener (this);
    if (linkedSlider)
    {
        setRange (linkedSlider->getRange (), linkedSlider->getInterval());
        linkedSlider->addListener (this);
    }
}

RealRotaryKnob::~RealRotaryKnob()
{
    if (linkedSlider)
        linkedSlider->removeListener (this);
}

void RealRotaryKnob::sliderValueChanged (Slider* s)
{
    if (s == linkedSlider)
    {
        setValue (s->getValue (), dontSendNotification);
        currentSliderValue = getValue();
        repaint ();
    }
    else if (s == this && linkedSlider)
    {
        linkedSlider->setValue (getValue(), sendNotification);
    }
}

bool RealRotaryKnob::hitTest (int x, int y)
{
//    int dia = std::min (getWidth(), getHeight()) * 0.5;
//    return getLocalBounds().getCentre().getDistanceFrom ({x, y}) < dia;
    return true;
}

void RealRotaryKnob::mouseDown(const MouseEvent& e)
{
        scrub = true;
    scrubAngle = getLocalBounds().getCentre().toFloat().getAngleToPoint (e.getPosition().toFloat());

    repaint();
}
void RealRotaryKnob::mouseDrag(const MouseEvent& e)
{
        auto clickAngle = getLocalBounds().getCentre().toFloat().getAngleToPoint (e.getPosition().toFloat());
    auto newAngle = 180.0 * (clickAngle - scrubAngle) / juce::float_Pi;
    currentSpeed = jlimit (-0.6, 0.6, newAngle * 0.5);
    angle = angle + newAngle;
    scrubAngle = clickAngle;

    currentSliderValue = jlimit(Slider::getRange().getStart(), Slider::getRange().getEnd(), currentSliderValue + currentSpeed.load());
    
    
    if ((int) currentSliderValue != (int)Slider::getValue())
        Slider::setValue(currentSliderValue, sendNotification);
    
    repaint();
}
void RealRotaryKnob::mouseUp(const MouseEvent& e)
{
    scrub = false;
    repaint();
}

void RealRotaryKnob::resized()
{
    auto area = getLocalBounds().toFloat();
    
    touchPath.clear();
    touchPath.addPieSegment(area, degreesToRadians(0.0f), degreesToRadians(360.0f), 0.0f);
    
    Slider::resized();
}

};
