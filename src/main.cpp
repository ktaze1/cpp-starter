#include <iostream>
#include <base64.h>

int main() {
    std::string str = "hello";
    std::vector<unsigned char> data(str.size());

    std::copy(str.begin(), str.end(), data.begin());
    std::string encoded = base64_encode(data);

    std::cout << "Encoded: " << encoded << std::endl;

    std::vector<unsigned char> decoded = base64_decode(encoded);

    return 0;
}
