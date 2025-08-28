[![Test Status](https://github.com/steinerAdi/baseX-Converter/actions/workflows/ci.yml/badge.svg)](https://github.com/steinerAdi/baseX-Converter/actions/workflows/ci.yml)[![codecov](https://codecov.io/gh/steinerAdi/baseX-Converter/graph/badge.svg?token=NNY8ENLEP7)](https://codecov.io/gh/steinerAdi/baseX-Converter)

# Base X converter

Coverts base-8, base-16, base-32 to byte array and vice-versa. 

## About The Project

Build to convert byte patterns to base-X conversion.
- Base-8:   
Can be used to enter a byte with a basic keyboard.
The numbers 1-8 are used.
- Base-16:   
Is a half byte and needs no padding bit.
It can be used on a hex keyboard with characters ``0-9 and a-f/A-F``. 
- Base-32:   
Most used for secrets in cryptographic as it can be entered with a basic keyboard.
The used characters are``A-Z and 2-7``.
For padding, the character ``=`` is used.
- Base-64:   
It increases the base-32 with lowercase letters, the full decimal digits and two special characters.
It can also be entered with the basic keyboard.   
Note: Currently not implemented.

### Build With
- [C Unity Tests](https://github.com/ThrowTheSwitch/Unity)
- GNU Make v4.3
- gcc v13.3.0
- [Codecov](https://about.codecov.io/)
- LCOV version 2.0-1

## Getting Started

### Installation
Include the source and header files into your project.
The header files are located in the [inc](inc/) directory.
The source files are located in the [src](src/) directory.

### Base-8 Conversion
Implemented and tested.
Include the [inc/base8_converter.h](inc/base8_converter.h) header file.
Do not forget to compile the file [src/base8_converter.c](src/base8_converter.c) for using these functions.

### Base-16 Conversion
Implemented and tested.
Include the [inc/base16_converter.h](inc/base16_converter.h) header file.
See the doxygen comments for ``base16_decodeString`` and ``base16_encodeBytes`` functions.
Do not forget to compile the file [src/base16_converter.c](src/base16_converter.c) for using these functions.

### Base-32 Conversion
Implemented and tested.
Include the [inc/base32_converter.h](inc/base32_converter.h) header file.
See the doxygen comments for ``base32_decodeString`` and ``base32_encodeBytes`` functions.
Do not forget to compile the file [src/base32_converter.c](src/base32_converter.c) for using these functions.

### Base-64 Conversion
!TODO

## Usage
Converter to read and write byte data with different bases.

## License
Distributed under the GNU general public license.
See [LICENSE](LICENSE) for more information.

## Authors
- Adrian STEINER (adi.steiner@hotmail.ch)

## Acknowledgments
