#include "Core.hpp"

int main(int _ac, char **_av)
{
    std::ignore = _ac;
    std::ignore = _av;
    Core core;

    core.init("../rsc/data");
    core.run();
    return 0;
}