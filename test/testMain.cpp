#define CATCH_CONFIG_MAIN
#include <catch2/catch_all.hpp>

#include <base64.h>


TEST_CASE("Base64 encoding and decoding", "[base64]") {
    
    std::string str = "hello";
    std::vector<unsigned char> data(str.size());

    std::copy(str.begin(), str.end(), data.begin());
    std::string encoded = base64_encode(data);
    auto decoded = base64_decode(encoded);

    REQUIRE(decoded == data);
}
