#include <iostream>
#include <string>
#include <cassert>
#include <list>

#include "Counter.hpp"


/* All the counters have the same interface:
**  - Construction with the value of 0
**  - get() to retrieve the value of the counter
**  - operator ++ to increment it
**  - opererator -- to decrement it
**  - reset() to set the value of the counter to 0
*/

/*
** Note:
** Counter is trivially copyable and trivially movable
** BUT the thread safe counters (atomic, mutex and share mutex) are not trivially copyable or trivially movable
** Because to copy/move a counter it must read/write the value 
** and to ensure there is no data race/race condition there is a cost 
*/

void example()
{
    /*
    ** Multithread example
    */
    // Create your counter
    Counter::SharedMutexCounter c;

    // Declare a lambda which will increment the counter
    auto lambda_increment =
        [&]()
        {
            for (int i = 0; i < 10000; ++i)
                ++c;
            return 0;
        }
    ;
    
    // Create threads which will use the lambda
    std::list<std::thread> threads;
    for (int j = 0; j < 10;++j)
        threads.emplace_back(lambda_increment);
    
    // Wait until the threads are done
    for (auto& t: threads)
        t.join();
    
    // Print the result
    std::cout << c.get() << std::endl;
    
    // Assert that we have the correct result
    assert(c.get() == 100000);
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

	auto c = counter;
	assert(c.get() == 1);

	Counter::BasicAtomicCounter<int> cc;
	cc = counter;
	assert(c.get() == 1);
}

void test_mutex_counter()
{
	Counter::BasicMutexCounter<int> counter;
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

	Counter::BasicMutexCounter<int> cc;
	cc = counter;
	assert(c.get() == 1);
}

void test_shared_mutex_counter()
{
	Counter::BasicSharedMutexCounter<int> counter;
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

	Counter::BasicSharedMutexCounter<int> cc;
	cc = counter;
	assert(c.get() == 1);
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
