//
// Created by Arthur Zerr on 13.01.23.
//

#ifndef CONTROLMODULE_CANBUSHELPER_H
#define CONTROLMODULE_CANBUSHELPER_H

#include "../lib/mcp2515/mcp2515.h"

class CanBusHelper {

private:
    MCP2515 mcp2515;

public:
    CanBusHelper();

    /**
     * Initializes the CanBus
     */
    void init();

    /**
     * Sends a message over the CanBus
     *
     * @param bytes bytes to send
     * @param len message length
     */
    void sendMessage(unsigned long commandId, const unsigned char *bytes, int len);

};


#endif //CONTROLMODULE_CANBUSHELPER_H
