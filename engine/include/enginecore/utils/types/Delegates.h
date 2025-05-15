#pragma once
#ifndef TYPES_DELEGATES_H_
#define TYPES_DELEGATES_H_

#include <functional>
#include <string>
#include <memory>

#include <glm/glm.hpp>

namespace delegates
{
	using runnable = std::function<void()>;
	template<class T> using supplier = std::function<T()>;
	template<class T> using consumer = std::function<void(T)>;

	using key_callback = std::function<bool()>;

	// data sources
	using u32stringsupplier = std::function<std::u32string()>;
	using doublesupplier = std::function<double()>;
	using boolsupplier = std::function<bool()>;
	using vec2supplier = std::function<glm::vec2()>;
	using key_handler = std::function<bool(int)>;

	using stringconsumer = std::function<void(const std::string&)>;
	using u32stringconsumer = std::function<void(const std::u32string&)>;
	using doubleconsumer = std::function<void(double)>;
	using boolconsumer = std::function<void(bool)>;
	using int_array_consumer = std::function<void(const int[], size_t)>;
	using u32stringchecker = std::function<bool(const std::u32string&)>;

	using observer_handler = std::shared_ptr<int>;
}

#endif // !TYPES_DELEGATES_H_