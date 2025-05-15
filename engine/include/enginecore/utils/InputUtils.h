#pragma once
#ifndef UTILS_INPUTUTILS_H_
#define UTILS_MEMORYUTILS_H_

#include <string>

#include "enginecore/core/CoreDefines.h"

enum class Keycode;
enum class Mousecode;

namespace UTILS_NAMESPACE
{
    namespace input
    {
        //void initialize();
        
        Keycode keycode_from(const std::string& name);
        Mousecode mousecode_from(const std::string& name);

        /// @return Key label by keycode
        std::string to_string(Keycode code);
        /// @return Mouse button label by keycode
        std::string to_string(Mousecode code);

        /// @return Key name by keycode
        std::string get_name(Keycode code);
        /// @return Mouse button name by keycode
        std::string get_name(Mousecode code);
    }
}


#endif // !UTILS_INPUTUTILS_H_