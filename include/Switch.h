/*
  Author: Tobias Grundtvig
*/

#ifndef Switch_h
#define Switch_h

#include <Arduino.h>
#include <RemoteDevice.h>
#include <LEDBlinker.h>
#include <SwitchCtrl.h>

#define CMD_IDENTIFY 1000
/*
  Author: Tobias Grundtvig
*/
#define CMD_SWITCH_LEFT 1500
#define CMD_SWITCH_RIGHT 1501
#define CMD_GET_STATE 1502

#define CMD_ON_STATE_CHANGE 2500

class Switch : public RemoteDevice, public SwitchListener
{
public:
    Switch( SwitchCtrl* pSwitchCtrl,
            uint8_t ledPin,
            bool ledOn,
            const char* deviceType,
            uint16_t deviceVersion);
    void update(unsigned long curTime);
    uint16_t onPacketReceived(uint16_t command,
                              uint16_t arg1,
                              uint16_t arg2,
                              uint16_t arg3,
                              uint16_t arg4,
                              uint8_t* pData,
                              uint16_t size);
    void onStateChange(uint8_t newState);
private:
    LEDBlinker _led;
    unsigned long _curTime;
    unsigned long _ledEndTime;
    SwitchCtrl* _pSwitchCtrl;
};

#endif