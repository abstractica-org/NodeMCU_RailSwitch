#include <Arduino.h>
#include <WiFiManager.h>
#include <Switch.h>

//********************* Configuration *************************

//Uncomment ONLY ONE of these:
#define DEVICE_TYPE "Left_Switch" //Left switch
//#define DEVICE_TYPE "Right_Switch" //Right switch

#define DEVICE_VERSION 1

#define LED_PIN LED_BUILTIN
#define LED_ON LOW
#define WIFI_RESET_PIN D7

//********************* Configuration *************************

#include <StepperSwitchCtrl.h>
#define MOTOR_PIN_1 5
#define MOTOR_PIN_2 4
#define MOTOR_PIN_3 14
#define MOTOR_PIN_4 12
StepperSwitchCtrl switchCtrl( MOTOR_PIN_1,
                              MOTOR_PIN_2,
                              MOTOR_PIN_3,
                              MOTOR_PIN_4 );


Switch rail_switch(&switchCtrl, LED_PIN, LED_ON, DEVICE_TYPE, DEVICE_VERSION);

void setup()
{
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(WIFI_RESET_PIN, INPUT_PULLUP);
  delay(10);
  bool resetWiFi = !digitalRead(WIFI_RESET_PIN);
  Serial.print("WiFiConfig -> Reset WiFi button pushed? : ");
  if(resetWiFi)
  {
    Serial.println("YES");
  }
  else
  {
    Serial.println("NO");
  }

  String apName = "Switch_";
  apName += ESP.getChipId();

  //WiFiManager
  WiFiManager wifiManager;
  //reset saved settings
  if(resetWiFi)
  {
    wifiManager.resetSettings();
  }
  
  wifiManager.autoConnect(apName.c_str());
  //if you get here you have connected to the WiFi
  Serial.println("WiFi is connected!");

  rail_switch.begin(3377, 3377);
}

void loop()
{
  rail_switch.update(millis());
}