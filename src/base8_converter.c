/**
 * @file base8_converter.c
 * @author Adrian STEINER (adi.steiner@hotmail.ch)
 * @brief Base8 byte converter with parity validation for potential padding bits.
 *
 * This module provides functionality to encode and decode byte arrays using a base8 representation.
 * It includes mechanisms to handle and verify parity bits that may be introduced due to padding,
 * ensuring data integrity during conversion.
 *
 * @version 0.1
 * @date 30-03-2025
 *
 * @copyright (C) 2025 Adrian STEINER
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https: //www.gnu.org/licenses/>.
 *
 */

#include "base8_converter.h"
#include <string.h>

const uint8_t baseNumberOfBits[8] = {
    0, // 000
    1, // 001
    1, // 010
    2, // 011
    1, // 100
    2, // 101
    2, // 110
    3, // 111
};

baseX_returnType base8_encodeBytes(
    uint8_t *encodedString,
    uint32_t encodedStringSize,
    const uint8_t *srcBytes,
    uint32_t srcBytesSize) {
  if (NULL == encodedString || NULL == srcBytes) {
    return BASEX_ARGUMENTS;
  }

  // Check needed length
  uint32_t outputLength = srcBytesSize * BASEX_BYTE_BIT_LENGTH / BASE8_BIT_LENGTH;

  uint8_t checkBits = (srcBytesSize) % BASE8_BIT_LENGTH;
  if (checkBits) {
    outputLength++;
  }
  // Check overflow
  if (outputLength >= encodedStringSize) {
    return BASEX_OVERFLOW;
  }

  uint16_t carry = 0;
  uint16_t carryLength = 0;
  uint32_t numberOfBits = 0;

  uint32_t outPos = 0;

  for (uint32_t srcPos = 0; srcPos < srcBytesSize; srcPos++) {
    carry += ((((uint16_t)srcBytes[srcPos]) & UINT8_MAX) << (BASEX_BYTE_BIT_LENGTH - carryLength));
    for (uint8_t i = 0; i < (2 + (carryLength ? 1 : 0)); i++) {
      uint8_t newBase8Number = carry >> (16 - BASE8_BIT_LENGTH);
      numberOfBits += baseNumberOfBits[newBase8Number];
      encodedString[outPos] = newBase8Number + BASE8_STARTCHAR;
      outPos++;
      carry = (carry << BASE8_BIT_LENGTH);
    }
    if (0 == carryLength) {
      carryLength = 2;
    } else {
      carryLength--;
    }
  }
  // Add one additional number with checkBits
  if (checkBits) {
    encodedString[outPos] = (carry >> (16 - BASE8_BIT_LENGTH)) + (numberOfBits % (2 * checkBits)) + BASE8_STARTCHAR;
    outPos++;
  }
  encodedString[outPos] = '\0';
  return BASEX_OK;
}

baseX_returnType base8_stringToNum(
    uint8_t *number,
    const char *srcString) {
  if (NULL == number || NULL == srcString) {
    return BASEX_ARGUMENTS;
  }
  uint32_t srcLength = strlen(srcString);
  if (0 == srcLength) {
    return BASEX_ARGUMENTS;
  }

  for (uint32_t i = 0; i < srcLength; i++) {
    if (srcString[i] < BASE8_STARTCHAR || srcString[i] > BASE8_ENDCHAR) {
      return BASEX_SRCERROR;
    } else {
      number[i] = (uint8_t)srcString[i] - BASE8_STARTCHAR;
    }
  }
  return BASEX_OK;
}

baseX_returnType base8_decodeNum(
    uint8_t *decodedBytes,
    uint32_t *decodedLength,
    uint32_t decodedBytesSize,
    const uint8_t *srcNumbers,
    const uint32_t srcLength) {

#define NO_CHECK_BYTES (8)

  if (NULL == decodedBytes || NULL == decodedLength || NULL == srcNumbers) {
    return BASEX_ARGUMENTS;
  }

  // Check allowed input length
  uint8_t realBytes = srcLength % NO_CHECK_BYTES;
  if (0 != realBytes && 0 != (realBytes % BASE8_BIT_LENGTH)) {
    return BASEX_SRCERROR;
  }
  // Set outputlength and check overflow

  uint32_t outputLength = (srcLength / NO_CHECK_BYTES * BASE8_BIT_LENGTH) + realBytes / BASE8_BIT_LENGTH;

  uint8_t checkBits = realBytes / BASE8_BIT_LENGTH;

  if (outputLength > decodedBytesSize) {
    return BASEX_OVERFLOW;
  }

  // Run algorithm
  uint32_t srcPos = 0;
  uint32_t outPos = 0;
  uint16_t carry = 0;
  uint8_t carryLength = 0;
  uint32_t numberOfBits = 0;
  uint8_t lastBitNumber = 0;

  for (; outPos < outputLength; outPos++) {
    for (uint8_t i = 0; i < (BASE8_BIT_LENGTH - carryLength / 2); i++, srcPos++) {
      carry = carry << 3;
      lastBitNumber = (srcNumbers[srcPos] & 0x07);
      numberOfBits += baseNumberOfBits[lastBitNumber];
      carry |= lastBitNumber;
    }
    carryLength = (carryLength + 1) % BASE8_BIT_LENGTH;
    decodedBytes[outPos] = (carry >> carryLength);
    carry &= (0x3 >> (2 - carryLength));
  }
  *decodedLength = outputLength;
  if (checkBits) {
    numberOfBits -= baseNumberOfBits[lastBitNumber];
    if (carry != numberOfBits % (2 * checkBits)) {
      return BASEX_SRCERROR;
    }
  }
  return BASEX_OK;
}