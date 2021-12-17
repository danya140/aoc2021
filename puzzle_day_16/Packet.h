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

    Packet(Header header, long long int data, int size);

    /**
     * @return size of packet in bits
     */
    int size() const;

    /**
     * @return Sum of all inner packets versions + this packet version
     */
    virtual int versions();

    /**
     * @return data
     */
    virtual long long int doAction();

    static Packet* parsePacket(const std::vector<int>& bits);

protected:
    Header m_header;
    long long int m_data;
    int m_size; //in bits
    std::vector<Packet*> m_packets; //for easy debug its here
};
