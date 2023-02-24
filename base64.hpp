#pragma once
#ifndef __BASE64_ENCODE_HPP__
#define __BASE64_ENCODE_HPP__

#include <cstdlib>
#include <string>

extern std::string base64_encode(uint8_t const *buf, size_t bufLen);

#endif // __BASE64_ENCODE_HPP__
