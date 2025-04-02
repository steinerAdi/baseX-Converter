/**
 * @file base8_converter.h
 * @author Adrian STEINER (steia19@bfh.ch)
 * @brief Base 8 byte converter
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

#include "baseX_converter.h"
#include <string.h>

#define BASE_BIT_LENGTH (3)
#define BYTE_BIT_LENGTH (8)

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

uint8_t
carryToAscii(uint16_t carry);

baseX_returnType base8_encodeBytes(
    uint8_t *encodedString,
    uint32_t encodedStringSize,
    const uint8_t *srcBytes,
    uint32_t srcBytesSize) {
  if (NULL == encodedString || NULL == srcBytes) {
    return BASEX_ARGUMENTS;
  }

  // Check needed length
  uint32_t outputLength = srcBytesSize * BYTE_BIT_LENGTH / BASE_BIT_LENGTH;

  uint8_t checkBits = (srcBytesSize) % BASE_BIT_LENGTH;
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
    carry += ((((uint16_t)srcBytes[srcPos]) & UINT8_MAX) << (BYTE_BIT_LENGTH - carryLength));
    for (uint8_t i = 0; i < (2 + (carryLength ? 1 : 0)); i++) {
      uint8_t newBase8Number = carry >> (16 - BASE_BIT_LENGTH);
      numberOfBits += baseNumberOfBits[newBase8Number];
      encodedString[outPos] = newBase8Number + '1';
      outPos++;
      carry = (carry << BASE_BIT_LENGTH);
    }
    if (0 == carryLength) {
      carryLength = 2;
    } else {
      carryLength--;
    }
  }
  // Add one additional number with checkBits
  if (checkBits) {
    encodedString[outPos] = (carry >> (16 - BASE_BIT_LENGTH)) + (numberOfBits % (2 * checkBits)) + '1';
    outPos++;
  }
  encodedString[outPos] = '\0';
  return BASEX_OK;
}

baseX_returnType base8_decodeString(
    uint8_t *decodedBytes,
    uint32_t decodedBytesSize,
    const uint8_t *srcString) {

  if (NULL == srcString) {
    return BASEX_ARGUMENTS;
  }

  uint32_t srcLength = strlen((const char *)srcString);
  for (uint32_t i = 0; i < srcLength; i++) {
    ;
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
  if (0 != srcLength % NO_CHECK_BYTES && 0 != srcLength % BASE_BIT_LENGTH) {
    printf("Src error in length: %u\n", srcLength);
    return BASEX_SRCERROR;
  }
  // Set outputlength and check overflow

  uint32_t outputLength = srcLength / BASE_BIT_LENGTH;

  uint8_t checkBits = (srcLength % NO_CHECK_BYTES) / BASE_BIT_LENGTH;
  // Set special case no checkBits results in one more character
  if (!checkBits) {
    outputLength++;
  }

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
    for (uint8_t i = 0; i < (3 - carryLength / 2); i++, srcPos++) {
      carry = carry << 3;
      lastBitNumber = (srcNumbers[srcPos] & 0x07);
      numberOfBits = baseNumberOfBits[lastBitNumber];
      carry |= lastBitNumber;
    }
    carryLength = (carryLength + 1) % 3;
    decodedBytes[outPos] = (carry >> carryLength);
    carry &= (0x3 >> (2 - carryLength));
  }
  *decodedLength = outputLength;

  if (checkBits) {
    lastBitNumber -= baseNumberOfBits[lastBitNumber];
    if (carry != numberOfBits % (2 * carryLength)) {
      printf("Src error in number of bits: %u\n", numberOfBits);
      return BASEX_SRCERROR;
    }
  }
  return BASEX_OK;
}

uint8_t carryToAscii(uint16_t carry) {
  uint8_t number = (carry >> 13);
  return number + '1';
}