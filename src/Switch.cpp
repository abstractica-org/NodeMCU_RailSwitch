/*
  Author: Tobias Grundtvig
*/

#include <Arduino.h>
#include "Switch.h"

Switch::Switch( SwitchCtrl* pSwitchCtrl,
                uint8_t ledPin,
                bool ledOn,
                const char* deviceType,
                uint16_t deviceVersion) :
                RemoteDevice(ESP.getChipId(), deviceType, deviceVersion),
                _led(ledPin, ledOn, 100, 300, 1000)
{
    _pSwitchCtrl = pSwitchCtrl;
    _pSwitchCtrl->setListener(this);
    _ledEndTime = 0;

}

void Switch::update(unsigned long curTime)
{
    _curTime = curTime;
    RemoteDevice::update(curTime);
    _pSwitchCtrl->update(curTime);
    _led.update(curTime);
    if(_led.isBlinking() && curTime > _ledEndTime)
    {
        _led.stopBlink();
    }
}

uint16_t Switch::onPacketReceived(uint16_t command, uint16_t arg1, uint16_t arg2, uint16_t arg3, uint16_t arg4, uint8_t* pData, uint16_t size)
{
    switch(command)
    {
        case CMD_IDENTIFY:
            _led.startBlink(arg1);
            _ledEndTime = _curTime + ((unsigned int) arg2) * 1000;
            return 0;
        case CMD_SWITCH_LEFT:
            if(_pSwitchCtrl->switchTo(LEFT))
            {
                return 0;
            }
            else
            {
                return 101;
            }
        case CMD_SWITCH_RIGHT:
            if(_pSwitchCtrl->switchTo(RIGHT))
            {
                return 0;
            }
            else
            {
                return 101;
            }
        case CMD_GET_STATE:
            sendPacketToServer(CMD_ON_STATE_CHANGE, _pSwitchCtrl->getState(), 0, 0, 0, true, true);
            return 0;
        default:
            return 404;
    }
}

void Switch::onStateChange(uint8_t newState)
{
    sendPacketToServer(CMD_ON_STATE_CHANGE, newState, 0, 0, 0, true, true);
}