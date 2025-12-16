#include "Rational.hpp"

Rational::Rational(int num, int den) : num_(num), den_(den)
{
    Reduce();
}

Rational::operator double() const
{
    return static_cast<double>(num_) / static_cast<double>(den_);
}

Rational& Rational::operator+=(const Rational& other)
{
    auto lcm = std::lcm(den_, other.den_);
    num_ = num_ * (lcm / den_) + other.num_ * (lcm / other.den_);
    den_ = lcm;
    Reduce();
    return *this;
}

Rational& Rational::operator-=(const Rational& other)
{
    return *this += Rational(-other.num_, other.den_);
}

Rational& Rational::operator*=(const Rational& other)
{
    num_ *= other.num_;
    den_ *= other.den_;
    Reduce();
    return *this;
}

Rational& Rational::operator/=(const Rational& other)
{
    return *this *= Rational(other.den_, other.num_);
}

Rational& Rational::operator++()
{
    return *this += 1;
}

Rational& Rational::operator--()
{
    return *this -= 1;
}

std::strong_ordering operator<=>(const Rational& lhs, const Rational& rhs)
{
    return (lhs.num_ * rhs.den_) <=> (rhs.num_ * lhs.den_);
}

bool operator==(const Rational& lhs, const Rational& rhs)
{
    return lhs.num_ == rhs.num_ && lhs.den_ == rhs.den_;
}

std::istream& operator>>(std::istream& stream, Rational& rational)
{
    char slash = 0;
    stream >> rational.num_ >> slash >> rational.den_;
    rational.Reduce();
    return stream;
}

std::ostream& operator<<(std::ostream& stream, const Rational& rational)
{
    return stream << rational.num_ << '/' << rational.den_;
}

void Rational::Reduce()
{
    if (den_ < 0)
    {
        num_ = -num_;
        den_ = -den_;
    }
    auto common = std::gcd(num_, den_);
    num_ /= common;
    den_ /= common;
}