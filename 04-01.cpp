#include <algorithm>
#include <cassert>
#include <cstddef>
#include <iostream>
#include <ranges>
#include <string>
#include <utility>
#include <vector>

const std::size_t SORT_THRESHOLD = 16;

template <typename T>
void Order(std::vector<T> &vector, std::size_t left, std::size_t right) {
  for (auto i = left + 1; i < right; ++i) {
    for (auto j = i; j > left; --j) {
      if (vector[j] < vector[j - 1]) {
        std::swap(vector[j], vector[j - 1]);
      } else {
        break;
      }
    }
  }
}

template <typename T>
std::size_t Partition(std::vector<T> &vector, std::size_t left,
                      std::size_t right) {
  auto mid = left + (right - left) / 2;
  auto last = right - 1;

  if (vector[mid] < vector[left]) {
    std::swap(vector[left], vector[mid]);
  }
  if (vector[last] < vector[left]) {
    std::swap(vector[left], vector[last]);
  }
  if (vector[last] < vector[mid]) {
    std::swap(vector[mid], vector[last]);
  }

  auto pivot = vector[mid];
  auto i = left;
  auto j = right;

  while (true) {
    while (vector[i] < pivot) {
      ++i;
    }

    while (vector[j - 1] > pivot) {
      --j;
    }

    if (i >= j - 1) {
      return j - 1;
    }

    std::swap(vector[i], vector[j - 1]);
    ++i;
    --j;
  }
}

template <typename T>
void Split(std::vector<T> &vector, std::size_t left, std::size_t right) {
  if (right - left > SORT_THRESHOLD) {
    auto pivotIndex = Partition(vector, left, right);
    Split(vector, left, pivotIndex);
    Split(vector, pivotIndex, right);
  } else {
    Order(vector, left, right);
  }
}

template <typename T> void Sort(std::vector<T> &vector) {
  if (!vector.empty()) {
    Split(vector, 0, vector.size());
  }
}

void TestIntegers() {
  std::size_t size = 1000;
  std::vector<int> vector(size);
  for (std::size_t i = 0; i < size; ++i) {
    vector[i] = static_cast<int>(size - i);
  }
  Sort(vector);
  assert(std::ranges::is_sorted(vector));
}

void TestDoubles() {
  std::vector<double> vector = {0.5, 0.1, 0.9, 0.3, 0.2};
  Sort(vector);
  assert(std::ranges::is_sorted(vector));
}

void TestStrings() {
  std::vector<std::string> vector = {"banana", "apple", "cherry", "date"};
  Sort(vector);
  assert(std::ranges::is_sorted(vector));
}

void TestDuplicates() {
  std::vector<int> vector = {5, 1, 5, 2, 5, 3, 5};
  Sort(vector);
  assert(std::ranges::is_sorted(vector));
}

void TestSorted() {
  std::vector<int> vector = {1, 2, 3, 4, 5};
  Sort(vector);
  assert(std::ranges::is_sorted(vector));
}

int main() {
  TestIntegers();
  TestDoubles();
  TestStrings();
  TestDuplicates();
  TestSorted();
  return 0;
}