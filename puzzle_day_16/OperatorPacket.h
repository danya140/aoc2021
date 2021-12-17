#pragma once

#include "Packet.h"


class OperatorPacket : public Packet
{
public:
    OperatorPacket(Header header, const std::vector<Packet*>& packets, int size, int data = 0);

    /**
     * Perform action according to type
     */
    long long int doAction() override;

    static OperatorPacket* parseOperatorPacket(const std::vector<int>& bits);

};