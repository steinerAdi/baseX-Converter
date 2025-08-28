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

#include "base16_converter.h"
#include "base32_converter.h"
#include "base8_converter.h"
#include "unity.h"
#include <string.h>

void setUp(void)
{
} // Empty needed definition
void tearDown(void)
{
} // Empty needed definition

#define BYTESTREAM_SIZE (32)
#define BUFFER_SIZE (3 * BYTESTREAM_SIZE)

typedef struct {
  uint8_t byteStream[BYTESTREAM_SIZE];
  uint32_t length;
  char baseAsString[BUFFER_SIZE];
  uint8_t baseNumerical[BUFFER_SIZE];
} baseX_testData;

baseX_testData base8_data[] = {
    {.byteStream = {0x00},
     .length = 1,
     .baseAsString = "111",
     .baseNumerical = {0, 0, 0}},
    {.byteStream = {0x3F},
     .length = 1,
     .baseAsString = "287",
     .baseNumerical = {1, 7, 6}},
    {.byteStream = {0xA5, 0xB3},
     .length = 2,
     .baseAsString = "624425",
     .baseNumerical = {5, 1, 3, 3, 1, 4}},
    {.byteStream = {0xC9, 0x4F, 0x1A},
     .length = 3,
     .baseAsString = "73358543",
     .baseNumerical = {6, 2, 2, 4, 7, 4, 3, 2}},
    {.byteStream = {0x65},
     .length = 1,
     .baseAsString = "424",
     .baseNumerical = {3, 1, 3}},
    {.byteStream = {0x42, 0x81, 0x7F, 0x11, 0x0A, 0xB8, 0x65},
     .length = 7,
     .baseAsString = "3161168815316381423",
     .baseNumerical = {2, 0, 5, 0, 0, 5, 7, 7, 0, 4, 2, 0, 5, 2, 7, 0, 3, 1,
                       2}},
    {.byteStream = {0xAA, 0xBB, 0xCC, 0xDD, 0xEE, 0xFF, 0x11, 0x22, 0x33},
     .length = 9,
     .baseAsString = "636468257847848815332174",
     .baseNumerical = {5, 2, 5, 3, 5, 7, 1, 4, 6, 7, 3, 6,
                       7, 3, 7, 7, 0, 4, 2, 2, 1, 0, 6, 3}}};

baseX_testData base16_data[] = {
    {.byteStream = {'H', 'e', 'l', 'l', 'o'},
     .length = 5,
     .baseAsString = "48656C6C6F",
     .baseNumerical = {4, 8, 6, 5, 6, 12, 6, 12, 6, 15}},
    {.byteStream = {'W', 'o', 'r', 'l', 'd'},
     .length = 5,
     .baseAsString = "576F726C64",
     .baseNumerical = {5, 7, 6, 15, 7, 2, 6, 12, 6, 4}},
    {.byteStream = {'A', 'B', 'C'},
     .length = 3,
     .baseAsString = "414243",
     .baseNumerical = {4, 1, 4, 2, 4, 3}},
    {.byteStream = {0x00, 0xFF, 0x10},
     .length = 3,
     .baseAsString = "00FF10",
     .baseNumerical = {0, 0, 15, 15, 1, 0}},
    {.byteStream = {' ', '\n', '\t'},
     .length = 3,
     .baseAsString = "200A09",
     .baseNumerical = {2, 0, 0, 10, 0, 9}},
    {.byteStream = {0xDE, 0xAD, 0xBE, 0xEF},
     .length = 4,
     .baseAsString = "DEADBEEF",
     .baseNumerical = {13, 14, 10, 13, 11, 14, 14, 15}},
    {.byteStream = {'1', '2', '3', '4', '5', '6', '7', '8', '9', '0'},
     .length = 10,
     .baseAsString = "31323334353637383930",
     .baseNumerical = {3, 1, 3, 2, 3, 3, 3, 4, 3, 5,
                       3, 6, 3, 7, 3, 8, 3, 9, 3, 0}}};

baseX_testData base32_data[] = {
    {
        // Single byte
        .byteStream = {0x66}, // ASCII 'f'
        .length = 1,
        .baseAsString = "MY======", // base32 of 'f'
        .baseNumerical = {12, 24}   // M=12, Y=24 (example values)
    },
    {
        // "foo"
        .byteStream = {0x66, 0x6f, 0x6f}, // "foo"
        .length = 3,
        .baseAsString = "MZXW6===",
        .baseNumerical = {12, 25, 23, 22} // M=12, Z=25, X=23, W=22 (example)
    },
    {// "foobar"
     .byteStream = {0x66, 0x6f, 0x6f, 0x62, 0x61, 0x72},
     .length = 6,
     .baseAsString = "MZXW6YTBOI======",
     .baseNumerical = {12, 25, 23, 22, 24, 19, 1, 14}},
    {// All zero bytes
     .byteStream = {0x00, 0x00, 0x00, 0x00, 0x00},
     .length = 5,
     .baseAsString = "AAAAAAAA",
     .baseNumerical = {0, 0, 0, 0, 0, 0, 0, 0}}};

void test_fail_base8_encode(void)
{
  uint8_t buf[BUFFER_SIZE];
  TEST_ASSERT_EQUAL_INT(BASEX_ARGUMENTS, base8_encodeBytes(buf, 0, NULL, 0));
  TEST_ASSERT_EQUAL_INT(BASEX_ARGUMENTS, base8_encodeBytes(NULL, 0, buf, 0));
  TEST_ASSERT_EQUAL_INT(BASEX_OVERFLOW, base8_encodeBytes(buf, 0, buf, 1));
}

void test_base8_encode(void)
{
  uint8_t buf[BUFFER_SIZE];

  for (uint32_t i = 0; i < sizeof(base8_data) / sizeof(base8_data[0]); i++) {
    TEST_ASSERT_EQUAL_INT(BASEX_OK, base8_encodeBytes(buf, BUFFER_SIZE,
                                                      base8_data[i].byteStream,
                                                      base8_data[i].length));
    TEST_ASSERT_EQUAL_UINT8_ARRAY(base8_data[i].baseAsString, buf,
                                  strlen((const char *)buf));
  }
}

void test_fail_base8_decodeNum(void)
{
  uint8_t buf[BUFFER_SIZE];
  uint32_t decodedLength = 0;
  TEST_ASSERT_EQUAL_INT(
      BASEX_ARGUMENTS,
      base8_decodeNum(buf, &decodedLength, BUFFER_SIZE, NULL, BUFFER_SIZE));
  TEST_ASSERT_EQUAL_INT(BASEX_ARGUMENTS,
                        base8_decodeNum(NULL, &decodedLength, 0, buf, 0));
  TEST_ASSERT_EQUAL_INT(BASEX_ARGUMENTS, base8_decodeNum(buf, NULL, 0, buf, 0));
  TEST_ASSERT_EQUAL_INT(BASEX_OVERFLOW, base8_decodeNum(buf, &decodedLength, 1,
                                                        buf, 16)); // Overflow
  TEST_ASSERT_EQUAL_INT(
      BASEX_SRCERROR,
      base8_decodeNum(buf, &decodedLength, 2, buf, 9)); // To much bytes
  TEST_ASSERT_EQUAL_INT(
      BASEX_SRCERROR,
      base8_decodeNum(buf, &decodedLength, 2, buf, 2)); // Not enough bytes
  uint8_t wrongPattern[] = {0x03, 0x00, 0x01};
  TEST_ASSERT_EQUAL_INT(
      BASEX_SRCERROR,
      base8_decodeNum(buf, &decodedLength, 1, wrongPattern,
                      sizeof(wrongPattern))); // Bit pattern wrong
  wrongPattern[0] = 0x0;
  wrongPattern[2] = 0x1;
  TEST_ASSERT_EQUAL_INT(
      BASEX_SRCERROR,
      base8_decodeNum(buf, &decodedLength, 1, wrongPattern,
                      sizeof(wrongPattern))); // Bit pattern wrong
}

void test_base8_decodeNum(void)
{
  uint8_t buf[BUFFER_SIZE];
  uint32_t decodedLength = 0;

  for (uint32_t i = 0; i < sizeof(base8_data) / sizeof(base8_data[0]); i++) {
    TEST_ASSERT_EQUAL_INT(
        (int)BASEX_OK,
        (int)base8_decodeNum(
            buf, &decodedLength, BUFFER_SIZE, base8_data[i].baseNumerical,
            (const uint32_t)strlen((const char *)base8_data[i].baseAsString)));
    TEST_ASSERT_EQUAL_UINT8_ARRAY(base8_data[i].byteStream, buf, decodedLength);
  }
}

void test_fail_base8_stringToNum(void)
{
  uint8_t buf[BUFFER_SIZE];
  TEST_ASSERT_EQUAL_INT(BASEX_ARGUMENTS, base8_stringToNum(NULL, "0"));
  TEST_ASSERT_EQUAL_INT(BASEX_ARGUMENTS, base8_stringToNum(buf, NULL));
  TEST_ASSERT_EQUAL_INT(BASEX_SRCERROR, base8_stringToNum(buf, "0"));
  TEST_ASSERT_EQUAL_INT(BASEX_ARGUMENTS, base8_stringToNum(buf, ""));
}

void test_base8_stringToNum(void)
{
  uint8_t buf[BUFFER_SIZE];
  for (uint32_t i = 0; i < sizeof(base8_data) / sizeof(base8_data[0]); i++) {
    TEST_ASSERT_EQUAL_INT(BASEX_OK,
                          base8_stringToNum(buf, base8_data[i].baseAsString));
    TEST_ASSERT_EQUAL_UINT8_ARRAY(base8_data[i].baseNumerical, buf,
                                  strlen(base8_data[i].baseAsString));
  }
}
void test_fail_base16_decodeString(void)
{
  uint8_t decoded[BUFFER_SIZE];
  uint32_t destLength;
  /* Argument errors*/
  TEST_ASSERT_EQUAL_INT(BASEX_ARGUMENTS, base16_decodeString(NULL, &destLength,
                                                             BUFFER_SIZE, "2"));
  TEST_ASSERT_EQUAL_INT(BASEX_ARGUMENTS,
                        base16_decodeString(decoded, NULL, BUFFER_SIZE, "2"));
  TEST_ASSERT_EQUAL_INT(
      BASEX_ARGUMENTS,
      base16_decodeString(decoded, &destLength, BUFFER_SIZE, NULL));

  /* Src errors */
  TEST_ASSERT_EQUAL_INT(
      BASEX_SRCERROR,
      base16_decodeString(decoded, &destLength, BUFFER_SIZE, ""));
  TEST_ASSERT_EQUAL_INT(
      BASEX_SRCERROR,
      base16_decodeString(decoded, &destLength, BUFFER_SIZE, "A"));
  TEST_ASSERT_EQUAL_INT(
      BASEX_SRCERROR,
      base16_decodeString(decoded, &destLength, BUFFER_SIZE, "AZ"));
  /* Overflow */
  TEST_ASSERT_EQUAL_INT(BASEX_OVERFLOW,
                        base16_decodeString(decoded, &destLength, 1, "AAAA"));
  return;
}

void test_base16_decodeString(void)
{
  uint8_t decoded[BUFFER_SIZE];
  uint32_t decodedLength = 0;
  for (uint32_t i = 0; i < sizeof(base16_data) / sizeof(base16_data[0]); i++) {
    TEST_ASSERT_EQUAL_INT(
        BASEX_OK, base16_decodeString(decoded, &decodedLength, BUFFER_SIZE,
                                      base16_data[i].baseAsString));
    TEST_ASSERT_EQUAL_UINT8_ARRAY(base16_data[i].byteStream, decoded,
                                  base16_data[i].length);
    TEST_ASSERT_EQUAL_UINT32(base16_data[i].length, decodedLength);
  }
  TEST_ASSERT_EQUAL_INT(BASEX_OK, base16_decodeString(decoded, &decodedLength,
                                                      BUFFER_SIZE, "ff"));
  const uint8_t lowData[] = {0xff};
  TEST_ASSERT_EQUAL_UINT8_ARRAY(lowData, decoded, 1);
  TEST_ASSERT_EQUAL_UINT32(1, decodedLength);
}

void test_fail_base16_encodeBytes(void)
{
  uint8_t decoded[BUFFER_SIZE];
  uint32_t destLength;
  const uint8_t *correctString = "Hello";
  /* Argument errors*/
  TEST_ASSERT_EQUAL_INT(BASEX_ARGUMENTS,
                        base16_encodeBytes(NULL, BUFFER_SIZE, correctString,
                                           strlen(correctString)));
  TEST_ASSERT_EQUAL_INT(
      BASEX_ARGUMENTS,
      base16_encodeBytes(decoded, BUFFER_SIZE, NULL, strlen(correctString)));

  /* Overflow */
  TEST_ASSERT_EQUAL_INT(
      BASEX_OVERFLOW,
      base16_encodeBytes(decoded, 1, correctString, strlen(correctString)));
  return;
}

void test_base16_encodeBytes(void)
{
  char encoded[BUFFER_SIZE];
  for (uint32_t i = 0; i < sizeof(base16_data) / sizeof(base16_data[0]); i++) {
    TEST_ASSERT_EQUAL_INT(BASEX_OK,
                          base16_encodeBytes(encoded, BUFFER_SIZE,
                                             base16_data[i].byteStream,
                                             base16_data[i].length));
    TEST_ASSERT_EQUAL_CHAR_ARRAY(base16_data[i].baseAsString, encoded,
                                 strlen(base16_data[i].baseAsString));
    TEST_ASSERT_EQUAL_UINT32(strlen(base16_data[i].baseAsString),
                             strlen(encoded));
  }
}

void test_fail_base32_decodeString(void)
{
  uint8_t decoded[BUFFER_SIZE];
  uint32_t destLength;
  TEST_ASSERT_EQUAL_INT(BASEX_ARGUMENTS, base32_decodeString(NULL, &destLength,
                                                             BUFFER_SIZE, "2"));
  TEST_ASSERT_EQUAL_INT(BASEX_ARGUMENTS,
                        base32_decodeString(decoded, NULL, BUFFER_SIZE, "2"));
  TEST_ASSERT_EQUAL_INT(BASEX_SRCERROR,
                        base32_decodeString(decoded, &destLength, BUFFER_SIZE,
                                            "1")); // Character not allowed
  TEST_ASSERT_EQUAL_INT(
      BASEX_SRCERROR,
      base32_decodeString(decoded, &destLength, BUFFER_SIZE,
                          "ABC=======")); // not allowed 7 paddings
  TEST_ASSERT_EQUAL_INT(
      BASEX_SRCERROR,
      base32_decodeString(decoded, &destLength, BUFFER_SIZE,
                          "ABCD=====")); // not allowed 5 paddings
  TEST_ASSERT_EQUAL_INT(
      BASEX_SRCERROR,
      base32_decodeString(decoded, &destLength, BUFFER_SIZE,
                          "ABCDE====")); // not allowed 4> paddings
  TEST_ASSERT_EQUAL_INT(
      BASEX_SRCERROR,
      base32_decodeString(decoded, &destLength, BUFFER_SIZE,
                          "ABCDEFG==")); // not allowed 2> paddings

  TEST_ASSERT_EQUAL_INT(
      BASEX_SRCERROR,
      base32_decodeString(decoded, &destLength, BUFFER_SIZE,
                          "ABCDEFGH==")); // Unnecessary paddings at the end

  TEST_ASSERT_EQUAL_INT(
      BASEX_SRCERROR, base32_decodeString(decoded, &destLength, BUFFER_SIZE,
                                          "AB=C=")); // Padding only at the end
  TEST_ASSERT_EQUAL_INT(
      BASEX_SRCERROR,
      base32_decodeString(decoded, &destLength, BUFFER_SIZE, ""));
  TEST_ASSERT_EQUAL_INT(BASEX_OVERFLOW,
                        base32_decodeString(decoded, &destLength, 1, "ABC"));
}

void test_base32_decodeString(void)
{
  uint8_t decoded[BUFFER_SIZE];
  uint32_t decodedLength = 0;
  for (uint32_t i = 0; i < sizeof(base32_data) / sizeof(base32_data[0]); i++) {
    TEST_ASSERT_EQUAL_INT(
        BASEX_OK, base32_decodeString(decoded, &decodedLength, BUFFER_SIZE,
                                      base32_data[i].baseAsString));
    TEST_ASSERT_EQUAL_UINT8_ARRAY(base32_data[i].byteStream, decoded,
                                  base32_data[i].length);
    TEST_ASSERT_EQUAL_UINT32(base32_data[i].length, decodedLength);
  }
}

void test_fail_base32_encodeBytes(void)
{
  char encoded[BUFFER_SIZE];
  TEST_ASSERT_EQUAL_INT(
      BASEX_ARGUMENTS,
      base32_encodeBytes(NULL, BUFFER_SIZE, (const uint8_t *)"000", 3));
  TEST_ASSERT_EQUAL_INT(BASEX_ARGUMENTS,
                        base32_encodeBytes(encoded, BUFFER_SIZE, NULL, 3));
  TEST_ASSERT_EQUAL_INT(
      BASEX_OVERFLOW,
      base32_encodeBytes(encoded, 2, (const uint8_t *)"000", 3)); // Overflow
}

void test_base32_encodeBytes(void)
{
  char encoded[BUFFER_SIZE];
  for (uint32_t i = 0; i < sizeof(base32_data) / sizeof(base32_data[0]); i++) {
    TEST_ASSERT_EQUAL_INT(BASEX_OK,
                          base32_encodeBytes(encoded, BUFFER_SIZE,
                                             base32_data[i].byteStream,
                                             base32_data[i].length));
    TEST_ASSERT_EQUAL_CHAR_ARRAY(base32_data[i].baseAsString, encoded,
                                 strlen(base32_data[i].baseAsString));
    TEST_ASSERT_EQUAL_UINT32(strlen(base32_data[i].baseAsString),
                             strlen(encoded));
  }
}

int main(void)
{
  UNITY_BEGIN();
  // Base 8 Tests
  RUN_TEST(test_fail_base8_encode);
  RUN_TEST(test_base8_encode);
  RUN_TEST(test_fail_base8_decodeNum);
  RUN_TEST(test_base8_decodeNum);
  RUN_TEST(test_fail_base8_stringToNum);
  RUN_TEST(test_base8_stringToNum);

  // Base 16 Tests
  RUN_TEST(test_fail_base16_decodeString);
  RUN_TEST(test_base16_decodeString);
  RUN_TEST(test_fail_base16_encodeBytes);
  RUN_TEST(test_base16_encodeBytes);

  // Base 32 Tests
  RUN_TEST(test_fail_base32_decodeString);
  RUN_TEST(test_base32_decodeString);
  RUN_TEST(test_fail_base32_encodeBytes);
  RUN_TEST(test_base32_encodeBytes);
  return UNITY_END();
}