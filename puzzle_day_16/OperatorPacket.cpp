#include "OperatorPacket.h"

#include "ParserHelpers.h"

OperatorPacket* OperatorPacket::parseOperatorPacket(const std::vector<int> &bits)
{
    auto header = Header::parseHeader(bits);
    assert(header.m_type != 4);

    int length = -1;
    int subPacketsLength = -1;

    int lengthSize;
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

        auto packet = parsePacketByType(nextDataBits);
        realLength += packet->size();
        subPackets.push_back(packet);

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
