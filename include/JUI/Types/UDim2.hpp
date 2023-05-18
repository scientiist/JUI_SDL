#pragma once

#include "Vector2.hpp"
// Universal Dimensions 2D
// Contains a scale vector, and a pixel offsets vector
// TODO: Think of a better name than UDim2
namespace JUI {

    class UDim2 {
    public:
        UDim2(int px, int py, float sx, float sy) {}

        UDim2(Vector2 pixels, Vector2 scale) {}

        static UDim2 FromPixels(int x, int y);

        static UDim2 FromScale(int x, int y);

        Vector2 GetScale();

        Vector2 GetPixels();

    protected:
    private:
        int pixelsX;
        int pixelsY;
        float scaleX;
        float scaleY;
    };
}