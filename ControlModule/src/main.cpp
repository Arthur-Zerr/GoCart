#include <Arduino.h>
#include "CanBusHelper.h"

#define Drive_Module 0x0444D
#define Battery_Module 0x0424D
#define Control_Module 0x0434D

#define DriveModule_Forward 0x02
#define DriveModule_Backward 0x03


CanBusHelper canBusHelper{};

bool backward = true;

void setup() {
    Serial.begin(115200);
    canBusHelper.init();
}


void sendPedalInformation(int sensorValue) {
    int pedal = max(sensorValue - 170, 0);

    int pedalPercentage = (pedal * 100) / 700;

    unsigned char bytes[2];

    bytes[0] = (pedalPercentage >> 0) & 0xFF;

    Serial.print("Raw pedal value: ");
    Serial.print(pedal);
    Serial.print(" Pedal percentage: ");
    Serial.print(pedalPercentage);
    Serial.println();

    if(!backward)
        canBusHelper.sendMessage(DriveModule_Forward, bytes, 1);
    else
        canBusHelper.sendMessage(DriveModule_Backward, bytes, 1);
}

void loop() {
    int pedalValue = analogRead(A0);
    sendPedalInformation(pedalValue);
    delay(100);
}