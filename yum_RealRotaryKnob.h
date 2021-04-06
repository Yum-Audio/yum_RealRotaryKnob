/***********************************************************************************
 BEGIN_JUCE_MODULE_DECLARATION

  ID:               yum_RealRotaryKnob
  vendor:          Yum Audio
  version:          1.0.0
  name:             Yum Audio - Real Rotary knob
  description:   A rotary knob that can be dialed in with circular motion
  website:
  license:

  dependencies:     juce_core 
  OSXFrameworks:
  iOSFrameworks:
  linuxLibs:
  mingwLibs:

 END_JUCE_MODULE_DECLARATION
***********************************************************************************/

#pragma once

#include <JuceHeader.h>

namespace YumAudio
{
class RealRotaryKnob : public Slider, public Slider::Listener
{
public:
    RealRotaryKnob (Slider* sliderToLink = nullptr);
    ~RealRotaryKnob ();
    
private:
    Slider* linkedSlider { nullptr };
    
    void resized() override;
    
    bool hitTest(int x, int y) override;
    void mouseDown(const MouseEvent& e) override;
    void mouseDrag(const MouseEvent& e) override;
    void mouseUp(const MouseEvent& e) override;

    void sliderValueChanged (Slider* s) override;
    
    Path touchPath;
    
    const float wheelResolution = 1.0f;

    bool                scrub         = false;
    float               scrubAngle    = 0.0;
    std::atomic<float>  currentSpeed  = {0.0};
    std::atomic<double>  angle         = {0.0};
    
    double currentSliderValue = 0;
    

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (RealRotaryKnob)
};

};
