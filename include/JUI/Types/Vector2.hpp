// Straightforward implementation of 2-Dimensional Vector

#pragma once

#include <ostream>
#include <cmath>
#include <algorithm>

// TODO: Consider generalizing the type with templates

//float lerp(float a, float b, float t) { return a + t * (b - a); }

namespace JUI {
    class Vector2 {
    public:
#pragma region Static Members
        static const Vector2 Zero;
        static const Vector2 One;
#pragma endregion

#pragma region Constructors

        Vector2() : X(0), Y(0) {}

        Vector2(float const &x, float const &y) : X(x), Y(y) {}

        Vector2(const Vector2 &v) : X(v.GetX()), Y(v.GetY()) {}

#pragma endregion

#pragma region Static Methods

        static Vector2 Max(Vector2 const &input, Vector2 const &max);

        static Vector2 Min(Vector2 const &input, Vector2 const &min);

        static Vector2 Perp(Vector2 const &rhs);

        static Vector2 Clamp(const Vector2 &input, Vector2 const &min, Vector2 const &max);

        static Vector2 Lerp(Vector2 const &start, Vector2 const &goal, float alpha);

        static float Dot(Vector2 const &rhs, Vector2 const &lhs);

        static float Magnitude(Vector2 const &vec);

        static float Distance(Vector2 const &, Vector2 const &);

#pragma endregion

#pragma region Operators

        friend Vector2 operator*(float t, Vector2 const &rhs);

        friend std::ostream &operator<<(std::ostream &os, const Vector2 &vector);

        bool operator==(const Vector2 &rhs) const;

        bool operator!=(const Vector2 &rhs) const;

        Vector2 &operator=(const Vector2 &) = default;

        Vector2 operator+(const Vector2 &rhs) const;

        Vector2 operator-(const Vector2 &rhs) const;

        Vector2 operator*(const Vector2 &rhs) const;

        Vector2 operator/(const Vector2 &rhs) const;

        Vector2 operator*(float rhs) const;

        Vector2 operator/(float rhs) const;

#pragma endregion

#pragma region Member Methods

        bool Equals(const Vector2 &rhs, float marginOfError = 0.0001f) {

        }

        float GetX() const { return this->X; }

        float GetY() const { return this->Y; }

        Vector2 Max(const Vector2 &max) const;

        Vector2 Min(const Vector2 &min) const;

        Vector2 Normalize() const;

        Vector2 Floor() const;

        Vector2 Ceil() const;

        Vector2 Perp() const;

        Vector2 Clamp(Vector2 const &min, Vector2 const &max) const;

        Vector2 Lerp(Vector2 const &goal, float alpha) const;

        Vector2 Project(Vector2 const &rhs) const;

        Vector2 Unit() const;

        float Dot(Vector2 const &against) const;

        float Magnitude() const;

        float Distance(const Vector2 &to) const;

        float GetAngle() const {
            return std::atan2(Y, X);
        }

        float GetAngleBetween(const Vector2 &rhs) const {
            auto numerator = this->Dot(rhs);
            auto denominator = this->Magnitude() * rhs.Magnitude();
            return std::acos(numerator / denominator);
        }

#pragma endregion

        float X;
        float Y;
    private:
    };
}