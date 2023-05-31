#include <JUI/Types/UDim2.hpp>

namespace JUI {
    UDim2 UDim2::operator+(const UDim2& rhs) const
    { return {X+rhs.X, Y+rhs.Y};}

    UDim2 UDim2::operator-(const UDim2& rhs) const
    { return {X-rhs.X, Y-rhs.X};}


    UDim2::UDim2()
    {
        X = {0, 0.0f};
        Y = {0, 0.0f};
    }

    UDim2::UDim2(int px, int py, float sx, float sy) {
        X = {px, sx};
        Y = {py, sy};
    }

    UDim2::UDim2(JUI::Vector2 pixels, JUI::Vector2 scale)
    {
        X = {static_cast<int>(pixels.X), scale.X};
        Y = {static_cast<int>(pixels.Y), scale.Y};
    }

    UDim2::UDim2(UDim x, UDim y)
    {
        X = x;
        Y = y;
    }

    UDim2 UDim2::FromPixels(int x, int y) { return {x, y, 0, 0}; }
    UDim2 UDim2::FromScale(float x, float y) { return {0, 0, x, y}; }


    Vector2 UDim2::GetScale() const
    { return {X.Scale, Y.Scale}; }

    Vector2 UDim2::GetPixels() const
    { return {(float) X.Pixels, (float) Y.Pixels}; }
}