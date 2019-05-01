#pragma once

#include <type_traits>
#include <thread>
#include <atomic>
#include <mutex>
#include <shared_mutex>

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
		// Rule of 5 (+1)
		BasicAtomicCounter() = default;

		BasicAtomicCounter(const BasicAtomicCounter& other) { _value = other.get(); }
		BasicAtomicCounter& operator=(const BasicAtomicCounter& other) { _value = other.get(); }

		BasicAtomicCounter(BasicAtomicCounter&& other) { _value = other.get(); }
		BasicAtomicCounter operator=(BasicAtomicCounter&& other) { _value = other.get(); }

		virtual ~BasicAtomicCounter() = default;

		// with an atomic value we can only access a copy of the value (and return the atomic directly does not seem like a good idea)
		T       get() const { return _value.load(); }
		void    reset() { _value.store(0); }

		BasicAtomicCounter&   operator++() { _value.fetch_add(1); }
		BasicAtomicCounter&   operator++(int) { _value.fetch_add(1); }

		BasicAtomicCounter&   operator--() { _value.fetch_sub(1); }
		BasicAtomicCounter&   operator--(int) { _value.fetch_sub(1); }


	private:
		std::atomic<T>   _value { 0 };
};

template<typename T, typename = typename std::enable_if_t<std::is_integral_v<T>>>
class BasicMutexCounter
{
	public:
		// Rule of 5 (+1)
		BasicMutexCounter() = default;

		BasicMutexCounter(const BasicMutexCounter& other)
		{
			std::lock_guard	lock(_mutex);
			_value = other.get();
		}

		BasicMutexCounter& operator=(const BasicMutexCounter& other)
		{
			std::lock_guard	lock(_mutex);
			_value = other.get();
		}

		BasicMutexCounter(BasicMutexCounter&& other)
		{
			std::lock_guard	lock(_mutex);
			_value = other.get();
		}
		BasicMutexCounter operator=(BasicMutexCounter&& other)
		{
			std::lock_guard	lock(_mutex);
			_value = other.get();
		}

		virtual ~BasicMutexCounter() = default;

		// never return reference to something you want to protect with a mutex
		T       get() const
		{
			std::lock_guard	lock(_mutex);
			return _value;
		}

		void    reset()
		{
			std::lock_guard	lock(_mutex);
			_value = 0;
		}

		BasicMutexCounter&   operator++()
		{
			std::lock_guard	lock(_mutex);
			++_value;
		}

		BasicMutexCounter&   operator++(int)
		{
			std::lock_guard	lock(_mutex);
			_value++;
		}

		BasicMutexCounter&   operator--()
		{
			std::lock_guard	lock(_mutex);
			--_value;
		}

		BasicMutexCounter&   operator--(int)
		{
			std::lock_guard	lock(_mutex);
			_value--;
		}


	private:
		T   				_value = 0;
		mutable std::mutex	_mutex;
};

template<typename T, typename = typename std::enable_if_t<std::is_integral_v<T>>>
class BasicSharedMutexCounter
{
	public:
		// Rule of 5 (+1)
		BasicSharedMutexCounter() = default;

		BasicSharedMutexCounter(const BasicSharedMutexCounter& other)
		{
			std::lock_guard	lock(_mutex);
			_value = other.get();
		}

		BasicSharedMutexCounter& operator=(const BasicSharedMutexCounter& other)
		{
			std::lock_guard	lock(_mutex);
			_value = other.get();
		}

		BasicSharedMutexCounter(BasicSharedMutexCounter&& other)
		{
			std::lock_guard	lock(_mutex);
			_value = other.get();
		}
		BasicSharedMutexCounter operator=(BasicSharedMutexCounter&& other)
		{
			std::lock_guard	lock(_mutex);
			_value = other.get();
		}

		virtual ~BasicSharedMutexCounter() = default;

		// never return reference to something you want to protect with a mutex
		T       get() const
		{
			std::shared_lock	lock(_mutex);
			return _value;
		}

		void    reset()
		{
			std::lock_guard	lock(_mutex);
			_value = 0;
		}

		BasicSharedMutexCounter&   operator++()
		{
			std::lock_guard	lock(_mutex);
			++_value;
		}

		BasicSharedMutexCounter&   operator++(int)
		{
			std::lock_guard	lock(_mutex);
			_value++;
		}

		BasicSharedMutexCounter&   operator--()
		{
			std::lock_guard	lock(_mutex);
			--_value;
		}

		BasicSharedMutexCounter&   operator--(int)
		{
			std::lock_guard	lock(_mutex);
			_value--;
		}


	private:
		T   						_value = 0;
		mutable std::shared_mutex	_mutex;
};

// aliases
using Counter = BasicCounter<int>;
using AtomicCounter = BasicAtomicCounter<int>;
using MutexCounter = BasicMutexCounter<int>;
using SharedMutexCounter = BasicSharedMutexCounter<int>;

}