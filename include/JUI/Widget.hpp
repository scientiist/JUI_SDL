#pragma once

#include <memory>
#include <vector>
#include <Vector2.hpp>

namespace JUI
{
    class Widget : public std::enable_shared_from_this<Widget> {
    public:
        Widget();
        virtual ~Widget();

        virtual void Draw() {}
        virtual void Update(float delta) {}


        void setParent(Widget* parent);
        Widget* getParent();
    protected:

    private:
        Widget* parent = nullptr;
        std::vector<std::shared_ptr<Widget>> children;
        //std::string name = "Instance";
        // Copy Parent-Child hierarchy from Redwood...



    };


    void Widget::setParent(Widget *parent) {
        //std::shared_ptr<Widget> shared = shared_from_this();
    }

    Widget* Widget::getParent() { }

}