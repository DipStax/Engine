#include "XML/UI/System/Context.hpp"

namespace eng::ui
{
    template<class ...Ts>
    Context<Ts...>::Context(ThreadPool &_tp, SysEventPool &_sys_ep, Point2<uint32_t> &_size)
        : m_size(_size), m_cus_ep(_tp), m_sys_ep(_sys_ep), m_tp(_tp)
    {
    }

    void load(const std::string &_path)
    {
        xml::Balise balise = Builder::run(_path);

        m_obj = m_fac.build(balise, m_ep_cus, m_ep_sys, m_tp);
    }

    template<class ...Ts>
    Point2<uint32_t> Context<Ts...>::getSize() const
    {
        return m_size;
    }

    template<class ...Ts>
    void Context<Ts...>::setSize(const Point2<uint32_t> &_size) const
    {
        m_size = _size;
    }

    template<class ...Ts>
    void Context<Ts...>::setSize(uint32_t _height, uint32_t _width) const
    {
        setSize({ _width, _height });
    }

    template<class ...Ts>
    void Context<Ts...>::display()
    {
        m_ep_cus.template raise<Display>({ m_size });
    }

    template<class ...Ts>
    void Context<Ts...>::draw(RenderTarget &_target, const Texture *_txtr) const
    {
        _target.draw(m_obj, _txtr);
    }
}