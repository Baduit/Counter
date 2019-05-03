# Counter
## Overall description
This is a C++ 17 header only library. Its goal is to create counter easily without writing boilerplate.

In this library there is 2 types of counters: "normal" counters (Counter) and thread safe counters (AtomicCounter, MutexCounter and SharedMutexCounter).

## How to use
### Method description 
* To access the value of the counter use the __get()__ method.
* To set the value of the counter use the __reset()__ method.
* To increment the counter use the __operator++__.
* To decrement the counter use the __operator--__.

### Example
```C++
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
```

### Note
The "normal" counter is trivially copyable but the thread safe counters are not trivially copyable nor trivially movable.

## Add it to your project
Just put the header __Counter.hpp__ in your path/sources.
Note that it requires C++ 17 because it uses std::shared_mutex and template deduction on class. Without this it should only require C++ 11.

## Why Counter is an alias for BasicCounter<int>?
All the counters classes are created with a basic templated class which allows to choose the underlying type used, then there is an alias to reduce the boilerplate code when the underlying type is not important.

If a __int__ does not fit your need, use the basic class instead of the alias. (and/or create your own alias)

## Differencies between thread safe counters
There is 3 types of thread safe counters:
* __AtomicCounter__ using the atomic operations.
* __MutexCounter__ using the std::mutex to lock the access to the value.
* __SharedMutexCounter__ using the std::shared type to lock the access to the value. Better than MutexCounter if there is 1 (or few) writer(s) and severals readers.

I advise to use the AtomicCounter by default in multithreaded applications, but the best way to choose is to makes benchmark if there are performance issues.

## Tests
There is some basic tests, juste use cmake (or compile it manually that's not hard) and run the executable test.out.

