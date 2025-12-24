#pragma once
#ifndef TYPES_FIXEDPOINT_H_
#define TYPES_FIXEDPOINT_H_

#include <cstdint>
#include <iostream>

#include <glm/glm.hpp>

#include <fixed_math/fixed_math.hpp>

using fixedmath::fixed_t;
using fixedmath::operator""_fix;

constexpr auto DIGITS = 1024; // exponent
constexpr auto EPS = 20; // sqrt limit


class FixedPoint
{
private:
	using fixed_int_t = signed int;

	static FixedPoint fromFixedInt(const fixed_int_t& a)
	{
		FixedPoint res;
		res.x = a;
		return res;
	}

public:
	FixedPoint() = default;
	~FixedPoint() = default;

	/*FixedPoint(const int& val)
	{
		x = val * DIGITS;
	}*/
	
	constexpr FixedPoint(const float& val)
	{
		x = static_cast<fixed_int_t>(val * DIGITS);
	}

public:
	float fixed2float() const
	{
		return (static_cast<float>(x)) / DIGITS;
	}

public:
	FixedPoint operator+(const FixedPoint& b)
	{
		return fromFixedInt(x + b.x);
	}

	FixedPoint& operator+=(const FixedPoint& b)
	{
		x += b.x;
		return *this;
	}

	FixedPoint operator-(const FixedPoint& b)
	{
		return fromFixedInt(x - b.x);
	}

	FixedPoint& operator-=(const FixedPoint& b)
	{
		x -= b.x;
		return *this;
	}

	FixedPoint operator*(const FixedPoint& b)
	{
		fixed_int_t c = x * b.x;
		if (c / b.x != x) 
		{
			// Overflow!
			fixed_int_t i1 = x / DIGITS;
			fixed_int_t i2 = b.x / DIGITS;
			fixed_int_t f1 = (x & (DIGITS - 1));
			fixed_int_t f2 = (b.x & (DIGITS - 1));
			return fromFixedInt((i1 * i2) * DIGITS + (f1 * f2) / DIGITS + i1 * f2 + i2 * f1);
		}
		else 
		{
			return fromFixedInt(c / DIGITS);
		}
	}

	FixedPoint& operator*=(const FixedPoint& b)
	{
		*this = *this * b;
		return *this;
	}

	FixedPoint operator/(const FixedPoint& b)
	{
		if (x > (1 << 21)) 
		{
			// Overflow!
			fixed_int_t i = x / DIGITS;
			fixed_int_t f = (x & (DIGITS - 1));
			return fromFixedInt(((i * DIGITS) / b.x) * DIGITS + (f * DIGITS) / b.x);
		}
		else 
		{
			return fromFixedInt((x * DIGITS) / b.x);
		}
	}

	FixedPoint& operator/=(const FixedPoint& b)
	{
		*this = *this / b;
		return *this;
	}


	FixedPoint sqrt(const FixedPoint& k)
	{
		FixedPoint tmp;
		tmp.x = k.x / 2;
		fixed_int_t min = 0;
		fixed_int_t max = k.x;
		FixedPoint quick;
		do 
		{
			tmp.x = (min + max) / 2;
			quick = tmp * tmp;
			if (abs(quick.x - k.x) < EPS) 
				return tmp;
			if (quick.x > k.x) 
			{
				max = tmp.x;
			}
			else 
			{
				min = tmp.x;
			}
		} while (true);
	}

public:
	explicit operator float() const
	{
		return fixed2float();
	}

	constexpr bool operator==(const FixedPoint& other)
	{
		return x == other.x;
	}
	constexpr bool operator!=(const FixedPoint& other)
	{
		return x != other.x;
	}
	constexpr bool operator<(const FixedPoint& other)
	{
		return x < other.x;
	}
	constexpr bool operator>(const FixedPoint& other)
	{
		return x > other.x;
	}

private:
	fixed_int_t x = 0;
};

//namespace std 
//{
//	template<>
//	class numeric_limits<FixedPoint> 
//	{
//	public:
//		static constexpr bool is_specialized = true;
//
//		static constexpr bool is_signed = true;
//		static constexpr bool is_integer = false;
//		static constexpr bool is_exact = false;
//
//		static constexpr int radix = 2;
//		static constexpr int digits = 24;
//		static constexpr int digits10 = 6;
//
//		static constexpr FixedPoint min() noexcept {
//			return FixedPoint(numeric_limits<float>::min());
//		}
//		static constexpr FixedPoint max() noexcept {
//			return FixedPoint(numeric_limits<float>::max());
//		}
//		static constexpr FixedPoint lowest() noexcept {
//			return FixedPoint(numeric_limits<float>::lowest());
//		}
//
//		static constexpr FixedPoint epsilon() noexcept {
//			return FixedPoint(numeric_limits<float>::epsilon());
//		}
//		static constexpr FixedPoint round_error() noexcept {
//			return FixedPoint(numeric_limits<float>::round_error());
//		}
//
//		static constexpr FixedPoint infinity() noexcept {
//			return FixedPoint(numeric_limits<float>::infinity());
//		}
//		static constexpr FixedPoint quiet_NaN() noexcept {
//			return FixedPoint(numeric_limits<float>::quiet_NaN());
//		}
//		static constexpr FixedPoint signaling_NaN() noexcept {
//			return FixedPoint(numeric_limits<float>::signaling_NaN());
//		}
//		static constexpr FixedPoint denorm_min() noexcept {
//			return FixedPoint(numeric_limits<float>::denorm_min());
//		}
//
//		static constexpr bool has_infinity = true;
//		static constexpr bool has_quiet_NaN = true;
//		static constexpr bool has_signaling_NaN = true;
//		static constexpr float_denorm_style has_denorm = denorm_present;
//		static constexpr bool has_denorm_loss = false;
//
//		static constexpr bool is_iec559 = true;
//		static constexpr bool is_bounded = true;
//		static constexpr bool is_modulo = false;
//
//		static constexpr bool traps = false;
//		static constexpr bool tinyness_before = false;
//
//		static constexpr float_round_style round_style = round_to_nearest;
//	};
//}


#endif // !TYPES_FIXEDPOINT_H_