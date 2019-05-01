#pragma once

#include <type_traits>
#include <thread>
#include <atomic>

namespace Counter
{

template<typename T, typename = typename std::enable_if_t<std::is_integral_v<T>>>
class BasicCounter
{
	public:
		// Rule of 0

		// Integral values are normally about the same size as a pointer or shorter so no need to pass them as const&
		T       get() const { return _value; }
		void    reset() { _value = 0; }

		BasicCounter&   operator++() { ++_value; }
		BasicCounter&   operator++(int) { _value++; }

		BasicCounter&   operator--() { --_value; }
		BasicCounter&   operator--(int) { _value--; }


	private:
		T   _value = 0;
};

template<typename T, typename = typename std::enable_if_t<std::is_integral_v<T>>>
class BasicAtomicCounter
{
	public:
		// Rule of 0

		// Integral values are normally about the same size as a pointer or shorter so no need to pass them as const&
		T       get() const { return _value.load(); }
		void    reset() { _value.store(0); }

		BasicAtomicCounter&   operator++() { _value.fetch_add(1); }
		BasicAtomicCounter&   operator++(int) { _value.fetch_add(1); }

		BasicAtomicCounter&   operator--() { _value.fetch_sub(1); }
		BasicAtomicCounter&   operator--(int) { _value.fetch_sub(1); }


	private:
		std::atomic<T>   _value { 0 };
};

// aliases
using Counter = BasicCounter<int>;
using AtomicCounter = BasicAtomicCounter<int>;


}