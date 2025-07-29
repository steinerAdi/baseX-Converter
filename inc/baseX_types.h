/**
 * @file baseX_types.h
 * @author Adrian STEINER (adi.steiner@hotmail.ch)
 * @brief BaseX defined types
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

/**
 * @brief Function return state
 *
 */
typedef enum {
  BASEX_OK = 0,    ///< Success
  BASEX_ARGUMENTS, ///< Invalid function arguments
  BASEX_OVERFLOW,  ///< Buffer overflow
  BASEX_SRCERROR,  ///< Invalid baseX input data
  BASEX_ERROR      ///< Unexpected error
} baseX_returnType;

#define BASEX_BYTE_BIT_LENGTH (8)

#ifdef __cplusplus
}
#endif

#endif /* BASEX_CONVERTER_H */