#include <iostream>
#include <string>
#include <cassert>

#include "Counter.hpp"

void example()
{

}

void test_basic_counter()
{
	Counter::BasicCounter<int> counter;
	assert(counter.get() == 0);

	++counter;
	assert(counter.get() == 1);

	counter++;
	assert(counter.get() == 2);

	counter--;
	assert(counter.get() == 1);

	counter.reset();
	assert(counter.get() == 0);

	++counter;

	auto c = counter;
	assert(c.get() == 1);

	Counter::BasicCounter<int> cc;
	cc = counter;
	assert(c.get() == 1);
}

void test_atomic_counter()
{
	Counter::BasicAtomicCounter<int> counter;
	assert(counter.get() == 0);

	++counter;
	assert(counter.get() == 1);

	counter++;
	assert(counter.get() == 2);

	counter--;
	assert(counter.get() == 1);

	counter.reset();
	assert(counter.get() == 0);

	++counter;
}

void test_mutex_counter()
{

}

void test_shared_mutex_counter()
{

}

int main()
{
	test_basic_counter();
	test_atomic_counter();
	test_mutex_counter();
	test_shared_mutex_counter();
	std::cout << "All tests passed." << std::endl;

	example();
}