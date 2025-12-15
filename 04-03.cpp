#include <cassert>
#include <string>
#include <type_traits>
#include <utility>
#include <vector>

template <typename Container> void Handle(Container &container, int value) {
  container.push_back(value);
}

template <typename Container, typename T> void Handle(Container &, T &&) {
  // ignore
}

template <typename Container, typename... Args>
void InsertInts(Container &container, Args &&...args) {
  (Handle(container, std::forward<Args>(args)), ...);
}

void TestMixedArguments() {
  std::vector<int> numbers;
  InsertInts(numbers, 1, "ignore", 2.5, 3, 'c', 4);

  assert(numbers.size() == 3);
  assert(numbers[0] == 1);
  assert(numbers[1] == 3);
  assert(numbers[2] == 4);
}

void TestOnlyInts() {
  std::vector<int> numbers;
  InsertInts(numbers, 10, 20, 30);

  assert(numbers.size() == 3);
  assert(numbers[0] == 10);
  assert(numbers[1] == 20);
  assert(numbers[2] == 30);
}

void TestNoInts() {
  std::vector<int> numbers;
  InsertInts(numbers, 1.1, "string", true);

  assert(numbers.empty());
}

void TestLValues() {
  std::vector<int> numbers;
  int x = 5;
  const int y = 6;
  double d = 7.0;

  InsertInts(numbers, x, y, d);

  assert(numbers.size() == 2);
  assert(numbers[0] == 5);
  assert(numbers[1] == 6);
}

void TestEmptyPack() {
  std::vector<int> numbers;
  InsertInts(numbers);

  assert(numbers.empty());
}

int main() {
  TestMixedArguments();
  TestOnlyInts();
  TestNoInts();
  TestLValues();
  TestEmptyPack();
  return 0;
}