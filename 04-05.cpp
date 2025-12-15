#include <limits>

template <int N> struct Fibonacci {
  static constexpr int previousValue1 = Fibonacci<N - 1>::value;
  static constexpr int previousValue2 = Fibonacci<N - 2>::value;

  static_assert(std::numeric_limits<int>::max() - previousValue1 >=
                    previousValue2,
                "Integer overflow detected in Fibonacci calculation");

  static constexpr int value = previousValue1 + previousValue2;
};

template <> struct Fibonacci<1> { static constexpr int value = 1; };

template <> struct Fibonacci<2> { static constexpr int value = 1; };

template <int N> constexpr int Fibonacci_v = Fibonacci<N>::value;

int main() {
  static_assert(Fibonacci_v<1> == 1);
  static_assert(Fibonacci_v<2> == 1);
  static_assert(Fibonacci_v<3> == 2);
  static_assert(Fibonacci_v<4> == 3);
  static_assert(Fibonacci_v<5> == 5);
  static_assert(Fibonacci_v<6> == 8);
  static_assert(Fibonacci_v<7> == 13);
  static_assert(Fibonacci_v<8> == 21);
  static_assert(Fibonacci_v<10> == 55);
  static_assert(Fibonacci_v<20> == 6765);
  static_assert(Fibonacci_v<30> == 832040);
  static_assert(Fibonacci_v<46> == 1836311903);

  return 0;
}