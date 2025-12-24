#pragma once
#ifndef WINDOW_INPUT_H_

#include <string>

#include <GLFW/glfw3.h>

#include "enginecore/core/CoreDefines.h"

#include "enginecore/utils/InputUtils.h"

#include "enginecore/interfaces/IEvent.h"

#ifdef DELETE
#undef DELETE
#endif // DELETE

#ifdef ERROR
#undef ERROR
#endif // ERROR


//#include "enginecore/utils/HandlersList.hpp"

constexpr short KEYS_BUFFER_SIZE = 1036;
constexpr short _MOUSE_KEYS_OFFSET = 1024;

enum class BindType
{
    BIND = 0,
    REBIND = 1
};

/// @brief Represents glfw3 keycode values.
enum class Keycode : int 
{
    SPACE = GLFW_KEY_SPACE,
    APOSTROPHE = GLFW_KEY_APOSTROPHE,
    COMMA = GLFW_KEY_COMMA,
    MINUS = GLFW_KEY_MINUS,
    PERIOD = GLFW_KEY_PERIOD,
    SLASH = GLFW_KEY_SLASH,
    NUM_0 = GLFW_KEY_0,
    NUM_1 = GLFW_KEY_1,
    NUM_2 = GLFW_KEY_2,
    NUM_3 = GLFW_KEY_3,
    NUM_4 = GLFW_KEY_4,
    NUM_5 = GLFW_KEY_5,
    NUM_6 = GLFW_KEY_6,
    NUM_7 = GLFW_KEY_7,
    NUM_8 = GLFW_KEY_8,
    NUM_9 = GLFW_KEY_9,
    SEMICOLON = GLFW_KEY_SEMICOLON,
    EQUAL = GLFW_KEY_EQUAL,
    A = GLFW_KEY_A,
    B = GLFW_KEY_B,
    C = GLFW_KEY_C,
    D = GLFW_KEY_D,
    E = GLFW_KEY_E,
    F = GLFW_KEY_F,
    G = GLFW_KEY_G,
    H = GLFW_KEY_H,
    I = GLFW_KEY_I,
    J = GLFW_KEY_J,
    K = GLFW_KEY_K,
    L = GLFW_KEY_L,
    M = GLFW_KEY_M,
    N = GLFW_KEY_N,
    O = GLFW_KEY_O,
    P = GLFW_KEY_P,
    Q = GLFW_KEY_Q,
    R = GLFW_KEY_R,
    S = GLFW_KEY_S,
    T = GLFW_KEY_T,
    U = GLFW_KEY_U,
    V = GLFW_KEY_V,
    W = GLFW_KEY_W,
    X = GLFW_KEY_X,
    Y = GLFW_KEY_Y,
    Z = GLFW_KEY_Z,
    LEFT_BRACKET = GLFW_KEY_LEFT_BRACKET,
    BACKSLASH = GLFW_KEY_BACKSLASH,
    RIGHT_BRACKET = GLFW_KEY_RIGHT_BRACKET,
    GRAVE_ACCENT = GLFW_KEY_GRAVE_ACCENT,
    ESCAPE = GLFW_KEY_ESCAPE,
    ENTER = GLFW_KEY_ENTER,
    TAB = GLFW_KEY_TAB,
    BACKSPACE = GLFW_KEY_BACKSPACE,
    INSERT = GLFW_KEY_INSERT,
    DELETE = GLFW_KEY_DELETE,
    LEFT = GLFW_KEY_LEFT,
    RIGHT = GLFW_KEY_RIGHT,
    DOWN = GLFW_KEY_DOWN,
    UP = GLFW_KEY_UP,
    PAGE_UP = GLFW_KEY_PAGE_UP,
    PAGE_DOWN = GLFW_KEY_PAGE_DOWN,
    HOME = GLFW_KEY_HOME,
    END = GLFW_KEY_END,
    CAPS_LOCK = GLFW_KEY_CAPS_LOCK,
    NUM_LOCK = GLFW_KEY_NUM_LOCK,
    PRINT_SCREEN = GLFW_KEY_PRINT_SCREEN,
    PAUSE = GLFW_KEY_PAUSE,
    F1 = GLFW_KEY_F1,
    F2 = GLFW_KEY_F2,
    F3 = GLFW_KEY_F3,
    F4 = GLFW_KEY_F4,
    F5 = GLFW_KEY_F5,
    F6 = GLFW_KEY_F6,
    F7 = GLFW_KEY_F7,
    F8 = GLFW_KEY_F8,
    F9 = GLFW_KEY_F9,
    F10 = GLFW_KEY_F10,
    F11 = GLFW_KEY_F11,
    F12 = GLFW_KEY_F12,
    LEFT_SHIFT = GLFW_KEY_LEFT_SHIFT,
    LEFT_CONTROL = GLFW_KEY_LEFT_CONTROL,
    LEFT_ALT = GLFW_KEY_LEFT_ALT,
    LEFT_SUPER = GLFW_KEY_LEFT_SUPER,
    RIGHT_SHIFT = GLFW_KEY_RIGHT_SHIFT,
    RIGHT_CONTROL = GLFW_KEY_RIGHT_CONTROL,
    RIGHT_ALT = GLFW_KEY_RIGHT_ALT,
    RIGHT_SUPER = GLFW_KEY_RIGHT_SUPER,
    MENU = GLFW_KEY_MENU,
    UNKNOWN = GLFW_KEY_UNKNOWN
};

/// @brief Represents glfw3 mouse button IDs.
/// @details There is a subset of glfw3 mouse button IDs.
enum class Mousecode : int 
{
    BUTTON_1 = GLFW_MOUSE_BUTTON_1,  // Left mouse button
    BUTTON_2 = GLFW_MOUSE_BUTTON_2,  // Right mouse button
    BUTTON_3 = GLFW_MOUSE_BUTTON_3,  // Middle mouse button
    BUTTON_4 = GLFW_MOUSE_BUTTON_4,  // Side mouse button 1
    BUTTON_5 = GLFW_MOUSE_BUTTON_5,  // Side mouse button 2
    BUTTON_6 = GLFW_MOUSE_BUTTON_6,  // Side mouse button 3
    BUTTON_7 = GLFW_MOUSE_BUTTON_7,  // Side mouse button 4
    BUTTON_8 = GLFW_MOUSE_BUTTON_8,  // Side mouse button 5
    UNKNOWN = -1,
};

//static inline Mousecode MOUSECODES_ALL[]
//{
//    Mousecode::BUTTON_1, Mousecode::BUTTON_2, Mousecode::BUTTON_3, Mousecode::BUTTON_4,
//    Mousecode::BUTTON_5, Mousecode::BUTTON_6, Mousecode::BUTTON_7, Mousecode::BUTTON_8 
//};

//static std::unordered_map<std::string, int> keycodes;
//static std::unordered_map<std::string, int> mousecodes;

enum class InputType 
{
    keyboard,
    mouse,
};

struct Binding 
{
    //util::HandlersList<> m_on_actived;

    InputType m_type;
    int m_code;
    bool m_state = false;
    bool m_just_change = false;
    bool m_enable = true;

    Binding() = default;
    Binding(InputType type, int code) 
        : m_type(type), m_code(code) {}

    bool active() const { return m_state; }

    bool jactive() const { return m_state && m_just_change; }

    void reset(const InputType& type, const int& code)
    {
        this->m_type = type;
        this->m_code = code;
    }
    void reset(const Keycode& code) { reset(InputType::keyboard, static_cast<int>(code)); }
    void reset(const Mousecode& code) { reset(InputType::mouse, static_cast<int>(code)); }

    inline std::string text() const 
    {
        switch (m_type)
        {
            case InputType::keyboard: 
            {
                return UTILS_NAMESPACE::input::to_string(static_cast<Keycode>(m_code));
            }
            case InputType::mouse:
            {
                return UTILS_NAMESPACE::input::to_string(static_cast<Mousecode>(m_code));
            }
        }
        return "<unknown input type>";
    }
};

namespace EVENT_NAMESPACE
{
    struct KeyEvent : public IEvent 
    {
        InputType m_type;
        int m_code;
        int scancode;
        int action;

        KeyEvent(InputType type, int key, int scancode, int action, int mods)
            : m_type(type), m_code(key), scancode(scancode), action(action) {}
    };

    struct MouseMoveEvent : public IEvent 
    {
        double x, y;
        MouseMoveEvent(double x, double y) : x(x), y(y) {}
    };
}

#endif // !WINDOW_INPUT_H_