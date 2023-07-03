#include "Core.hpp"

int main(int _ac, char **ac)
{
    Core core;

    core.init("../rsc/data");
    core.run();
    return 0;
}