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

baseX_returnType base8_encodeBytes(
    uint8_t *converter,
    uint32_t convertedSize,
    const uint8_t *srcBytes,
    uint32_t srcBytesSize);

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
    uint32_t decodedBytesSize,
    const uint8_t *srcNumbers,
    const uint32_t srcLength) {

  if (NULL == decodedBytes || NULL == srcNumbers) {
    return BASEX_ARGUMENTS;
  }

  uint32_t expectedLength = srcLength * 8 / BASE_BIT_LENGTH;
  if (expectedLength > decodedBytesSize) {
    return BASEX_OVERFLOW;
  }

  return BASEX_OK;
}