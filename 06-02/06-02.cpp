import rational;
#include <cassert>
#include <cmath>
#include <sstream>

const double EPSILON_VAL = 1e-6;

bool AreDoublesEqual(double x, double y)
{
    return std::abs(x - y) < EPSILON_VAL;
}

void TestArithmetic()
{
    using Math::Rational;
    Rational x(1, 2);
    Rational y(1, 3);

    Rational sum = x + y;
    assert(sum == Rational(5, 6));

    Rational diff = x - y;
    assert(diff == Rational(1, 6));

    Rational prod = x * y;
    assert(prod == Rational(1, 6));

    Rational quot = x / y;
    assert(quot == Rational(3, 2));
}

void TestIncrementDecrement()
{
    using Math::Rational;
    Rational x(1, 1);

    assert(++x == Rational(2, 1));
    assert(x == Rational(2, 1));

    assert(x++ == Rational(2, 1));
    assert(x == Rational(3, 1));

    assert(--x == Rational(2, 1));
    assert(x == Rational(2, 1));

    assert(x-- == Rational(2, 1));
    assert(x == Rational(1, 1));
}

void TestComparison()
{
    using Math::Rational;
    Rational a(1, 2);
    Rational b(2, 4);
    Rational c(1, 3);

    assert(a == b);
    assert(a != c);
    assert(a > c);
    assert(c < a);
    assert(a >= b);
    assert(a <= b);
}

void TestIO()
{
    using Math::Rational;
    std::stringstream ss;
    Rational r(3, 4);
    ss << r;
    assert(ss.str() == "3/4");

    Rational r2;
    std::stringstream input("5/8");
    input >> r2;
    assert(r2 == Rational(5, 8));
}

void TestDoubleConversion()
{
    using Math::Rational;
    Rational r(1, 2);
    assert(AreDoublesEqual(static_cast<double>(r), 0.5));
}

int main()
{
    TestArithmetic();
    TestIncrementDecrement();
    TestComparison();
    TestIO();
    TestDoubleConversion();
    return 0;
}