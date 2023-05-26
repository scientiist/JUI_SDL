#pragma once

#include <JUI/Types/Vector2.hpp>
// Universal Dimensions 2D - Immuatable Data Type
// Contains a scale vector, and a pixel offsets vector
// TODO: Think of a better name than UDim2
namespace JUI {

    class UDim2 {
    public:
#pragma region Constructors

        UDim2()
        {
            pixelsX = 0;
            pixelsY = 0;
            scaleX = 0;
            scaleY = 0;
        }

        UDim2(int px, int py, float sx, float sy) :
                pixelsX(px), pixelsY(py), scaleX(sx), scaleY(sy) {}

        UDim2(Vector2 pixels, Vector2 scale) {
            pixelsX = pixels.X;
            pixelsY = pixels.Y;
            scaleX = scale.X;
            scaleY = scale.Y;
        }

        static UDim2 FromPixels(int x, int y) { return {x, y, 0, 0}; }

        static UDim2 FromScale(float x, float y) { return {0, 0, x, y}; }

#pragma endregion

        Vector2 GetScale() { return {scaleX, scaleY}; }

        Vector2 GetPixels() { return {(float) pixelsX, (float) pixelsY}; }

    protected:
    private:
        int pixelsX;
        int pixelsY;
        float scaleX;
        float scaleY;
    };
}