#pragma once

#include <JUI/Widgets/Widget.hpp>

namespace JUI {
    // Base class
    // Any objects parented will
    class LayoutContainerWidget : public Widget {
    public:
        LayoutContainerWidget() {}

        ~LayoutContainerWidget() override {}

        void Update(float delta) override {
            Widget::Update(delta);
        }

        void Draw(SDL_Renderer *target) override {
            Widget::Draw(target);
        }

        virtual void ApplyLayout() {}

    protected:
    private:
    };

    class VerticalListLayout : public LayoutContainerWidget {
    public:
        VerticalListLayout() {}

        ~VerticalListLayout() override {}

        void Update(float delta) override {
            ApplyLayout();
            LayoutContainerWidget::Update(delta);
        }

        void Draw(SDL_Renderer *target) override {
            LayoutContainerWidget::Draw(target);
        }

        void ApplyLayout() override {
            int consumed_height = 0;
            for (auto &child_widget: children) {
                // TODO: Implement widget.LayoutOrder property
                // TODO: Sort children by LayoutOrder
                child_widget->SetPosition({0, consumed_height, 0, 0});
                consumed_height += child_widget->GetAbsoluteSize().Y;

            }
        }

    private:
        UDim padding;
    };

    class HorizontalListLayout : public LayoutContainerWidget {
    public:
        HorizontalListLayout() {}

        ~HorizontalListLayout() override {}

    private:
        UDim2 padding;

        void ApplyLayout() override {
            int consumed_width = 0;
            for (auto &child_widget: children) {
                // TODO: Implement widget.LayoutOrder property
                // TODO: Sort children by LayoutOrder
                child_widget->SetPosition({consumed_width, 0, 0.0f, 0.0f});
                consumed_width += child_widget->GetAbsoluteSize().X;
                consumed_width += 0;
            }
        }
    };

    enum Orientation {
        VERTICAL, HORIZONTAL
    };

    class GridLayout : public LayoutContainerWidget {
        GridLayout() {}

        ~GridLayout() override {}

    public:
        void ApplyLayout() override {

        }

    private:
        UDim2 cell_padding;
        UDim2 cell_size;
        int max_cells;
        UDim2 margin;
    };

    class Slider : public Widget {
    public:
    private:
        bool smooth_increment;
        float min;
        float max;
        float value;
        float increment;
        Orientation orientation;
    };
}