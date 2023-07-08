#include <iostream>

#include "EventPool.hpp"
#include "ThreadPool.hpp"

void func(const tester::ExampleEvent &_event)
{
    std::cout << _event.i << std::endl;
}

int main()
{
    tester::ExampleEvent ex;

    ex.i = 1;
    tester::ThreadPool::start();
    auto handler = tester::EventPool::Subscribe<tester::ExampleEvent>(func);
    tester::EventPool::Raise(ex);
    tester::EventPool::Unsubscribe(handler);
    tester::ThreadPool::stop();
    return 0;
}