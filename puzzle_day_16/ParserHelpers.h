#pragma once

#include "../helpers.h"

#include "OperatorPacket.h"

/**
 * Convert bits to int
 * @param length length of data bits
 * @param start index where data starts
 */
long long int readBits(const std::vector<int> &bits, int length, int start);

/**
 * Parse data bits with trailing zeros
 */
std::vector<int> readLiteral(const std::vector<int> &bits);

/**
 * Clear data bits from leading bit
 */
std::vector<int> deleteStartingBit(const std::vector<int> &bits);

/**
 * Parse packet according to header type
 */
Packet* parsePacketByType(const std::vector<int> &nextDataBits);