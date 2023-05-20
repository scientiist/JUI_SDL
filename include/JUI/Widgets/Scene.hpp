#pragma once

#include <SDL2/SDL.h>
#include "JUI/Widget.hpp"

namespace JUI {
    class Scene : public Widget {
    public:
        Scene(SDL_Window *wnd, SDL_Renderer *rend) : Widget() {

        }

        void Draw() override;

        void Update(float delta) override;

    protected:
    private:
        SDL_Window *window;
        SDL_Renderer *renderer;
    };

    void Scene::Draw() {
        DrawChildWidgets();
    }

    void Scene::Update(float delta) {
        UpdateChildWidgets(delta);
    }

}
