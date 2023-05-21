#pragma once

#include <SDL2/SDL.h>
#include <JUI/Widget.hpp>

namespace JUI {
    class Scene : public Widget {
    public:
        Scene() : Widget() {

        }
        Scene(SDL_Window *wnd, SDL_Renderer *rend) : Widget(), window(wnd), renderer(rend)
        {}

        ~Scene() {}

        void Draw() { Draw(renderer); }
        void Draw(SDL_Renderer* target) override
        {
            for (auto child: children) {
                child->Draw(target);
            }
        }

        void Update(float delta) override;

        Vector2 GetAbsolutePosition() const override;
        Vector2 GetAbsoluteSize() const override;

    protected:
    private:
        SDL_Window *window;
        SDL_Renderer *renderer;
    };





}
