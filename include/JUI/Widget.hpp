#pragma once

#include <memory>
#include <vector>
#include <JUI/Types/Vector2.hpp>
#include <JUI/Types/UDim2.hpp>
#include <JUI/Event.hpp>
#include <SDL_render.h>

namespace JUI {

    class Widget : public std::enable_shared_from_this<Widget> {
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


        virtual void Draw(SDL_Renderer *target);

        virtual void Update(float delta);

        void DrawChildWidgets();

        void UpdateChildWidgets(float delta);

        bool IsAncestorOf(Widget *w);

        bool IsDescendantOf(Widget *w);

        std::vector<Widget *> GetDescendants();

        std::vector<Widget *> GetAncestors();

        std::vector<std::shared_ptr<Widget>> GetChildren();

        void SetParent(Widget *parent);

        Widget *GetParent();

        UDim2 GetPosition();

        void SetPosition(UDim2 const &);

        UDim2 GetSize();

        void SetSize(UDim2 const &);

        Vector2 GetAbsoluteSize() {
            Vector2 child_size_scale = this->GetSize().GetScale();
            Vector2 child_size_pixels = this->GetSize().GetPixels();
            Vector2 child_pos_scale = this->GetPosition().GetScale();
            Vector2 child_pos_pixels = this->GetPosition().GetPixels();
            Vector2 parent_abs_size = this->GetParent()->GetAbsoluteSize();
            Vector2 parent_abs_pos = this->GetParent()->GetAbsolutePosition();
            Vector2 absolute_size = (child_size_scale * parent_abs_size) + child_size_pixels;
            // TODO: Take into account constraints on the widget
            return absolute_size;
        }

        Vector2 GetAbsolutePosition() {
            Vector2 child_size_scale = this->GetSize().GetScale();
            Vector2 child_size_pixels = this->GetSize().GetPixels();
            Vector2 child_pos_scale = this->GetPosition().GetScale();
            Vector2 child_pos_pixels = this->GetPosition().GetPixels();
            Vector2 parent_abs_size = this->GetParent()->GetAbsoluteSize();
            Vector2 parent_abs_pos = this->GetParent()->GetAbsolutePosition();
            Vector2 absolute_position = parent_abs_pos + (child_pos_scale * parent_abs_size) + child_pos_pixels;
            return absolute_position;
        }

        float GetRotation() { return rotation; }

        void SetRotation(float rot) { rotation = rot; }

        float GetAbsoluteRotation() { return absolute_rotation; }

        //void _SetAbsoluteSize(Vector2 const &);

        //void _SetAbsolutePosition(Vector2 const &);

    protected:

    private:
        UDim2 position;
        UDim2 size;
        Vector2 absolutePosition;
        Vector2 absoluteSize;
        Widget *parent = nullptr;
        std::vector<std::shared_ptr<Widget>> children;
        float rotation = 0;
        float absolute_rotation;

        //std::string name = "Instance";
    };

    void Widget::Update(float delta) {

    }


    void Widget::UpdateChildWidgets(float delta) {
        for (const auto &child: GetChildren()) {

        }
    }

    void Widget::SetParent(Widget *parent) {
        // hold a reference to this so it doesn't get collected as we're working with it
        std::shared_ptr<Widget> shared = shared_from_this();
        Widget *oldParent = this->parent;
        if (parent == oldParent)
            return;
        // Don't allow for an instance to be parented to itself
        if (this == parent)
            throw std::runtime_error("Cannot parent a widget to itself");
        if (this->IsAncestorOf(parent))
            throw std::runtime_error("Cannot create circular reference");

        for (Widget *ancestor: this->GetAncestors()) {
            if (oldParent && !ancestor->IsAncestorOf(parent) && parent != ancestor) {
                ancestor->DescendantRemoved(this);
                for (Widget *descendant: this->GetDescendants()) {
                    ancestor->DescendantRemoved(this);
                }
            }
        }

        // Remove ourselves from our parent (if we have one)
        if (this->parent) {
            //this->parent->onChildRemoving(this);
            parent->children.erase(std::remove(parent->children.begin(), parent->children.end(), this->shared_from_this()), parent->children.end());
        }

        // Update our old parent to the new one
        this->parent = parent;

        // If our parent is set to nullptr, we can't update it's vector of children
        if (!parent) {
            return;
        }

        // Add ourselves to our new parent's list of children
        parent->children.emplace_back(this->shared_from_this());
        //newParent->onChildAdded(this);

        for (Widget *ancestor: this->GetAncestors()) {
            if (!oldParent || !oldParent->IsDescendantOf(parent) && oldParent != ancestor) {
                // Don't fire event unless an instance is actually a new descendant
                //ancestor->OnDescendantAdded(this, oldParent, newParent);
                for (Widget *descendant: this->GetDescendants()) {
                    //ancestor->OnDescendantAdded(descendant, oldParent, newParent);
                }
            }
        }
    }

    bool Widget::IsDescendantOf(Widget *ancestor) {
        if (ancestor == nullptr)
            return false;
        Widget *instance = this;
        while (instance->GetParent()) {
            instance = instance->GetParent();
            if (instance == ancestor)
                return true;
        }
        return false;
    }

    bool Widget::IsAncestorOf(Widget *descendant) {
        if (descendant == nullptr)
            return false;
        Widget *instance = descendant;
        while (instance->GetParent()) {
            instance = instance->GetParent();
            if (instance == this)
                return true;
        }
        return false;
    }


    std::vector<std::shared_ptr<Widget>> Widget::GetChildren() {
        return this->children;
    }

    std::vector<Widget *> Widget::GetDescendants() {
        std::vector<Widget *> descendants;
        for (std::shared_ptr<Widget> child: this->children) {
            descendants.push_back(child.get());
            std::vector<Widget *> recursiveDescendants = child->GetDescendants();
            descendants.insert(descendants.end(), recursiveDescendants.begin(), recursiveDescendants.end());
        }
        return descendants;
    }

    std::vector<Widget *> Widget::GetAncestors() {
        std::vector<Widget *> ancestors;
        for (Widget *ancestor = this->parent; ancestor; ancestor = ancestor->parent) {
            ancestors.push_back(ancestor);
        }
        return ancestors;
    }

    Widget *Widget::GetParent() {}

}