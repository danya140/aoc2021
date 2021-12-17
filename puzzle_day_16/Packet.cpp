#include "Packet.h"

namespace
{

/**
 * Convert bits to int
 * @param length length of data bits
 * @param start index where data starts
 */
long long int readBits(const std::vector<int> &bits, int length, int start)
{
    long long int result = 0;

    std::vector<long long int> reverseBits;
    std::copy(bits.begin() + start, bits.begin()  + start + length, std::back_inserter(reverseBits));
    std::reverse(reverseBits.begin(), reverseBits.end());

    for (int i = 0; i < length; ++i)
    {
        result += reverseBits[i] * std::pow(2, i);
        assert(result >= 0);
    }
    return result;
}

/**
 * Parse literal from packet bits
 * @param length length of data bits
 * @param start index where data starts
 * @return
 */
std::vector<int> readLiteral(const std::vector<int> &bits, int length, int start)
{
    std::vector<int> dataBits;
    std::copy(bits.begin() + start, bits.begin()  + start + length, std::back_inserter(dataBits));

    std::vector<int> realData;
    for (int i = 0; i < dataBits.size(); i +=5)
    {
        std::copy(dataBits.begin() + i, dataBits.begin() + i + 5, std::back_inserter(realData));
        if(dataBits[i] == 0)
        {
            break;
        }
    }

    return realData;
}

std::vector<int> deleteStartingBit(const std::vector<int> &bits)
{
    std::vector<int> dataBits;

    for (int i = 0; i < bits.size(); i +=5)
    {
        std::copy(bits.begin() + i + 1, bits.begin() + i + 5, std::back_inserter(dataBits));
    }
    return  dataBits;
}

} // anonymous

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
    std::vector<int> realData = readLiteral(bits, bits.size() - HEADER_SIZE, HEADER_SIZE);
    long long int data = readBits(deleteStartingBit(realData), deleteStartingBit(realData).size(), 0);
    return new Packet(header, data, HEADER_SIZE + realData.size());
}

Packet::Packet(Header header, long long int data, int size)
    : m_header(header),
      m_data(data),
      m_size(size)
{}

int Packet::size()
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

OperatorPacket* OperatorPacket::parseOperatorPacket(const std::vector<int> &bits)
{
    auto header = Header::parseHeader(bits);
    assert(header.m_type != 4);

    int length = -1;
    int subPacketsLength = -1;

    int lengthSize = 0;
    if (bits[HEADER_SIZE] != 1)
    {
        lengthSize = FIFTEEN_BIT_NUMBER;
        length = readBits(bits, FIFTEEN_BIT_NUMBER, HEADER_SIZE + 1);
    }
    else
    {
        lengthSize = ELEVEN_BIT_NUMBER;
        subPacketsLength = readBits(bits, ELEVEN_BIT_NUMBER, HEADER_SIZE + 1);
    }

    std::vector<Packet*> subPackets;

    int realLength = 0;

    int dataShift = HEADER_SIZE + lengthSize + 1;
    std::vector<int> dataBits;
    std::copy(bits.begin() + dataShift, bits.end(), std::back_inserter(dataBits));

    while (realLength != length && length != -1
            || subPackets.size() != subPacketsLength && subPacketsLength != -1)
    {
        std::vector<int> nextDataBits;
        std::copy(dataBits.begin() + realLength, dataBits.end(), std::back_inserter(nextDataBits));

        if (nextDataBits.size() < HEADER_SIZE)
        {
            break;
        }

        auto subHeader = Header::parseHeader(nextDataBits);
        if (subHeader.m_type == 4)
        {
            auto subPacket = Packet::parsePacket(nextDataBits);
            realLength += subPacket->size();
            subPackets.push_back(subPacket);
        }
        else
        {
            auto subPacket = OperatorPacket::parseOperatorPacket(nextDataBits);
            realLength += subPacket->size();
            subPackets.push_back(subPacket);
        }

        nextDataBits.clear();
    }

    return new OperatorPacket(header, subPackets, realLength + dataShift);
}

OperatorPacket::OperatorPacket(Header header, const std::vector<Packet*>& packets, int size, int data)
    : Packet(header, data, size)
{
    std::copy(packets.begin(), packets.end(), std::back_inserter(m_packets));
}

long long int OperatorPacket::doAction()
{
    std::vector<long long int> subPacketsValues;

    for (const auto& subPacket : m_packets)
    {
        auto value = subPacket->doAction();
        assert(value >= 0);
        subPacketsValues.push_back(value);
    }

    long long int result = 0;

    switch (m_header.m_type)
    {
        case 0:
            result = std::accumulate(subPacketsValues.begin(), subPacketsValues.end(), result);
            break;
        case 1:
            result = std::accumulate(subPacketsValues.begin(), subPacketsValues.end(), ++result, std::multiplies<long long int>());
            break;
        case 2:
            std::sort(subPacketsValues.begin(), subPacketsValues.end());
            result = subPacketsValues.front();
            break;
        case 3:
            std::sort(subPacketsValues.begin(), subPacketsValues.end());
            result = subPacketsValues.back();
            break;
        case 5:
            assert(subPacketsValues.size() == 2);
            result = subPacketsValues.front() > subPacketsValues.back();
            break;
        case 6:
            assert(subPacketsValues.size() == 2);
            result = subPacketsValues.front() < subPacketsValues.back();
            break;
        case 7:
            assert(subPacketsValues.size() == 2);
            result = subPacketsValues.front() == subPacketsValues.back();
            break;
    }

    assert(result >= 0);
    return result;
}