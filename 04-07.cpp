#include <cassert>
#include <numeric>
#include <type_traits>
#include <utility>

template <int N = 0, int D = 1> struct Ratio {
  static constexpr auto num = N;
  static constexpr auto den = D;
};

template <typename R1, typename R2> struct Sum {
  static constexpr auto rawNum = R1::num * R2::den + R2::num * R1::den;
  static constexpr auto rawDen = R1::den * R2::den;
  static constexpr auto common = std::gcd(rawNum, rawDen);

  static constexpr auto num = (rawDen < 0 ? -rawNum : rawNum) / common;
  static constexpr auto den = (rawDen < 0 ? -rawDen : rawDen) / common;

  using type = Ratio<num, den>;
};

template <typename R1, typename R2> using sum = typename Sum<R1, R2>::type;

template <typename R1, typename R2> struct Sub {
  using type = typename Sum<R1, Ratio<-R2::num, R2::den>>::type;
};

template <typename R1, typename R2> using sub = typename Sub<R1, R2>::type;

template <typename R1, typename R2> struct Mul {
  static constexpr auto rawNum = R1::num * R2::num;
  static constexpr auto rawDen = R1::den * R2::den;
  static constexpr auto common = std::gcd(rawNum, rawDen);

  static constexpr auto num = (rawDen < 0 ? -rawNum : rawNum) / common;
  static constexpr auto den = (rawDen < 0 ? -rawDen : rawDen) / common;

  using type = Ratio<num, den>;
};

template <typename R1, typename R2> using mul = typename Mul<R1, R2>::type;

template <typename R1, typename R2> struct Div {
  static_assert(R2::num != 0, "Division by zero");
  using type = typename Mul<R1, Ratio<R2::den, R2::num>>::type;
};

template <typename R1, typename R2> using div = typename Div<R1, R2>::type;

template <typename T, typename R = Ratio<1>> struct Duration {
  constexpr Duration(T v = T()) : x(v) {}
  T x;
};

template <typename T1, typename R1, typename T2, typename R2>
constexpr auto operator+(Duration<T1, R1> const &lhs,
                         Duration<T2, R2> const &rhs) {
  using ratio_t = Ratio<1, sum<R1, R2>::den>;

  auto x = (lhs.x * ratio_t::den / R1::den * R1::num +
            rhs.x * ratio_t::den / R2::den * R2::num);

  return Duration<decltype(x), ratio_t>(x);
}

template <typename T1, typename R1, typename T2, typename R2>
constexpr auto operator-(Duration<T1, R1> const &lhs,
                         Duration<T2, R2> const &rhs) {
  Duration<T2, R2> negatedRhs(-rhs.x);
  return lhs + negatedRhs;
}

int main() {
  static_assert(sum<Ratio<1, 2>, Ratio<1, 3>>::num == 5);
  static_assert(sum<Ratio<1, 2>, Ratio<1, 3>>::den == 6);

  static_assert(sub<Ratio<1, 2>, Ratio<1, 3>>::num == 1);
  static_assert(sub<Ratio<1, 2>, Ratio<1, 3>>::den == 6);

  static_assert(sub<Ratio<1, 3>, Ratio<1, 2>>::num == -1);
  static_assert(sub<Ratio<1, 3>, Ratio<1, 2>>::den == 6);

  static_assert(mul<Ratio<2, 3>, Ratio<3, 4>>::num == 1);
  static_assert(mul<Ratio<2, 3>, Ratio<3, 4>>::den == 2);

  static_assert(div<Ratio<1, 2>, Ratio<1, 4>>::num == 2);
  static_assert(div<Ratio<1, 2>, Ratio<1, 4>>::den == 1);

  static_assert(div<Ratio<1, 2>, Ratio<-1, 2>>::num == -1);
  static_assert(div<Ratio<1, 2>, Ratio<-1, 2>>::den == 1);

  auto x = 1, y = 2;
  Duration<int, Ratio<1, 2>> d1(x);
  Duration<int, Ratio<1, 3>> d2(y);

  auto d3 = d1 + d2;
  assert(d3.x == 7);
  static_assert(std::is_same_v<decltype(d3), Duration<int, Ratio<1, 6>>>);

  auto d4 = d1 - d2;

  assert(d4.x == -1);
  static_assert(std::is_same_v<decltype(d4), Duration<int, Ratio<1, 6>>>);

  return 0;
}