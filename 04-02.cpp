#include <cassert>
#include <cmath>
#include <concepts>
#include <limits>

const double EPSILON_VAL = 1e-9;

bool AreEqual(double a, double b) { return std::abs(a - b) < EPSILON_VAL; }

double Minimum(double val) { return val; }

template <typename... Args> double Minimum(double first, Args... args) {
  double rest = Minimum(args...);
  return (first < rest) ? first : rest;
}

double Maximum(double val) { return val; }

template <typename... Args> double Maximum(double first, Args... args) {
  double rest = Maximum(args...);
  return (first > rest) ? first : rest;
}

template <typename... Args> double Sum(Args... args) { return (args + ...); }

template <typename... Args> double Average(Args... args) {
  return (args + ...) / static_cast<double>(sizeof...(args));
}

void TestMinimum() {
  assert(AreEqual(Minimum(10.0, 20.0, 5.0, 30.0), 5.0));
  assert(AreEqual(Minimum(1.0), 1.0));
  assert(AreEqual(Minimum(-5.0, -10.0, 0.0), -10.0));
  assert(AreEqual(Minimum(5.0, 5.0, 5.0), 5.0));
}

void TestMaximum() {
  assert(AreEqual(Maximum(10.0, 20.0, 5.0, 30.0), 30.0));
  assert(AreEqual(Maximum(1.0), 1.0));
  assert(AreEqual(Maximum(-5.0, -10.0, 0.0), 0.0));
  assert(AreEqual(Maximum(5.0, 5.0, 5.0), 5.0));
}

void TestSum() {
  assert(AreEqual(Sum(1.0, 2.0, 3.0), 6.0));
  assert(AreEqual(Sum(1.5, 2.5), 4.0));
  assert(AreEqual(Sum(-5.0, 5.0), 0.0));
  assert(AreEqual(Sum(10.0), 10.0));
}

void TestAverage() {
  assert(AreEqual(Average(2.0, 4.0), 3.0));
  assert(AreEqual(Average(1.0, 2.0, 3.0, 4.0), 2.5));
  assert(AreEqual(Average(10.0), 10.0));
  assert(AreEqual(Average(0.0, 10.0), 5.0));
}

int main() {
  TestMinimum();
  TestMaximum();
  TestSum();
  TestAverage();
  return 0;
}