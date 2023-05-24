#pragma once

#include <memory>
#include <vector>
#include "JUI/Types/Vector2.hpp"
#include "JUI/Types/UDim2.hpp"
#include "JUI/Types/Event.hpp"
#include <SDL2/SDL_render.h>

namespace JUI {

    class Widget  {
    public:

        Widget();
        virtual ~Widget();

        Event<Widget *> DescendantAdded;
        Event<Widget *> DescendantRemoved;
        Event<Widget *, Widget *> AncestryChanged;
        Event<Widget *> ChildAdded;
        Event<Widget *> ChildRemoved;
        Event<Widget *> Destroying;
        Widget *NextSelection;
        Widget *PreviousSelection;
        bool Selected;
        virtual void Draw(SDL_Renderer *target) { DrawChildWidgets(target); }
        virtual void Update(float delta) = 0;
        void DrawChildWidgets(SDL_Renderer* r);
        void UpdateChildWidgets(float delta);
        bool IsAncestorOf(Widget *w);
        bool IsDescendantOf(Widget *w);
        std::vector<Widget *> GetDescendants();
        std::vector<Widget *> GetAncestors();
        std::vector<Widget*> GetChildren();
        void SetParent(Widget *parent);
        Widget *GetParent() const;
        UDim2 GetPosition() const;
        void SetPosition(UDim2 const &);
        UDim2 GetSize() const;
        void SetSize(UDim2 const &);
        virtual Vector2 GetAbsoluteSize() const;
        virtual Vector2 GetAbsolutePosition() const;
        float GetRotation() { return rotation; }
        void SetRotation(float rot) { rotation = rot; }
        float GetAbsoluteRotation() { return absolute_rotation; }
        void SetName(std::string n) { name = n;    }
        std::string GetName() const { return name; }
        Widget* FindFirstChild(std::string name);
        template <typename T>
        T* FindFirstChildOfType() const;

    protected:
        UDim2 position = {0, 0, 0.0f, 0.0f};
        UDim2 size = {200, 50, 0.0f, 0.0f};
        Vector2 absolutePosition = {0,0};
        Vector2 absoluteSize = {0,0};
        Widget *parent = nullptr;
        std::vector<Widget*> children;
        float rotation = 0;
        float absolute_rotation;
        std::string name;
    private:


        //std::string name = "Instance";
    };


}