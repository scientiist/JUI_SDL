#pragma once

#include <JUI/Widget.hpp>
#include "JUI/Types/Color.hpp"
#include "JUI/Types/UDim2.hpp"

namespace JUI {
    class Rect : public Widget {
    public:

        void Draw() override;

        void Update(float delta) override;

        void SetBackgroundColor(JUI::Color c);

        void SetBorderColor(JUI::Color c);

        void SetBorderWidth(float);

        void SetClipsDescendants(bool);

        bool GetClipsDescendants();

        void SetTransparency(float alpha);

        float GetTransparency();

        float GetRotation();

        float SetRotation();

        bool IsVisible();

        void SetVisible(bool);

    protected:
    private:
        float transparency;
    };


    void Rect::Draw() {

    }
}
