#pragma once

#include <tuple>

namespace tester
{
    struct IEvent
    {};

    struct ExampleEvent : public IEvent
    {
        size_t i;
    };

    using EventList = std::tuple<ExampleEvent>;
}