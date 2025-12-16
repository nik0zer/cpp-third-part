import rational;
#include <cassert>
#include <sstream>
#include <cmath>

const double EPSILON_VAL = 1e-6;

bool AreDoublesEqual(double x, double y)
{
    return std::abs(x - y) < EPSILON_VAL;
}

void TestAll()
{
    using Math::Rational;
    Rational x(1, 2);
    Rational y(1, 3);
    Rational sum = x + y;
    assert(sum == Rational(5, 6));

    std::stringstream ss;
    ss << sum;
    assert(ss.str() == "5/6");
}

int main()
{
    TestAll();
    return 0;
}