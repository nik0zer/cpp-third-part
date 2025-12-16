module;

#include <compare>
#include <iostream>

export module rational;
export import :mixins;

export namespace Math
{

class Rational :
    public Addable<Rational>,
    public Subtractable<Rational>,
    public Multipliable<Rational>,
    public Dividable<Rational>,
    public Incrementable<Rational>,
    public Decrementable<Rational>
{
public:
    Rational(int num = 0, int den = 1);

    explicit operator double() const;

    Rational& operator+=(const Rational& other);
    Rational& operator-=(const Rational& other);
    Rational& operator*=(const Rational& other);
    Rational& operator/=(const Rational& other);

    Rational& operator++();
    Rational& operator--();

    using Incrementable<Rational>::operator++;
    using Decrementable<Rational>::operator--;

    friend std::strong_ordering operator<=>(const Rational& lhs, const Rational& rhs);
    friend bool operator==(const Rational& lhs, const Rational& rhs);

    friend std::istream& operator>>(std::istream& stream, Rational& rational);
    friend std::ostream& operator<<(std::ostream& stream, const Rational& rational);

private:
    void Reduce();

    int num_;
    int den_;
};

}