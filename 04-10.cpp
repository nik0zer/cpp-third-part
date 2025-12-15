#include <cstddef>
#include <type_traits>

template <typename... Ts> struct Deque {};

template <typename D> struct Size {};

template <typename... Ts> struct Size<Deque<Ts...>> {
  static constexpr std::size_t value = sizeof...(Ts);
};

template <typename D> constexpr auto sizeV = Size<D>::value;

template <typename D> constexpr auto isEmptyV = sizeV<D> == 0;

template <typename D> struct Front {};

template <typename T, typename... Ts> struct Front<Deque<T, Ts...>> {
  using Type = T;
};

template <typename D> using FrontT = typename Front<D>::Type;

template <typename D> struct PopFront {};

template <typename T, typename... Ts> struct PopFront<Deque<T, Ts...>> {
  using Type = Deque<Ts...>;
};

template <typename D> using PopFrontT = typename PopFront<D>::Type;

template <typename T, typename D, bool IsEmpty = isEmptyV<D>> struct Has {};

template <typename T, typename D> struct Has<T, D, true> {
  static constexpr bool value = false;
};

template <typename T, typename D> struct Has<T, D, false> {
  static constexpr bool value =
      std::is_same_v<T, FrontT<D>> || Has<T, PopFrontT<D>>::value;
};

template <typename T, typename D> constexpr bool hasV = Has<T, D>::value;

int main() {
  using Data = Deque<int, double, char>;

  static_assert(hasV<int, Data>);
  static_assert(hasV<double, Data>);
  static_assert(hasV<char, Data>);
  static_assert(!hasV<float, Data>);

  using Empty = Deque<>;
  static_assert(!hasV<int, Empty>);

  using Duplicates = Deque<int, int, int>;
  static_assert(hasV<int, Duplicates>);
  static_assert(!hasV<double, Duplicates>);
}