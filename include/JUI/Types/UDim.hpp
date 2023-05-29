#pragma once

// Universal dimensions 1D
namespace JUI {
    class UDim {
    public:
        int Pixels;
        float Scale;
        // TODO: Implement Math Operators

        UDim operator+(const UDim& rhs) const { return {Pixels+rhs.Pixels, Scale+rhs.Scale}; }
        UDim operator-(const UDim& rhs) const { return {Pixels-rhs.Pixels, Scale-rhs.Scale}; }
        UDim operator*(float rhs) const { return {static_cast<int>(Pixels*rhs), Scale*rhs}; }
        UDim operator/(float rhs) const { return {static_cast<int>(Pixels/rhs), Scale*rhs}; }

    private:
    };

    UDim operator "" _scale(long double sc)
    {
        return {0, static_cast<float>(sc)};
    }

    UDim operator ""_percent(unsigned long long pc)
    {
        return {0, pc/100.0f};
    }

    UDim operator "" _pixels(unsigned long long px)
    {
        return {static_cast<int>(px), 0.0f};
    }

    UDim operator "" _px(unsigned long long px)
    {
        return {static_cast<int>(px), 0.0f};
    }
}