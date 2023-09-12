#ifndef CORE_HPP
#define CORE_HPP

#include "Engine/Event/Property.hpp"

class Core
{
    public:
        Core();
        ~Core() = default;

        void init(const std::string &_path);
        void run();

    private:
        eng::ThreadPool m_tp{};
        eng::EventPool<eng::PropertyEvent> m_epProp;
};

#endif