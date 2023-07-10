#ifndef ECS_SYS_RENDER_MODEL_HPP
#define ECS_SYS_RENDER_MODEL_HPP

#include "ECS/System/ISystem.hpp"

namespace ecs::sys
{
    class RenderModel : public ISystem
    {
        public:
            void run(MainRegister &_reg, Entity *_entity, eng::Window *_window) override;

        private:
            std::vector<eng::Point2<float>> transform(const ecs::comp::Model &_model, eng::Window *_window) const;
            void process(ecs::comp::Model &_model, eng::Window *_window) const;
    };
}

#endif