#pragma once

#include "JUI/Widget.hpp"

namespace JUI {
    class Scene : public Widget {
    public:
        void Draw() override;

        void Update(float delta) override;

    protected:
    private:
    };

    void Scene::Draw() {

    }

    void Scene::Update(float delta) {

    }
}
