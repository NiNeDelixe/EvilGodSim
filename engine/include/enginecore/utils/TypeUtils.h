#pragma once
#ifndef UTILS_TYPEUTILS_H_
#define UTILS_TYPEUTILS_H_

#include "enginecore/core/CoreDefines.h"

namespace UTILS_NAMESPACE
{
    namespace type
    {
        template<typename T>
        struct TypeInitial
        {
            static const char value = '?';
        };

        template <> struct TypeInitial<float> { static const char value = 'f'; };
        template <> struct TypeInitial<int> { static const char value = 'i'; };
        template <> struct TypeInitial<unsigned int> { static const char value = 'u'; };
    }
}

#define GET_SYMB(T) UTILS_NAMESPACE::type::TypeInitial<T>::value

#endif // !UTILS_TYPEUTILS_H_