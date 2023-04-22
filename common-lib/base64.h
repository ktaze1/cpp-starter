#pragma once

#include <string>
#include <vector>
#include <array>


std::string base64_encode(const std::vector<unsigned char>& data);


std::vector<unsigned char> base64_decode(const std::string& input);