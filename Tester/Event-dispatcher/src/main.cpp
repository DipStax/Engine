#include <iostream>

#include "EventPool.hpp"
#include "ThreadPool.hpp"

void func(const tester::ExampleEvent &_event)
{
    std::cout << _event.i << std::endl;
}

int main()
{
    tester::ThreadPool tp;
    tester::ExampleEvent ex;

    tester::EventPool<tester::ExampleEvent> ep(tp);

    ex.i = 1;
    auto handler = ep.subscribe<tester::ExampleEvent>(func);
    ep.raise(ex);
    while (true) {}
    // tester::EventPool::Unsubscribe(handler);
    // tester::ThreadPool::stop();
    return 0;
}