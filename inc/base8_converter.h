/**
 * @file base8_converter.h
 * @author Adrian STEINER (adi.steiner@hotmail.ch)
 * @brief Converter to convert bytes to base 8 and vis-versa.
 * @version 0.1
 * @date 29-07-2025
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

#ifndef BASE8_CONVERTER_H
#define BASE8_CONVERTER_H

#ifdef __cplusplus
extern "C" {
#endif

#include "baseX_types.h"
#include <stdint.h>

#define BASE8_BIT_LENGTH (3)
#define BASE8_STARTCHAR ('1')
#define BASE8_ENDCHAR ('8')

/**
 * @brief Encodes a byte array into a base8-encoded string.
 *
 * This function converts the input byte array (`srcBytes`) into a base8-encoded
 * string and stores the result in `encodedString`.
 *
 * @param[out] encodedString Buffer to store the base8-encoded output string.
 * @param[in] encodedStringSize Size of the output buffer in bytes.
 * @param[in] srcBytes Pointer to the input byte array to encode.
 * @param[in] srcBytesSize Length of the input byte array in bytes.
 * @return baseX_returnType Status code.
 */
baseX_returnType base8_encodeBytes(
    uint8_t *encodedString,
    uint32_t encodedStringSize,
    const uint8_t *srcBytes,
    uint32_t srcBytesSize);

/**
 * @brief Converts a base8-encoded string into a numeric representation.
 *
 * This function parses a base8-encoded string and converts it into a numeric
 * byte array representation.
 *
 * @param[out] number Buffer to store the resulting numeric representation.
 * @param[in] srcString Null-terminated base8-encoded input string.
 * @return baseX_returnType Status code.
 */
baseX_returnType base8_stringToNum(
    uint8_t *number,
    const char *srcString);

/**
 * @brief Decodes a base8-encoded numeric array into its original byte form.
 *
 * This function takes a base8-encoded numeric array and decodes it into the
 * original byte array, storing the result in `decodedBytes`.
 *
 * @param[out] decodedBytes Buffer to store the decoded byte output.
 * @param[out] decodedLength Pointer to a variable that will hold the length of the decoded output.
 * @param[in] decodedBytesSize Size of the output buffer in bytes.
 * @param[in] srcNumbers Input array containing base8-encoded numeric values.
 * @param[in] srcLength Length of the input numeric array.
 * @return baseX_returnType Status code.
 */
baseX_returnType base8_decodeNum(
    uint8_t *decodedBytes,
    uint32_t *decodedLength,
    uint32_t decodedBytesSize,
    const uint8_t *srcNumbers,
    const uint32_t srcLength);

#ifdef __cplusplus
}
#endif

#endif /* BASE8_CONVERTER_H */