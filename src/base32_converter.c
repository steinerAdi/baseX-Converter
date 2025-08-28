/**
 * @file base32_converter.c
 * @author Adrian STEINER (adi.steiner@hotmail.ch)
 * @brief Base32 byte converter.
 * @version 0.1
 * @date 17-07-2025
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

#include "base32_converter.h"

#include <ctype.h>
#include <string.h>

const char paddingCharacter = '='; ///< Padding character
static const char *base32_alphabet =
    "ABCDEFGHIJKLMNOPQRSTUVWXYZ234567"; ///< used base32 characters listed as an
                                        ///< alphabet

/**
 * @brief Calculates the number of base32 padding characters required for a
 * given input length.
 *
 * @param inputLength Length of the input byte array.
 * @return Number of '=' padding characters (0, 1, 3, 4, or 6).
 */
uint8_t base32_padding(uint32_t inputLength);

baseX_returnType base32_decodeString(uint8_t *decodedBytes,
                                     uint32_t *decodedLength,
                                     uint32_t decodedBytesSize,
                                     const char *srcString)
{

  if (!decodedBytes || !decodedLength || !srcString) {
    return BASEX_ARGUMENTS;
  }

  uint32_t wPos = 0; // Write position
  uint32_t rPos = 0; // Read position
  uint32_t bits = 0; // Number of bits
  uint32_t vbit = 0; // Current bits read

  uint32_t srcLength = (uint32_t)strlen(srcString);

  if (0 == srcLength) {
    return BASEX_SRCERROR;
  }

  while ((rPos < srcLength) || (vbit >= 8)) {
    if (wPos >= decodedBytesSize) {
      return BASEX_OVERFLOW;
    }
    if ((rPos < srcLength) && (vbit < 8)) {
      const char *p;
      char c = srcString[rPos++];

      if (paddingCharacter == c) {
        /* padding character */
        uint8_t expectedPadding = base32_padding(wPos);

        for (size_t i = 1; i < expectedPadding && rPos < srcLength;
             i++, rPos++) {
          // Check only accepted padding bytes
          if (paddingCharacter != srcString[rPos]) {
            return BASEX_SRCERROR;
          }
        }
        if (rPos < srcLength) {
          // To much padding bytes
          return BASEX_SRCERROR;
        }
        break;
      }
      p = strchr(base32_alphabet, toupper(c));
      if (!p) {
        /* invalid character */
        return BASEX_SRCERROR;
      }
      bits = (bits << BASE32_BIT_LENGTH) | (uint32_t)(p - base32_alphabet);
      vbit += BASE32_BIT_LENGTH;
    }
    if (vbit >= 8) {
      decodedBytes[wPos++] = (bits >> (vbit - 8)) & 0xFF;
      vbit -= 8;
    }
  }
  *decodedLength = wPos;
  return BASEX_OK;
}

baseX_returnType base32_encodeBytes(char *encodedString,
                                    uint32_t encodedSize,
                                    const uint8_t *srcBytes,
                                    uint32_t srcLength)
{

  if (!encodedString || !srcBytes)
    return BASEX_ARGUMENTS;

  uint32_t outputLength = ((srcLength + 4) / BASE32_BIT_LENGTH) * 8;
  if (encodedSize < (outputLength + 1)) { // +1 for null terminator
    return BASEX_OVERFLOW;
  }

  uint32_t buffer = 0;
  int bitsLeft = 0;
  uint32_t outIndex = 0;

  for (uint32_t i = 0; i < srcLength; ++i) {
    buffer <<= 8;
    buffer |= srcBytes[i] & 0xFF;
    bitsLeft += 8;

    while (bitsLeft >= BASE32_BIT_LENGTH) {
      encodedString[outIndex++] =
          base32_alphabet[(buffer >> (bitsLeft - BASE32_BIT_LENGTH)) & 0x1F];
      bitsLeft -= BASE32_BIT_LENGTH;
    }
  }

  if (bitsLeft > 0) {
    buffer <<= (BASE32_BIT_LENGTH - bitsLeft);
    encodedString[outIndex++] = base32_alphabet[buffer & 0x1F];
  }

  // Padding
  while (outIndex % 8 != 0) {
    encodedString[outIndex++] = paddingCharacter;
  }

  encodedString[outIndex] = '\0';
  return BASEX_OK;
}

uint8_t base32_padding(uint32_t inputLength)
{
  switch (inputLength % 5) {
  case 0:
    return 0;
  case 1:
    return 6;
  case 2:
    return 4;
  case 3:
    return 3;
  case 4:
    return 1;
  default:
    return 0;
  }
}
