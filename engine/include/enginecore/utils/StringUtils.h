#pragma once
#ifndef UTILS_STRINGUTILS_H_
#define UTILS_STRINGUTILS_H_

#include <string>
#include <vector>
#include <sstream>
#include <set>
#include <concepts>

#include "enginecore/core/CoreDefines.h"

namespace UTILS_NAMESPACE
{
	namespace string
	{
		template<typename T>
		concept IsStdString = requires(T a)
		{
			typename T::value_type;
		};

		template<typename T>
		concept HasPushBack = requires(T t)
		{
            { t.push_back(std::declval<typename T::value_type>()) } -> std::same_as<void>;
		};

        struct utf_t 
        {
            char mask;
            char lead;
            uint32_t beg;
            uint32_t end;
            int bits_stored;

            static const utf_t utf[];
            static const std::set<char> escape_set;
        };

        uint_t utf8_len(ubyte_t cp);

        uint32_t decode_utf8(uint_t& size, const char* chr);

        template<IsStdString STR, class STRVIEW = std::basic_string_view<typename STR::value_type>>
        STR escape(const STRVIEW& s, bool escapeUnicode)
        {
            std::basic_stringstream<typename STR::value_type,
                std::char_traits<typename STR::value_type>,
                std::allocator<typename STR::value_type>> ss;
            // STR('"')
            ss << STR({ 0x22 });
            size_t pos = 0;
            while (pos < s.length()) 
            {
                char c = static_cast<char>(s[pos]);
                if (utf_t::escape_set.find(c) != utf_t::escape_set.end())
                {
                    // STR('\\')
                    ss << STR({ 0x5C });
                    pos++;
                    continue;
                }
                
                if (c & 0x80)
                {
                    uint_t cpsize{};
                    int codepoint = decode_utf8(cpsize, s.data() + pos);
                    if (escapeUnicode) 
                    {
                        // STR("\\u")
                        ss << STR({ 0x5C, 0x75 }) << std::hex << codepoint;
                    }
                    else 
                    {
                        ss << STR(s.data() + pos, cpsize);
                    }
                    pos += cpsize - 1;
                    break;
                }
                if (c < ' ') 
                {
                    ss << "\\" << std::oct << uint_t(ubyte_t(c));
                    break;
                }
                ss << c;

                pos++;
            }
            // STR('"')
            ss << STR({ 0x22 });
            return ss.str();
        }

        template<IsStdString STR>
		STR quote(const STR& s) 
        {
			return escape<STR, std::basic_string_view<typename STR::value_type>>(s, false);
		}

		template<IsStdString STR, HasPushBack RETURNTYPE = std::vector<STR>, class STRVIEW = std::basic_string_view<typename STR::value_type>>
		RETURNTYPE split_at(const STRVIEW& string, const typename STR::value_type& symbol)
		{
			size_t idx = string.find(symbol);
			if (idx == STR::npos) 
			{
				throw std::runtime_error(quote(STR({ symbol })) + " not found");
			}
		    
            std::basic_stringstream<typename STR::value_type,
                std::char_traits<typename STR::value_type>,
                std::allocator<typename STR::value_type>> ss;
            RETURNTYPE result{};    
            STR item{};
            while (std::getline(ss, item, symbol))
            {
                result.push_back(item);
            }

            return result;
		}
	}
}

#endif // !UTILS_STRINGUTILS_H_