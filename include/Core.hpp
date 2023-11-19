#ifndef CORE_HPP
#define CORE_HPP

#include <string>

#include "XML/UI/System/Context.hpp"

#include "Engine/Rendering/RenderWindow.hpp"
#include "XML/UI/Event/Event.hpp"
#include "Engine/Event/Property.hpp"
#include "XML/UI/System/Expression.hpp"
#include "Engine/Rendering/Rect.hpp"

class Core
{
    public:
        Core();
        ~Core() = default;

        void init(const std::string &_path);
        void run();

    private:
        eng::ThreadPool m_tp;
        eng::RenderWindow m_win;

        eng::ui::SysEventPool m_sys_ep;

        eng::ui::Context<eng::Property<eng::Rect>::Event, eng::Property<uint32_t>::Event, eng::Property<float>::Event, eng::ui::evt::Display> m_xml;
};

#endif