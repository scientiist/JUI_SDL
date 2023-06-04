#pragma once

// Universal dimensions 1D
namespace JUI {
    class UDim {
    public:
        int Pixels;
        float Scale;

#pragma region Operators
        UDim operator+(const UDim& rhs) const;
        UDim operator-(const UDim& rhs) const;
        UDim operator*(float rhs) const;
        UDim operator/(float rhs) const;
        // TODO: Implement Math Operators



#pragma endregion


#pragma region Constructors

    UDim();
    UDim(const UDim &u) : Pixels(u.Pixels), Scale(u.Scale) {}


#pragma endregion

#pragma region Methods

#pragma endregion



    private:
    };



#pragma region Unit Shorthands

    UDim operator "" _scale(long double sc);
    UDim operator ""_percent(unsigned long long pc);
    UDim operator "" _pixels(unsigned long long px);
    UDim operator "" _px(unsigned long long px);

#pragma endregion

}