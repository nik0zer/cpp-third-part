#include <array>
#include <numbers>

constexpr double ABS_TOLERANCE_MULTIPLIER = 1.1;

constexpr double Abs(double value) { return value < 0.0 ? -value : value; }

consteval double CalculatePi(double epsilon) {
  double pi = 0.0;
  double denominator = 1.0;
  double sign = 1.0;

  while (true) {
    double term = 4.0 / denominator;
    if (term < epsilon) {
      break;
    }
    pi += sign * term;
    sign = -sign;
    denominator += 2.0;
  }
  return pi;
}

consteval double CalculateE(double epsilon) {
  double e = 1.0;
  double term = 1.0;
  double n = 1.0;

  while (true) {
    term /= n;
    if (term < epsilon) {
      break;
    }
    e += term;
    n += 1.0;
  }
  return e;
}

constexpr std::array EPSILON_VALUES = {1e-1, 1e-2, 1e-3, 1e-4};

static_assert(Abs(CalculatePi(EPSILON_VALUES[0]) - std::numbers::pi) <
              EPSILON_VALUES[0] * ABS_TOLERANCE_MULTIPLIER);
static_assert(Abs(CalculatePi(EPSILON_VALUES[1]) - std::numbers::pi) <
              EPSILON_VALUES[1] * ABS_TOLERANCE_MULTIPLIER);
static_assert(Abs(CalculatePi(EPSILON_VALUES[2]) - std::numbers::pi) <
              EPSILON_VALUES[2] * ABS_TOLERANCE_MULTIPLIER);
static_assert(Abs(CalculatePi(EPSILON_VALUES[3]) - std::numbers::pi) <
              EPSILON_VALUES[3] * ABS_TOLERANCE_MULTIPLIER);

static_assert(Abs(CalculateE(EPSILON_VALUES[0]) - std::numbers::e) <
              EPSILON_VALUES[0] * ABS_TOLERANCE_MULTIPLIER);
static_assert(Abs(CalculateE(EPSILON_VALUES[1]) - std::numbers::e) <
              EPSILON_VALUES[1] * ABS_TOLERANCE_MULTIPLIER);
static_assert(Abs(CalculateE(EPSILON_VALUES[2]) - std::numbers::e) <
              EPSILON_VALUES[2] * ABS_TOLERANCE_MULTIPLIER);
static_assert(Abs(CalculateE(EPSILON_VALUES[3]) - std::numbers::e) <
              EPSILON_VALUES[3] * ABS_TOLERANCE_MULTIPLIER);

int main() { return 0; }