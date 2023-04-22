#include "base64.h"

const static char base64_chars[] =
    "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
    "abcdefghijklmnopqrstuvwxyz"
    "0123456789+/";

std::string base64_encode(const std::vector<unsigned char>& data) {
    size_t len = data.size();
    std::string result(((len + 2) / 3) * 4, '=');
    size_t out_index = 0;

    for (size_t i = 0; i < len;) {
        int a = i < len ? data[i++] : 0;
        int b = i < len ? data[i++] : 0;
        int c = i < len ? data[i++] : 0;

        result[out_index++] = base64_chars[(a >> 2) & 0x3F];
        result[out_index++] = base64_chars[((a << 4) | (b >> 4)) & 0x3F];
        result[out_index++] = base64_chars[((b << 2) | (c >> 6)) & 0x3F];
        result[out_index++] = base64_chars[c & 0x3F];
    }

    return result;
}

std::array<unsigned char, 128> create_base64_decode_table() {
    std::array<unsigned char, 128> table{};
    for (size_t i = 0; i < sizeof(base64_chars) - 1; i++) {
        table[base64_chars[i]] = static_cast<unsigned char>(i);
    }
    return table;
}

std::vector<unsigned char> base64_decode(const std::string& input) {
    static const auto decode_table = create_base64_decode_table();
    std::vector<unsigned char> result;
    size_t len = input.size();
    size_t in_index = 0;

    while (in_index < len) {
        int a = (in_index < len && input[in_index] != '=') ? decode_table[input[in_index++]] : 0;
        int b = (in_index < len && input[in_index] != '=') ? decode_table[input[in_index++]] : 0;
        int c = (in_index < len && input[in_index] != '=') ? decode_table[input[in_index++]] : 0;
        int d = (in_index < len && input[in_index] != '=') ? decode_table[input[in_index++]] : 0;

        result.push_back((a << 2) | (b >> 4));
        if (c != 64) {
            result.push_back((b << 4) | (c >> 2));
            if (d != 64) {
                result.push_back((c << 6) | d);
            }
        }
    }

    // Remove the last byte if it's a padding character
    if (!result.empty() && result.back() == 0) {
        result.pop_back();
    }

    return result;
}
