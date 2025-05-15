#pragma once
#ifndef TYPES_SETTING_H_
#define TYPES_SETTING_H_

#include <limits>
#include <string>
#include <unordered_map>
#include <vector>
#include <memory>

#include "enginecore/utils/types/Delegates.h"
#include "enginecore/core/CoreDefines.h"

#ifdef max
#undef max
#endif // max

#ifdef min
#undef min
#endif // min


enum class setting_format { simple, percent };

class Setting
{
public:
    Setting(setting_format format)
        : m_format(format) {
    }

    virtual ~Setting() {}

    virtual void resetToDefault() = 0;

    virtual setting_format getFormat() const { return m_format; }

    virtual std::string toString() const = 0;

protected:
    setting_format m_format;
};

template <class T>
class ObservableSetting : public Setting
{
public:
    ObservableSetting(T value, setting_format format)
        : Setting(format), m_initial(value), m_value(value) {
    }

    delegates::observer_handler observe(delegates::consumer<T> callback, bool call_on_start = false)
    {
        const int id = m_next_id++;
        m_observers.emplace(id, callback);
        if (call_on_start)
        {
            callback(m_value);
        }


        return std::shared_ptr<int>(new int(id),
            [this](int* id)
            {
                m_observers.erase(*id);
                delete id;
            });
    }

    const T& get() const { return m_value; }
    const T& getDefault() const { return m_initial; }
    T& operator*() { return m_value; }

    void notify(T m_value)
    {
        for (auto& entry : m_observers)
        {
            entry.second(m_value);
        }
    }

    void set(T m_value)
    {
        if (m_value == this->m_value)
        {
            return;
        }
        this->m_value = m_value;
        notify(m_value);
    }

    virtual void resetToDefault() override { set(m_initial); }

private:
    int m_next_id = 1;
    std::unordered_map<int, delegates::consumer<T>> m_observers;

protected:
    T m_initial;
    T m_value;
};

class NumberSetting : public ObservableSetting<number_t>
{
public:
    NumberSetting(number_t m_value, number_t min = std::numeric_limits<number_t>::min(),
        number_t m_max = std::numeric_limits<number_t>::max(), setting_format m_format = setting_format::simple)
        : ObservableSetting(m_value, m_format), m_min(min), m_max(m_max) {
    }

    number_t& operator*() { return m_value; }

    number_t get() const { return m_value; }

    number_t getMin() const { return m_min; }

    number_t getMax() const { return m_max; }

    number_t getT() const { return (m_value - m_min) / (m_max - m_min); }

    virtual std::string toString() const override
    {
        switch (getFormat())
        {
        case setting_format::simple:
            return std::to_string(m_value);
        case setting_format::percent:
            return std::to_string(static_cast<integer_t>(std::round(m_value * 100))) + "%";
        default:
            return "invalid format";
        }
    }

    static inline NumberSetting createPercent(number_t def)
    {
        return NumberSetting(def, 0.0, 1.0, setting_format::percent);
    }

protected:
    number_t m_min;
    number_t m_max;
};

class IntegerSetting : public ObservableSetting<integer_t>
{
public:
    IntegerSetting(integer_t value, integer_t min = std::numeric_limits<integer_t>::min(),
        integer_t max = std::numeric_limits<integer_t>::max(), setting_format format = setting_format::simple)
        : ObservableSetting(value, format), m_min(min), m_max(max) {}

    integer_t getMin() const { return m_min; }

    integer_t getMax() const { return m_max; }

    integer_t getT() const { return (m_value - m_min) / (m_max - m_min); }

    virtual std::string toString() const override
    {
        switch (getFormat())
        {
            case setting_format::simple:
                return std::to_string(m_value);
            case setting_format::percent:
                return std::to_string(m_value) + "%";
            default:
                return "invalid format";
        }
    }

protected:
    integer_t m_min;
    integer_t m_max;
};

class FlagSetting : public ObservableSetting<bool> 
{
public:
    FlagSetting(bool m_value, setting_format m_format = setting_format::simple)
        : ObservableSetting(m_value, m_format) {}

    void toggle() { set(!get()); }

    virtual std::string toString() const override
    {
        switch (getFormat()) 
        {
            case setting_format::simple:
                return m_value ? "true" : "false";
            default:
                return "invalid format";
        }
    }
};

class StringSetting : public ObservableSetting<std::u32string> 
{
public:
    StringSetting(std::u32string m_value, setting_format m_format = setting_format::simple)
        : ObservableSetting(m_value, m_format) {}

    virtual std::string toString() const override 
    { 
        std::string ret = std::string();
        for (const auto& symb : m_value)
        {
            ret += static_cast<char>(symb);
        }
        return ret;
    }
    virtual std::u32string toU32String() const { return m_value; }
};

#endif // !TYPES_SETTING_H_