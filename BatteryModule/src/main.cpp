#include <SPI.h>
#include "../lib/vector/Vector.h"
#include "../lib/mcp2515/mcp2515.h"
#include "CanBusModules.h"

#include <Arduino.h>

MCP2515 mcp2515(10);


void setup() {

    while (!Serial);
    Serial.begin(115200);

    mcp2515.reset();
    mcp2515.setBitrate(CAN_125KBPS);
    mcp2515.setNormalMode();

    Serial.println("Example: Write to CAN");
}




void loop() {
    int sensorValue = analogRead(A0);
    // print out the value you read:
    unsigned char bytes[2];



    delay(100);  // delay in between reads for stability
}