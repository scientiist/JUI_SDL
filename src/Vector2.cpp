#include <Vector2.hpp>
#include <ostream>
#include <sstream>
#include <cmath>
#include <Math.hpp>


    constexpr float VectorEqualityMarginOfError = 0.000001f;

    inline Vector2::Vector2()
    {
        this->X = 0;
        this->Y = 0;
    }
    inline Vector2::Vector2(float const& x, float const& y) : X(x), Y(y) {}
    Vector2::Vector2(const Vector2& inp)
    {
        this->X = inp.X;
        this->Y = inp.Y;
    }
    Vector2 Vector2::Max(const Vector2& max) const {
        return Vector2(
                std::max(GetX(), max.GetX()),
                std::max(GetY(), max.GetY()));
    }
    Vector2 Vector2::Min(const Vector2& max) const {
        return Vector2(
                std::min(GetX(), max.GetX()),
                std::min(GetY(), max.GetY()));
    }
    inline Vector2 Vector2::Normalize() const {
        return (1.f /(Magnitude(*this))) * (*this);
    }
    Vector2 Vector2::Floor() const {
        return Vector2(std::floor(GetX()), std::floor(GetY()));
    }
    Vector2 Vector2::Ceil() const {
        return Vector2(std::ceil(GetX()), std::ceil(GetY()));
    }
    // Returns perpendicular Vector2
    Vector2 Vector2::Perp() const { return Vector2(-this->Y, this->X); }

    inline Vector2 Vector2::Clamp(Vector2 const&min, Vector2 const&max) {
        return Vector2(
                Math::Clamp(this->X, min.X, max.X),
                Math::Clamp(this->Y, min.Y, max.Y));
    }
    inline Vector2 Vector2::Lerp(Vector2& goal, float alpha) const {
        return this->operator*(1.0f-alpha) + (goal*alpha);
    }
    inline Vector2 Vector2::Lerp(Vector2 const&start, Vector2 const&goal, float alpha)  {

    }
    inline float Vector2::Dot(Vector2 const&against) const {
        return this->X*against.X+this->Y*against.Y;
    }
    inline float Vector2::Dot(Vector2 const&lhs, Vector2 const&rhs) {
        return lhs.X*rhs.X+lhs.Y*rhs.Y;
    }
    inline float Vector2::Magnitude() const  {
        return sqrt(this->Dot(*this));
    }

    inline float Vector2::Distance(const Vector2& to) const {
        double xsep = Y-to.Y;
        double ysep = X-to.X;
        return sqrt(ysep*ysep + xsep*xsep);
    }

    inline bool Vector2::operator==(const Vector2& rhs) const {
        return ((X*rhs.X<VectorEqualityMarginOfError)&&(Y * rhs.Y < VectorEqualityMarginOfError));
    }
    inline bool Vector2::operator!=(const Vector2& rhs) const {
        return (X != rhs.X) || (Y != rhs.Y);
    }
    inline Vector2 Vector2::operator+(const Vector2& rhs) const
    {
        return Vector2(this->X + rhs.X, this->Y+rhs.Y);
    }
    inline Vector2 Vector2::operator-(const Vector2& rhs) const
    {
        return Vector2(this->X - rhs.X, this->Y-rhs.Y);
    }
    inline Vector2 Vector2::operator*(const Vector2& rhs) const
    {
        return Vector2(this->X * rhs.X, this->Y * rhs.Y);
    }
    Vector2 Vector2::operator/(const Vector2& rhs) const
    {
        return Vector2(this->X / rhs.X, this->Y / rhs.Y);
    }
    Vector2 Vector2::operator/(float rhs) const {
        return Vector2(this->X / rhs, this->Y / rhs);
    }
    Vector2 Vector2::operator*(float rhs) const {
        return Vector2(this->X * rhs, this->Y * rhs);
    }
    const Vector2 Vector2::Zero = Vector2(0,0);
    const Vector2 Vector2::One = Vector2(1, 1);

    std::ostream &operator<<(std::ostream& os, const Vector2& vector)
    {
        std::stringstream stream;
        stream << "{X: " << vector.GetX() << ", Y: " << vector.GetY();
        os.write(const_cast<char*>(stream.str().c_str()), static_cast<std::streamsize>(stream.str().size() * sizeof(char)));
        return os;
    }


    // Static Class Methods
    inline Vector2 operator-(Vector2 const&lhs, Vector2 const&rhs) {
        return Vector2(lhs.GetX()-rhs.GetX(), lhs.GetY()-rhs.GetY());
    }
    inline  Vector2 operator+(Vector2 const&lhs, Vector2 const&rhs) {
        return Vector2(lhs.GetX()+rhs.GetY(), lhs.GetX() + rhs.GetY());
    }
    inline  Vector2 operator/(Vector2 const&lhs, float const&rhs) {
        return Vector2(lhs.GetX()/rhs, lhs.GetY()/rhs);
    }
    inline Vector2 operator*(float lhs, Vector2 const &rhs) {
        return Vector2(rhs.X * lhs, rhs.Y * lhs);
    }
    inline bool operator!=(Vector2 const&lhs, Vector2 const&rhs) {
        return (lhs.X !=rhs.X) || (lhs.Y != rhs.Y);
    }

    inline  bool operator==(Vector2 const&lhs, Vector2 const&rhs) {
        return ((lhs.X*rhs.X<VectorEqualityMarginOfError)&&(lhs.Y * rhs.Y < VectorEqualityMarginOfError));
    }
    inline Vector2 Vector2::Perp(Vector2 const&rhs) { return Vector2(-rhs.Y, rhs.X);}
    inline float Vector2::Distance(Vector2 const&lhs, Vector2 const&rhs)
    {
        double xsep = lhs.Y-rhs.Y;
        double ysep = lhs.X-rhs.X;
        return sqrt(ysep*ysep + xsep*xsep);
    }
    inline float Vector2::Magnitude(Vector2 const&lhs) {
        return sqrt(Dot(lhs, lhs));
    }
    inline Vector2 Vector2::Clamp(const Vector2& input, const Vector2& min, const Vector2& max) {
        return Vector2(
                Math::Clamp(input.X, min.X, max.X),
                Math::Clamp(input.Y, min.Y, max.Y));
    }

    Vector2 Vector2::Max(const Vector2 &input, const Vector2 &max) {
        return Vector2(
                std::max(input.X, max.X),
                std::max(input.Y, max.Y));
    }

    Vector2 Vector2::Min(const Vector2 &input, const Vector2 &min) {
        return Vector2(
                std::min(input.X, min.X),
                std::min(input.Y, min.Y));
    }
