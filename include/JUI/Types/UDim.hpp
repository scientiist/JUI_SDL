#pragma once

// Universal dimensions 1D
namespace JUI {
    class UDim {
    public:
        int Pixels;
        float Scale;
        // TODO: Implement Math Operators

        UDim operator+(const UDim& rhs) const;
        UDim operator-(const UDim& rhs) const;
        UDim operator*(float rhs) const;
        UDim operator/(float rhs) const;

    private:
    };

    UDim operator "" _scale(long double sc);
    UDim operator ""_percent(unsigned long long pc);
    UDim operator "" _pixels(unsigned long long px);
    UDim operator "" _px(unsigned long long px);

}