
#include "JUI/Widgets/Widget.hpp"

namespace JUI {

    Widget::Widget() {
        children = std::vector<Widget *>();
    }

    Widget::~Widget() {}

    void Widget::Update(float delta) {
        this->UpdateChildWidgets(delta);
    }

    void Widget::DrawChildWidgets(SDL_Renderer *target) {
        for (auto child: children) {
            child->Draw(target);
        }
    }

    void Widget::UpdateChildWidgets(float delta) {
        for (auto &child: children) {
            child->Update(delta);
        }
    }

    void Widget::SetParent(Widget *parent) {
        // hold a reference to this so it doesn't get collected as we're working with it
        //std::shared_ptr<Widget> shared = shared_from_this();
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
                    ancestor->DescendantRemoved(descendant);
                }
            }
        }

        // Remove ourselves from our parent (if we have one)
        if (this->parent) {
            //this->parent->onChildRemoving(this);
            parent->children.erase(std::remove(parent->children.begin(), parent->children.end(), this), parent->children.end());
        }

        // Update our old parent to the new one
        this->parent = parent;

        // If our parent is set to nullptr, we can't update it's vector of children
        if (!parent) {
            return;
        }

        // Add ourselves to our new parent's list of children
        parent->children.emplace_back(this);
        //newParent->onChildAdded(this);

        /*for (Widget *ancestor: this->GetAncestors()) {
            if (!oldParent || (!oldParent->IsDescendantOf(parent) && oldParent != ancestor)) {
                // Don't fire event unless an instance is actually a new descendant
                //ancestor->OnDescendantAdded(this, oldParent, newParent);
                for (Widget* _: this->GetDescendants()) {
                    //ancestor->OnDescendantAdded(descendant, oldParent, newParent);
                }
            }
        }*/
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


    std::vector<Widget*> Widget::GetChildren() {
        return this->children;
    }

    std::vector<Widget *> Widget::GetDescendants() {
        std::vector<Widget *> descendants;
        for (auto& child: this->children) {
            descendants.push_back(child);
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

    Widget* Widget::GetParent() const { return parent; }

    UDim2 Widget::GetPosition() const { return position;}
    void Widget::SetPosition(const JUI::UDim2 &pos) {
        position = pos;
    }
    UDim2 Widget::GetSize() const { return size;}
    void Widget::SetSize(const JUI::UDim2 &s) {
        size = s;
    }

    Vector2 Widget::GetAbsolutePosition() const {
        //Vector2 child_size_scale = this->GetSize().GetScale();
        //Vector2 child_size_pixels = this->GetSize().GetPixels();
        Vector2 child_pos_scale = this->GetPosition().GetScale();
        Vector2 child_pos_pixels = this->GetPosition().GetPixels();
        Vector2 parent_abs_size = this->GetParent()->GetAbsoluteSize();
        Vector2 parent_abs_pos = this->GetParent()->GetAbsolutePosition();
        Vector2 absolute_position = parent_abs_pos + child_pos_pixels + (parent_abs_size * child_pos_scale);
        return absolute_position;
    }

    // TODO: implement padding shrinking abs_size;
    Vector2 Widget::GetAbsoluteSize() const {
        Vector2 child_size_scale = this->GetSize().GetScale();
        Vector2 child_size_pixels = this->GetSize().GetPixels();
        Vector2 parent_abs_size = this->GetParent()->GetAbsoluteSize();

        UDim padding_h = parent->GetPaddingLeft() + parent->GetPaddingRight();
        float calculated_padding_x = padding_h.Pixels + (padding_h.Scale * parent->GetAbsoluteSize().X );

        UDim padding_v = parent->GetPaddingTop() + parent->GetPaddingBottom();
        float calculated_padding_y = padding_v.Pixels + (padding_v.Scale * parent->GetAbsoluteSize().Y);

        Vector2 padding_size_reduction = {calculated_padding_x, calculated_padding_y};


        Vector2 absolute_size = child_size_pixels + (parent_abs_size * child_size_scale) + padding_size_reduction;
        // TODO: Take into account constraints on the widget
        return absolute_size;
    }

    Widget* Widget::FindFirstChild(std::string search_name)
    {
        for (auto& child : children) {
            if (child->GetName() == search_name) {
                return child;
            }
        }
        return nullptr;
    }

    template <typename T>
    T* Widget::FindFirstChildOfType() const
    {
        for (auto& child : children) {
            T* p = dynamic_cast<T>(child);

            if (p != nullptr)
                return p;
        }
        return nullptr;
    }

    float Widget::GetRotation() const
    { return rotation; }

    void Widget::SetRotation(float rot)
    {rotation = rot;}

    UDim Widget::GetPaddingLeft()   const { return padding_left; }
    UDim Widget::GetPaddingRight()  const { return padding_right;}
    UDim Widget::GetPaddingTop()    const { return padding_top;  }
    UDim Widget::GetPaddingBottom() const { return padding_bottom;}

    void Widget::SetPaddingLeft(UDim pl)  { padding_left = pl;}
    void Widget::SetPaddingRight(UDim pr) { padding_right = pr;}
    void Widget::SetPaddingTop(UDim pt)   { padding_top = pt;}
    void Widget::SetPaddingBottom(UDim pb){ padding_bottom = pb;}

    UDim Widget::GetMarginLeft()   const { return margin_left;}
    UDim Widget::GetMarginRight()  const { return margin_right; }
    UDim Widget::GetMarginTop()    const { return margin_top;}
    UDim Widget::GetMarginBottom() const { return margin_bottom;}

    void Widget::SetMarginLeft(UDim ml)   { margin_left = ml;}
    void Widget::SetMarginRight(UDim mr)  { margin_right = mr;}
    void Widget::SetMarginTop(UDim mt)    { margin_top = mt;}
    void Widget::SetMarginBottom(UDim mb) { margin_bottom = mb;}


}