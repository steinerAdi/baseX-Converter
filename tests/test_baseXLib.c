/**
 * @file test_baseXLib.c
 * @author Adrian STEINER (steia19@bfh.ch)
 * @brief test application for the baseX library
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
#include "unity.h"
#include <string.h>

void setUp(void) {
} // Empty needed definition
void tearDown(void) {
} // Empty needed definition

#define BYTESTREAM_SIZE (32)
#define BUFFER_SIZE (3 * BYTESTREAM_SIZE)

struct {
  uint8_t byteStream[BYTESTREAM_SIZE];
  uint32_t length;
  uint8_t base8String[BUFFER_SIZE];
  uint8_t base8Num[BUFFER_SIZE];
} base8Data[] = {
    {.byteStream = {0x00},
        .length = 1,
        .base8String = "111",
        .base8Num = {0, 0, 0}},
    {.byteStream = {0x3F},
        .length = 1,
        .base8String = "287",
        .base8Num = {1, 7, 6}},
    {.byteStream = {0xA5, 0xB3},
        .length = 2,
        .base8String = "624425",
        .base8Num = {5, 1, 3, 3, 1, 4}},
    {.byteStream = {0xC9, 0x4F, 0x1A},
        .length = 3,
        .base8String = "73358543",
        .base8Num = {6, 2, 2, 4, 7, 4, 3, 2}},
    {.byteStream = {0x65},
        .length = 1,
        .base8String = "424",
        .base8Num = {3, 1, 3}},
    {.byteStream = {0x42, 0x81, 0x7F, 0x11, 0x0A, 0xB8, 0x65},
        .length = 7,
        .base8String = "3161168815316381423",
        .base8Num = {
            2, 0, 5, 0, 0, 5, 7, 7,
            0, 4, 2, 0, 5, 2, 7, 0,
            3, 1, 2}},
    {.byteStream = {0xAA, 0xBB, 0xCC, 0xDD, 0xEE, 0xFF, 0x11, 0x22, 0x33}, .length = 9, .base8String = "636468257847848815332174", .base8Num = {5, 2, 5, 3, 5, 7, 1, 4, 6, 7, 3, 6, 7, 3, 7, 7, 0, 4, 2, 2, 1, 0, 6, 3}},
    // {.byteStream = {0xF3, 0xE7, 0xD1, 0xA4, 0x5B, 0x92, 0x3C, 0xEF, 0x01, 0x7A, 0xA9, 0x4D, 0x82, 0xC7, 0x5F, 0x3B, 0xD4, 0x9E, 0x8A, 0x6F, 0xB1, 0xC0, 0xFA, 0x27, 0x13, 0x99, 0xE8, 0x4C, 0x21, 0x7D, 0x5A},
    //     .length = 5,
    //     .base8String = "287",
    //     .base8Num = {7, 4, 7, 6, 3, 5, 1, 5, 1, 2, 2, 6, 7, 1, 2, 3, 6, 0, 3, 5, 7, 5, 0, 1, 7, 2, 5, 1, 2, 3, 2, 3,
    //         0, 2, 6, 1, 7, 5, 3, 7, 7, 5, 2, 3, 6, 2, 1, 2, 6, 7, 3, 6, 2, 6, 0, 1, 7, 5, 4, 3, 4, 4, 7, 7,
    //         5, 6, 5, 4, 3, 4, 0}},
};

void test_fail_base8_encode(void) {
  uint8_t buf[BUFFER_SIZE];
  TEST_ASSERT_EQUAL_INT(BASEX_ARGUMENTS, base8_encodeBytes(NULL, 0, buf, 0));
  TEST_ASSERT_EQUAL_INT(BASEX_ARGUMENTS, base8_encodeBytes(buf, 0, NULL, 0));
  TEST_ASSERT_EQUAL_INT(BASEX_OVERFLOW, base8_encodeBytes(buf, 0, buf, 1));
}

void test_base8_encode(void) {
  uint8_t buf[BUFFER_SIZE];

  for (uint32_t i = 0; i < sizeof(base8Data) / sizeof(base8Data[0]); i++) {
    TEST_ASSERT_EQUAL_INT(BASEX_OK, base8_encodeBytes(buf, BUFFER_SIZE, base8Data[i].byteStream, base8Data[i].length));
    TEST_ASSERT_EQUAL_UINT8_ARRAY(base8Data[i].base8String, buf, strlen((const char *)buf));
  }
}

test_fail_base8_decodeNum(void) {
  uint8_t buf[BUFFER_SIZE];
  uint32_t decodedLength = 0;
  TEST_ASSERT_EQUAL_INT(BASEX_ARGUMENTS, base8_decodeNum(NULL, &decodedLength, BUFFER_SIZE, buf, BUFFER_SIZE));
  TEST_ASSERT_EQUAL_INT(BASEX_ARGUMENTS, base8_decodeNum(buf, NULL, 0, NULL, 0));
  TEST_ASSERT_EQUAL_INT(BASEX_OVERFLOW, base8_decodeNum(buf, &decodedLength, 1, buf, 16));
  TEST_ASSERT_EQUAL_INT(BASEX_SRCERROR, base8_decodeNum(buf, &decodedLength, 2, buf, 9)); // Not enough || to much src bytes
}

test_base8_decodeNum(void) {
  uint8_t buf[BUFFER_SIZE];
  uint32_t decodedLength = 0;

  for (uint32_t i = 0; i < sizeof(base8Data) / sizeof(base8Data[0]); i++) {
    TEST_ASSERT_EQUAL_INT(BASEX_OK, base8_decodeNum(buf, &decodedLength, BUFFER_SIZE, base8Data[i].base8Num, strlen(base8Data[i].base8String)));
    TEST_ASSERT_EQUAL_UINT8_ARRAY(base8Data[i].byteStream, buf, decodedLength);
  }
}

int main(void) {
  UNITY_BEGIN();
  RUN_TEST(test_fail_base8_encode);
  RUN_TEST(test_base8_encode);
  // RUN_TEST(test_fail_base8_decodeNum);
  RUN_TEST(test_base8_decodeNum);
  return UNITY_END();
}