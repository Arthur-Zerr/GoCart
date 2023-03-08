#include <Arduino.h>
#include "../lib/mcp2515/mcp2515.h"

#define DriveModule_Forward 0x02
#define DriveModule_Backward 0x03

volatile bool interrupt = false;

struct can_frame canMsg;
MCP2515 mcp2515(10);

int motor1_A = 4;
int motor1_B = 3;
int motor1_Speed = 5;

bool isMotorOn = false;
int lastPercentage = 0;

void irqHandler() {
    interrupt = true;
}


void setup() {
    Serial.begin(115200);

    mcp2515.reset();
    mcp2515.setBitrate(CAN_125KBPS);
    mcp2515.setNormalMode();

    pinMode(motor1_A, OUTPUT);
    pinMode(motor1_B, OUTPUT);

//    mcp2515.setFilterMask(MCP2515::MASK0, false, 0xDB2);
//    mcp2515.setFilter(MCP2515::RXF0, false, 0x000);

//    attachInterrupt(0, irqHandler, FALLING);
    digitalWrite(motor1_A, HIGH);
    digitalWrite(motor1_B, LOW);
}


void debugSerial() {
    Serial.print("ID: ");
    Serial.print(canMsg.can_id, HEX); // print ID
    Serial.print(" CL: ");
    Serial.print(canMsg.can_dlc, HEX); // print DLC
    Serial.print(" ");

    for (int i = 0; i < canMsg.can_dlc; i++) {  // print the data
        Serial.print(canMsg.data[i], HEX);
        Serial.print(" ");
    }
}

void runMotor(int pedalPercentage) {
    Serial.print("Forward: ");
    Serial.print(" Pedal: ");
    Serial.print(pedalPercentage);

    int speed = (pedalPercentage * 255) / 100;
    Serial.print(" Speed: ");
    Serial.print(speed);
    Serial.println();


    analogWrite(motor1_Speed, speed);
}


void loop() {
    if (mcp2515.readMessage(MCP2515::RXB0, &canMsg) == MCP2515::ERROR_OK) {
        if (canMsg.can_id == DriveModule_Forward) {
            int pedalPercentage = int(canMsg.data[0]);

            if(pedalPercentage > 1) {
                isMotorOn = true;
                lastPercentage = pedalPercentage;
            }else {
                isMotorOn = false;
                lastPercentage = 0;
            }

        } else if (canMsg.can_id == DriveModule_Backward) {
            int pedalPercentage = int(canMsg.data[0]);
            runMotor(pedalPercentage);
        }
    }

    if(isMotorOn) {
        runMotor(lastPercentage);
    }

}

