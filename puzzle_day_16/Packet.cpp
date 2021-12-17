#include "Packet.h"

#include "ParserHelpers.h"

Header Header::parseHeader(const std::vector<int> &bits)
{
    std::vector<int> headerBits;
    std::copy(bits.begin(), bits.begin() + HEADER_SIZE, std::back_inserter(headerBits));

    int version = readBits(headerBits, VERSION_SIZE, 0);
    int type = readBits(headerBits, TYPE_SIZE, 3);

    return {version, type};
}

Packet* Packet::parsePacket(const std::vector<int> &bits)
{
    auto header = Header::parseHeader(bits);

    std::vector<int> realData = readLiteral(bits); //read all bytes with trailing zeros
    long long int data = readBits(deleteStartingBit(realData), deleteStartingBit(realData).size(), 0);

    return new Packet(header, data, HEADER_SIZE + realData.size());
}

Packet::Packet(Header header, long long int data, int size)
    : m_header(header),
      m_data(data),
      m_size(size)
{}

int Packet::size() const
{
    return m_size;
}

int Packet::versions()
{
    int versions = 0;

    for (const auto& packet : m_packets)
    {
        versions += packet->versions();
    }

    return versions + m_header.m_version;
}

long long int Packet::doAction()
{
    return m_data;
}
