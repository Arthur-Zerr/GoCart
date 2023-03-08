//
// Created by Arthur Zerr on 13.01.23.
//

#include "CanBusHelper.h"

CanBusHelper::CanBusHelper() : mcp2515(10) {
}


void CanBusHelper::init() {
    mcp2515.reset();
    mcp2515.setBitrate(CAN_125KBPS);
    mcp2515.setNormalMode();
}

void CanBusHelper::sendMessage(unsigned long commandId, const unsigned char *bytes, int len) {
    can_frame canFrame{};

    canFrame.can_id = commandId;
    canFrame.can_dlc = len;

    for (int i = 0; i < len; ++i) {
        canFrame.data[i] = bytes[i];
    }

    mcp2515.sendMessage(&canFrame);
}
