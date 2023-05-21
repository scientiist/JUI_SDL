
#include <JUI/Widgets/Scene.hpp>

namespace JUI
{
    void Scene::Update(float delta)
    {
        this->UpdateChildWidgets(delta);
    }

    Vector2 Scene::GetAbsolutePosition() const {
        return {0,0};
    }

    Vector2 Scene::GetAbsoluteSize() const {
        return {640, 480};
    }
}