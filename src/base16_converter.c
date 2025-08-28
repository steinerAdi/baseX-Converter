/**
 * @file base16_converter.c
 * @author Adrian STEINER (adi.steiner@hotmail.ch)
 * @brief Base16 byte converter.
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

#include "base16_converter.h"

#define BASE16_CHAR_PER_BYTE (2)

/**
 * @brief Returns the decimal number of the hexadecimal character.
 *
 * Allowed characters are 0-9, a-f and A-F
 *
 * @param c The character to convert
 * @return int8_t The decimal number of the character, -1 in case of an error
 */
int8_t hexCharToInt(char c);

baseX_returnType base16_decodeString(uint8_t *decodedBytes,
                                     uint32_t *decodedLength,
                                     uint32_t decodedBytesSize,
                                     const char *srcString)
{
  if (!decodedBytes || !decodedLength || !srcString) {
    return BASEX_ARGUMENTS;
  }
  uint32_t srcLength = (uint32_t)strlen(srcString);
  if (0 == srcLength) {
    return BASEX_SRCERROR;
  }

  *decodedLength = srcLength / BASE16_CHAR_PER_BYTE;

  if (decodedLength > decodedBytesSize) {
    return BASEX_OVERFLOW;
  }

  for (uint32_t i = 0; i < srcLength; i += 2) {
    int8_t high = hexCharToInt(srcString[i++]);
    int8_t low = hexCharToInt(srcString[i]);
    if (high == -1 || low == -1) {
      return BASEX_SRCERROR; // Src error, not allowed character letter
    }
    *decodedBytes++ = (high << 4) | low;
  }
  return BASEX_OK; // success
}

baseX_returnType base16_encodeBytes(char *encodedString,
                                    uint32_t encodedSize,
                                    const uint8_t *srcBytes,
                                    uint32_t srcLength)
{
  if (!encodedString || !srcBytes) {
    return BASEX_ARGUMENTS;
  }
  if (srcLength % BASE16_CHAR_PER_BYTE) {
    return BASEX_SRCERROR;
  }
  uint32_t outputLength = srcLength * BASE16_CHAR_PER_BYTE;
  if (encodedSize < (outputLength + 1)) { // +1 for null terminator
    return BASEX_OVERFLOW;
  }
  const char hexDigits[16] = "0123456789ABCDEF";
  for (uint32_t i = 0; i < srcLength; i++) {
    char c = srcBytes[i];
    *encodedString++ = hexDigits[(c >> 4) & 0xF];
    *encodedString++ = hexDigits[c & 0xF];
  }
  *encodedString = '\0';
  return BASEX_OK;
}

int8_t hexCharToInt(char c)
{
  if ('0' <= c && c <= '9') {
    return c - '0';
  }
  if ('A' <= c && c <= 'F') {
    return c - 'A' + 10;
  }
  if ('a' <= c && c <= 'f') {
    return c - 'a' + 10;
  }
  return -1; // invalid character
}