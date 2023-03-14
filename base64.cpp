#include "base64.hpp"

std::string base64_encode(uint8_t const *buf, size_t bufLen)
{
    static const std::string base64_chars = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
    std::string b64;
    uint8_t arr3[3];
    uint8_t arr4[4];
    int i = 0;
    while (bufLen--)
    {
        arr3[i++] = *(buf++);
        if (i == 3)
        {
            arr4[0] = (arr3[0] & 0xfc) >> 2;
            arr4[1] = ((arr3[0] & 0x03) << 4) | ((arr3[1] & 0xf0) >> 4);
            arr4[2] = ((arr3[1] & 0x0f) << 2) | ((arr3[2] & 0xc0) >> 6);
            arr4[3] = arr3[2] & 0x3f;
            for (i = 0; i < 4; ++i)
            {
                b64 += base64_chars[arr4[i]];
            }
            i = 0;
        }
    }
    if (i != 0)
    {
        for (int j = i; j < 3; ++j)
        {
            arr3[j] = 0;
        }
        arr4[0] = (arr3[0] & 0xfc) >> 2;
        arr4[1] = ((arr3[0] & 0x03) << 4) | ((arr3[1] & 0xf0) >> 4);
        arr4[2] = ((arr3[1] & 0x0f) << 2) | ((arr3[2] & 0xc0) >> 6);
        arr4[3] = arr3[2] & 0x3f;
        for (int j = 0; j <= i; ++j)
        {
            b64 += base64_chars[arr4[j]];
        }
        while (i++ < 3)
        {
            b64 += '=';
        }
    }
    return b64;
}
