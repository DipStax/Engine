#include "Engine/Network/Ip.hpp"

namespace eng
{
    template<class ...Args>
    Ip::Ip(Args &&..._args)
    {
        set(std::forward<Args>(_args)...);
    }
}