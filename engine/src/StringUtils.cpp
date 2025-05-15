#include "enginecore/utils/StringUtils.h"

const UTILS_NAMESPACE::string::utf_t UTILS_NAMESPACE::string::utf_t::utf[] = {
    /* mask             lead              beg      end     bits */
    {(char)0b00111111, (char)0b10000000, 0, 0, 6},
    {(char)0b01111111, (char)0b00000000, 0000, 0177, 7},
    {(char)0b00011111, (char)0b11000000, 0200, 03777, 5},
    {(char)0b00001111, (char)0b11100000, 04000, 0177777, 4},
    {(char)0b00000111, (char)0b11110000, 0200000, 04177777, 3},
    {0, 0, 0, 0, 0},
};

const std::set<char> UTILS_NAMESPACE::string::utf_t::escape_set =
{
    '\n',
    '\r',
    '\t',
    '\f',
    '\b',
    '"',
    '\\'
};

uint_t UTILS_NAMESPACE::string::utf8_len(ubyte_t cp)
{
    if ((cp & 0x80) == 0)
    {
        return 1;
    }
    if ((cp & 0xE0) == 0xC0)
    {
        return 2;
    }
    if ((cp & 0xF0) == 0xE0)
    {
        return 3;
    }
    if ((cp & 0xF8) == 0xF0)
    {
        return 4;
    }
    throw std::runtime_error("utf8 decode error");
}

uint32_t UTILS_NAMESPACE::string::decode_utf8(uint_t& size, const char* chr)
{
    size = utf8_len(*chr);
    int shift = utf_t::utf[0].bits_stored * (size - 1);
    uint32_t code = (*chr++ & utf_t::utf[size].mask) << shift;

    for (uint_t i = 1; i < size; ++i, ++chr)
    {
        shift -= utf_t::utf[0].bits_stored;
        code |= ((char)*chr & utf_t::utf[0].mask) << shift;
    }
    return code;
}