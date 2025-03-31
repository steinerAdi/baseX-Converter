/**
 * @file baseX_converter.h
 * @author Adrian STEINER (steia19@bfh.ch)
 * @brief Converter to convert bytes to base 8, 16 and 32 conversion.
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

#ifndef BASEX_CONVERTER_H
#define BASEX_CONVERTER_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

typedef enum {
  BASEX_OK = 0,
  BASEX_ARGUMENTS,
  BASEX_OVERFLOW,
  BASEX_ERROR
} baseX_returnType;

baseX_returnType base8_encodeBytes(
    uint8_t *converter,
    uint32_t convertedSize,
    const uint8_t *srcBytes,
    uint32_t srcBytesSize);

baseX_returnType base8_decodeString(
    uint8_t *decodedBytes,
    uint32_t decodedBytesSize,
    const uint8_t *srcString);

baseX_returnType base8_decodeNum(
    uint8_t *decodedBytes,
    uint32_t decodedBytesSize,
    const uint8_t *srcNumbers,
    const uint32_t srcLength);

#ifdef __cplusplus
}
#endif

#endif /* BASEX_CONVERTER_H */