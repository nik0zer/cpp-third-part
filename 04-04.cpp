#include <cassert>
#include <cmath>
#include <compare>
#include <concepts>
#include <iostream>
#include <numeric>
#include <sstream>
#include <utility>
#include <vector>

const double EPSILON_VAL = 1e-6;

template <typename T> class Rational {
public:
  Rational(T num = 0, T den = 1) : num_(num), den_(den) { Reduce(); }

  explicit operator double() const {
    return static_cast<double>(num_) / static_cast<double>(den_);
  }

  Rational &operator+=(const Rational &other) {
    auto lcm = std::lcm(den_, other.den_);
    num_ = num_ * (lcm / den_) + other.num_ * (lcm / other.den_);
    den_ = lcm;
    Reduce();
    return *this;
  }

  Rational &operator-=(const Rational &other) {
    return *this += Rational(-other.num_, other.den_);
  }

  Rational &operator*=(const Rational &other) {
    num_ *= other.num_;
    den_ *= other.den_;
    Reduce();
    return *this;
  }

  Rational &operator/=(const Rational &other) {
    return *this *= Rational(other.den_, other.num_);
  }

  const Rational operator++(int) {
    auto temp = *this;
    *this += 1;
    return temp;
  }

  const Rational operator--(int) {
    auto temp = *this;
    *this -= 1;
    return temp;
  }

  Rational &operator++() {
    *this += 1;
    return *this;
  }

  Rational &operator--() {
    *this -= 1;
    return *this;
  }

  friend Rational operator+(Rational lhs, const Rational &rhs) {
    return lhs += rhs;
  }

  friend Rational operator-(Rational lhs, const Rational &rhs) {
    return lhs -= rhs;
  }

  friend Rational operator*(Rational lhs, const Rational &rhs) {
    return lhs *= rhs;
  }

  friend Rational operator/(Rational lhs, const Rational &rhs) {
    return lhs /= rhs;
  }

  friend std::strong_ordering operator<=>(const Rational &lhs,
                                          const Rational &rhs) {
    return (lhs.num_ * rhs.den_) <=> (rhs.num_ * lhs.den_);
  }

  friend bool operator==(const Rational &lhs, const Rational &rhs) {
    return lhs.num_ == rhs.num_ && lhs.den_ == rhs.den_;
  }

  friend std::istream &operator>>(std::istream &stream, Rational &rational) {
    char slash = 0;
    stream >> rational.num_ >> slash >> rational.den_;
    rational.Reduce();
    return stream;
  }

  friend std::ostream &operator<<(std::ostream &stream,
                                  const Rational &rational) {
    return stream << rational.num_ << '/' << rational.den_;
  }

private:
  void Reduce() {
    if (den_ < 0) {
      num_ = -num_;
      den_ = -den_;
    }
    auto common = std::gcd(num_, den_);
    num_ /= common;
    den_ /= common;
  }

  T num_ = 0;
  T den_ = 1;
};

bool AreDoublesEqual(double x, double y) {
  return std::abs(x - y) < EPSILON_VAL;
}

void TestInt() {
  using RationalInt = Rational<int>;
  RationalInt x = 1;
  RationalInt y(2, 1);

  assert(AreDoublesEqual(static_cast<double>(x), 1.0));

  assert((x += y) == RationalInt(3, 1));
  assert((x -= y) == RationalInt(1, 1));
  assert((x *= y) == RationalInt(2, 1));
  assert((x /= y) == RationalInt(1, 1));

  assert((x++) == RationalInt(1, 1));
  assert(x == RationalInt(2, 1));
  assert((x--) == RationalInt(2, 1));
  assert(x == RationalInt(1, 1));

  assert((++x) == RationalInt(2, 1));
  assert((--x) == RationalInt(1, 1));

  assert((x + y) == RationalInt(3, 1));
  assert((x - y) == RationalInt(-1, 1));
  assert((x * y) == RationalInt(2, 1));
  assert((x / y) == RationalInt(1, 2));

  assert((x < y));
  assert(!(x > y));
  assert((x <= y));
  assert(!(x >= y));
  assert(x != y);
  assert(!(x == y));

  RationalInt z(1, 1);
  assert(x == z);
}

void TestLongLong() {
  using RationalLL = Rational<long long>;
  RationalLL a(10000000000LL, 2LL);
  RationalLL b(5000000000LL, 1LL);

  assert(a == b);
  assert(!(a < b));
  assert(!(a > b));
  assert(a <= b);
  assert(a >= b);
  assert(a == b);
}

void TestIO() {
  using RationalInt = Rational<int>;
  std::stringstream ss;
  RationalInt r(3, 4);
  ss << r;
  assert(ss.str() == "3/4");

  RationalInt r2;
  std::stringstream input("5/2");
  input >> r2;
  assert(r2 == RationalInt(5, 2));
}

int main() {
  TestInt();
  TestLongLong();
  TestIO();
  return 0;
}