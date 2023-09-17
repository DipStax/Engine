#ifndef CORE_HPP
#define CORE_HPP

#include <string>

class Core
{
    public:
        Core();
        ~Core() = default;

        void init(const std::string &_path);
        void run();

    private:
};

#endif