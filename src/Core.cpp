#include "Engine/Rendering/Loader.hpp"
#include "Engine/Rendering/Sprite.hpp"
#include "Engine/Rendering/RenderTexture.hpp"
#include "Core.hpp"

Core::Core()
    : m_epProp(m_tp)
{
}

void Core::init(const std::string &_path)
{
}

void Core::run()
{
    std::string in;
    eng::Property<int> prop(m_epProp, "int", 10);
    auto trig = [] (const eng::PropertyEvent &_prop) {
        std::cout << "name: " << _prop.name << std::endl;
        std::cout << "value: " << std::any_cast<int>(_prop.value) << std::endl;
    };

    auto stask = prop.subscribe(trig);
    prop = 20;
    std::cin >> in;
    prop.unsubscribe(stask);
}