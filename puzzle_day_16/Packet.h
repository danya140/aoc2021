#pragma once

#include "../helpers.h"

const int TYPE_SIZE = 3;
const int VERSION_SIZE = 3;
const int HEADER_SIZE = TYPE_SIZE + VERSION_SIZE;
const int FIFTEEN_BIT_NUMBER = 15;
const int ELEVEN_BIT_NUMBER = 11;

struct Header
{
    static Header parseHeader(const std::vector<int>& bits);

    int m_version;
    int m_type;
};


class Packet
{
public:

    Packet(Header header, int data, int size);

    int size();

    virtual int versions();

    virtual long long int doAction();

    static Packet* parsePacket(const std::vector<int>& bits);

protected:
    Header m_header;
    long long int m_data;
    int m_size; //in bits
    std::vector<Packet*> m_packets; //for easy debug its here
};

class OperatorPacket : public Packet
{
public:
    OperatorPacket(Header header, const std::vector<Packet*>& packets, int size, int data = 0);

    long long int doAction() override;

    static OperatorPacket* parseOperatorPacket(const std::vector<int>& bits);

};
