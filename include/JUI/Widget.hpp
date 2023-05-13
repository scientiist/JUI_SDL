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


    void Widget::setParent(Widget *newParent) {
        // hold a reference to this so it doesn't get collected as we're working with it
        std::shared_ptr<Widget> shared = shared_from_this();

        Widget* oldParent = this->parent;
        if (parent == newParent)
            return;

        // Don't allow for an instance to be parented to itself
        if (this == newParent)
        {
            throw std::runtime_error("Cannot parent a widget to itself");
        }

        if (this->isAncestorOf(newParent))
        {
            throw std::runtime_error("Cannot create circular reference");
        }

        for (Widget* ancestor : this->getAncestors())
        {
            if (oldParent && !ancestor->isAncestorOf(newParent) && newParent != ancestor)
            {
                // TODO: ancestor->onDescendantRemoved(this, oldParent, newParent);
                for (Widget* descendant: this->getDescendants())
                {
                    ancestor->OnDescendantRemoving(descendant, oldParent, newParent);
                }
            }
        }

        // Remove ourselves from our parent (if we have one)
        if (this->parent) 
        {
            this->parent->onChildRemoving(this);
            parent->children.erase(std::remove(parent->children.begin(), parent->children.end(), this->shared_from_this()), parent->children.end());
        }

        // Update our old parent to the new one
        this->parent = newParent;

        // If our parent is set to nullptr, we can't update it's vector of children
        if (!newParent)
        {
            return;
        }

        // Add ourselves to our new parent's list of children
        newParent->children.emplace_back(this->shared_from_this());
        newParent->onChildAdded(this);

        for (Widget* ancestor : this->getAncestors()) {
            if (!oldParent || !oldParent->isDescendantOf(newParent) && oldParent != ancestor)
            {
                // Don't fire event unless an instance is actually a new descendant
                ancestor->OnDescendantAdded(this, oldParent, newParent);
                for (Widget* descendant : this->getDescendants())
                {
                    ancestor->OnDescendantAdded(descendant, oldParent, newParent);
                }
            }
        }
    }

    bool Widget:isDescendantOf(Widget* ancestor)
    {
        if (ancestor == nullptr)
            return false;
        Widget* instance = this;
        while(instane->getParent())
        {
            instance = instance->getParent();
            if (instance == ancestor)
                return true;
        }
        return false;
    }

    bool Widget::isAncestorOf(Widget* descendant)
    {
        if (descendant == nullptr)
            return false;
        Widget* instance = descendant;
        while (instance->getParent())
        {
            instance = instance->getParent();
            if (instance == this)
                return true;
        }
        return false;
    }


    std::vector<std::shared_ptr<Widget>> Widget::getChildren()
    {
        return this->children;
    }

    std::vector<Widget*> Widget::getDescendants()
    {
        std::vector<Widget*> descendants;
        for (std::shared_ptr<Widget> child : this->children)
        {
            descendants.push_back(child.get());
            std::vector<Widget*> recursiveDescendants = child->getDescendants();
            descendants.insert(descendants.end(), recursiveDescendants.begin(), recursiveDescendants.end());
        }
        return descendants;
    }

    std::vector<Widget*> Widget::getAncestors()
    {
        std::vector<Widget*> ancestors;
        for (Widget* ancestor = this->parent; ancestor; ancestor = ancester->parent)
        {
            ancestors.push_back(ancestor);
        }
        return ancestors;
    }

    void Widget::

    Widget* Widget::getParent() { }

}