/**
 * @file base16_converter.h
 * @author Adrian STEINER (adi.steiner@hotmail.ch)
 * @brief Converter to convert bytes to base 16 and vis-versa.
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

#ifndef BASE16_CONVERTER_H
#define BASE16_CONVERTER_H

#ifdef __cplusplus
extern "C" {
#endif

#include "baseX_types.h"
#include <stdint.h>

/**
 * @brief Decodes a base16-encoded string into a byte array.
 *
 * This function decodes a base32-encoded string back into its original
 * byte representation based on RFC3548.
 *
 * @param[out] decodedBytes Buffer to store the decoded byte array.
 * @param[out] decodedLength Pointer to store the actual number of decoded
 * bytes.
 * @param[in] decodedBytesSize Size of the output buffer in bytes.
 * @param[in] srcString NULL-terminated base32-encoded input string.
 * @param[in] srcLength the size of srcString
 * @return baseX_returnType Status code.
 */
baseX_returnType base16_decodeString(uint8_t *decodedBytes,
                                     uint32_t *decodedLength,
                                     uint32_t decodedBytesSize,
                                     const char *srcString);

/**
 * @brief Encodes a byte array into a base16-encoded string (RFC 4648).
 *
 * This function converts the input byte array into a base32-encoded string
 * using the standard RFC 4648 alphabet. The output string will be
 * null-terminated.
 *
 * @param[out] encodedString Buffer to store the base32-encoded string.
 * @param[in] encodedSize Size of the output buffer in bytes.
 * @param[in] srcBytes Pointer to the input byte array.
 * @param[in] srcLength Length of the input byte array in bytes.
 * @return baseX_returnType Status code.
 */
baseX_returnType base16_encodeBytes(char *encodedString,
                                    uint32_t encodedSize,
                                    const uint8_t *srcBytes,
                                    uint32_t srcLength);

#ifdef __cplusplus
}
#endif

#endif /* BASE16_CONVERTER_H */