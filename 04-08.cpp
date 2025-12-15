#include <cassert>
#include <cstddef>
#include <string>
#include <utility>

template <typename... Ts> class Tuple {};

template <typename T, typename... Ts> class Tuple<T, Ts...> {
public:
  constexpr Tuple(T &&head, Ts &&...tail)
      : head_(std::forward<T>(head)), tail_(std::forward<Ts>(tail)...) {}

  template <std::size_t I> constexpr auto Get() const {
    if constexpr (I > 0) {
      return tail_.template Get<I - 1>();
    } else {
      return head_;
    }
  }

  constexpr std::size_t Size() const { return 1 + sizeof...(Ts); }

private:
  T head_;
  Tuple<Ts...> tail_;
};

constexpr bool TestTuple() {
  Tuple<int, int, int> t(1, 2, 3);
  return t.Size() == 3 && t.Get<0>() == 1 && t.Get<1>() == 2 && t.Get<2>() == 3;
}

static_assert(TestTuple());
static_assert(Tuple<int>(10).Size() == 1);
static_assert(Tuple<int>(10).Get<0>() == 10);

int main() {
  Tuple<int, double, std::string> tuple(1, 2.0, "aaaaa");
  assert(tuple.Get<0>() == 1);
  assert(tuple.Size() == 3);

  return 0;
}