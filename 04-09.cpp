#include <cstddef>
#include <type_traits>

template <typename T, T Value> struct IntegralConstant {
  static constexpr T value = Value;
  using ValueType = T;
  using Type = IntegralConstant;
  constexpr operator ValueType() const noexcept { return value; }
  constexpr ValueType operator()() const noexcept { return value; }
};

using TrueType = IntegralConstant<bool, true>;
using FalseType = IntegralConstant<bool, false>;

template <bool B, typename T, typename F> struct Conditional {
  using Type = T;
};

template <typename T, typename F> struct Conditional<false, T, F> {
  using Type = F;
};

template <bool B, typename T, typename F>
using ConditionalT = typename Conditional<B, T, F>::Type;

template <typename T> struct RemoveConst { using Type = T; };

template <typename T> struct RemoveConst<const T> { using Type = T; };

template <typename T> using RemoveConstT = typename RemoveConst<T>::Type;

template <typename T> struct AddConst { using Type = const T; };

template <typename T> using AddConstT = typename AddConst<T>::Type;

template <typename T> struct RemoveVolatile { using Type = T; };

template <typename T> struct RemoveVolatile<volatile T> { using Type = T; };

template <typename T> using RemoveVolatileT = typename RemoveVolatile<T>::Type;

template <typename T> struct RemoveCV {
  using Type = RemoveVolatileT<RemoveConstT<T>>;
};

template <typename T> using RemoveCVT = typename RemoveCV<T>::Type;

template <typename T> struct RemoveReference { using Type = T; };

template <typename T> struct RemoveReference<T &> { using Type = T; };

template <typename T> struct RemoveReference<T &&> { using Type = T; };

template <typename T>
using RemoveReferenceT = typename RemoveReference<T>::Type;

namespace Detail {
template <typename T> auto TestIsClass(int T::*) -> TrueType;

template <typename T> auto TestIsClass(...) -> FalseType;
} // namespace Detail

template <typename T>
struct IsClass : decltype(Detail::TestIsClass<T>(nullptr)) {};

template <typename T> constexpr bool IsClassV = IsClass<T>::value;

namespace Detail {
template <typename T> struct DecayImpl { using Type = RemoveCVT<T>; };

template <typename T, std::size_t N> struct DecayImpl<T[N]> {
  using Type = T *;
};

template <typename T> struct DecayImpl<T[]> { using Type = T *; };

template <typename Ret, typename... Args> struct DecayImpl<Ret(Args...)> {
  using Type = Ret (*)(Args...);
};

template <typename Ret, typename... Args> struct DecayImpl<Ret(Args..., ...)> {
  using Type = Ret (*)(Args..., ...);
};
} // namespace Detail

template <typename T> struct Decay {
  using Type = typename Detail::DecayImpl<RemoveReferenceT<T>>::Type;
};

template <typename T> using DecayT = typename Decay<T>::Type;

struct MyClass {};
union MyUnion {};
struct MyStruct {
  int x;
};

static_assert(IsClassV<MyClass>);
static_assert(IsClassV<MyStruct>);
static_assert(IsClassV<MyUnion>);
static_assert(!IsClassV<int>);
static_assert(!IsClassV<int *>);
static_assert(!IsClassV<void>);

static_assert(std::is_same_v<RemoveConstT<const int>, int>);
static_assert(std::is_same_v<RemoveConstT<int>, int>);
static_assert(std::is_same_v<AddConstT<int>, const int>);

static_assert(std::is_same_v<ConditionalT<true, int, double>, int>);
static_assert(std::is_same_v<ConditionalT<false, int, double>, double>);

static_assert(std::is_same_v<DecayT<int>, int>);
static_assert(std::is_same_v<DecayT<int &>, int>);
static_assert(std::is_same_v<DecayT<int &&>, int>);
static_assert(std::is_same_v<DecayT<const int &>, int>);
static_assert(std::is_same_v<DecayT<int[2]>, int *>);
static_assert(std::is_same_v<DecayT<int(int)>, int (*)(int)>);

int main() { return 0; }