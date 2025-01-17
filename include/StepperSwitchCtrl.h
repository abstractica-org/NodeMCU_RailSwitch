/*
  Author: Tobias Grundtvig
*/

#ifndef StepperSwitchCtrl_h
#define StepperSwitchCtrl_h

#include <Arduino.h>
#include <AccelStepper.h>
#include <SwitchCtrl.h>
#include <SwitchListener.h>

class StepperSwitchCtrl : public SwitchCtrl
{
public:
    StepperSwitchCtrl(  uint8_t motorPin1,
                        uint8_t motorPin2,
                        uint8_t motorPin3,
                        uint8_t motorPin4 );
    void setListener(SwitchListener* pListener) {_pListener = pListener;}
    void update(unsigned long curTime);
    bool switchTo(uint8_t side);
    uint8_t getState() {return _state;}
private:
    void calibrate();
    SwitchListener* _pListener;
    AccelStepper _stepper;
    uint8_t _state;
    unsigned long _lastStateSend;
};

#endif