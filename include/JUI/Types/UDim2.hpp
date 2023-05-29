#pragma once

#include <JUI/Types/Vector2.hpp>
#include <JUI/Types/UDim.hpp>

// Universal Dimensions 2D - Immuatable Data Type
// Contains a scale vector, and a pixel offsets vector
// TODO: Think of a better name than UDim2
namespace JUI {

    class UDim2 {
    public:
        UDim X;
        UDim Y;

        UDim2 operator+(const UDim2& rhs) const { return {}}

#pragma region Constructors
        // TODO: Implement Math Operators
        UDim2() {
            X = {0, 0.0f};
            Y = {0, 0.0f};
        }

        UDim2(int px, int py, float sx, float sy) {
            X = {px, sx};
            Y = {py, sy};
        }

        UDim2(Vector2 pixels, Vector2 scale) {
            X = {static_cast<int>(pixels.X), scale.X};
            Y = {static_cast<int>(pixels.Y), scale.Y};
        }

        UDim2(UDim x, UDim y)
        {
            X = x;
            Y = y;
        }

        static UDim2 FromPixels(int x, int y) { return {x, y, 0, 0}; }

        static UDim2 FromScale(float x, float y) { return {0, 0, x, y}; }

#pragma endregion

        Vector2 GetScale() { return {X.Scale, Y.Scale}; }

        Vector2 GetPixels() { return {(float) X.Pixels, (float) Y.Pixels}; }

    protected:
    private:
    };
}