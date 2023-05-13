#pragma once

#include <JUI/Widget.hpp>
#include <JUI/Color.hpp>

namespace JUI {
    class Rect : public Widget {
    public:

        void Draw() override;
        void Update(float delta) override;
        bool ClipsDescendants;
        bool BorderEnabled;
        float BorderThickness;
        Color BorderColor;
        Color
    protected:
    private:
        
    };
}
