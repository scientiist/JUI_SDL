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

#pragma region Operators
        UDim2 operator+(const UDim2& rhs) const;
        UDim2 operator-(const UDim2& rhs) const;
        UDim2 operator*(float rhs) const;
        UDim2 operator/(float rhs) const;
#pragma endregion

#pragma region Constructors
        UDim2();
        UDim2(int px, int py, float sx, float sy);
        UDim2(Vector2 pixels, Vector2 scale);
        UDim2(UDim x, UDim y);
        static UDim2 FromPixels(int x, int y);
        static UDim2 FromScale(float x, float y);

#pragma endregion

#pragma region Methods
        Vector2 GetScale() const;
        Vector2 GetPixels() const;
#pragma endregion

    protected:
    private:
    };
}