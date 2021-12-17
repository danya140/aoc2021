#include "ParserHelpers.h"

long long int readBits(const std::vector<int> &bits, int length, int start)
{
    long long int result = 0;

    std::vector<long long int> reverseBits;
    std::copy(bits.begin() + start, bits.begin()  + start + length, std::back_inserter(reverseBits));
    std::reverse(reverseBits.begin(), reverseBits.end());

    for (int i = 0; i < length; ++i)
    {
        result += reverseBits[i] * std::pow(2, i);
    }

    return result;
}

/**
 * Parse data bits with trailing zeros
 */
std::vector<int> readLiteral(const std::vector<int> &bits)
{
    std::vector<int> dataBits;
    std::copy(bits.begin() + HEADER_SIZE, bits.end(), std::back_inserter(dataBits));

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

/**
 * Clear data bits from leading bit
 */
std::vector<int> deleteStartingBit(const std::vector<int> &bits)
{
    std::vector<int> dataBits;

    for (int i = 0; i < bits.size(); i +=5)
    {
        std::copy(bits.begin() + i + 1, bits.begin() + i + 5, std::back_inserter(dataBits));
    }
    return  dataBits;
}

/**
 * Parse packet according to header type
 */
Packet* parsePacketByType(const std::vector<int> &nextDataBits)
{
    auto subHeader = Header::parseHeader(nextDataBits);
    if (subHeader.m_type == 4)
    {
        return Packet::parsePacket(nextDataBits);
    }
    else
    {
        return OperatorPacket::parseOperatorPacket(nextDataBits);
    }
}
