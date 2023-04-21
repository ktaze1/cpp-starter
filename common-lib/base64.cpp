#include "base64.h"

const std::string base64_chars =
    "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
    "abcdefghijklmnopqrstuvwxyz"
    "0123456789+/";

std::string base64_encode(const std::vector<unsigned char> &data) {
    std::string encoded;
    int bits_collected = 0;
    unsigned int accumulator = 0;
    for (const auto &datum : data) {
        accumulator = (accumulator << 8) | datum;
        bits_collected += 8;
        while (bits_collected >= 6) {
            bits_collected -= 6;
            encoded += base64_chars[(accumulator >> bits_collected) & 0x3F];
        }
    }
    if (bits_collected > 0) {
        accumulator <<= 6 - bits_collected;
        encoded += base64_chars[accumulator & 0x3F];
    }
    while (encoded.size() % 4 != 0) {
        encoded += '=';
    }
    return encoded;
}

std::vector<unsigned char> base64_decode(const std::string &data) {
    std::vector<unsigned char> decoded;
    int bits_collected = 0;
    unsigned int accumulator = 0;
    for (const auto &datum : data) {
        if (datum == '=') {
            break;
        }
        const auto &ch = base64_chars.find(datum);
        if (ch == std::string::npos) {
            continue;
        }
        accumulator = (accumulator << 6) | ch;
        bits_collected += 6;
        if (bits_collected >= 8) {
            bits_collected -= 8;
            decoded.emplace_back((accumulator >> bits_collected) & 0xFF);
        }
    }
    return decoded;
}
