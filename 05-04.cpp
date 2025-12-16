#include <cassert>

class AdditionStrategy {
public:
  int Execute(int a, int b) const { return a + b; }
};

class SubtractionStrategy {
public:
  int Execute(int a, int b) const { return a - b; }
};

class MultiplicationStrategy {
public:
  int Execute(int a, int b) const { return a * b; }
};

template <typename TStrategy> class Entity : public TStrategy {
public:
  int Compute(int a, int b) const { return this->Execute(a, b); }
};

void TestAddition() {
  Entity<AdditionStrategy> entity;
  assert(entity.Compute(10, 20) == 30);
  assert(entity.Compute(-5, 5) == 0);
}

void TestSubtraction() {
  Entity<SubtractionStrategy> entity;
  assert(entity.Compute(10, 20) == -10);
  assert(entity.Compute(50, 10) == 40);
}

void TestMultiplication() {
  Entity<MultiplicationStrategy> entity;
  assert(entity.Compute(10, 20) == 200);
  assert(entity.Compute(3, 3) == 9);
}

int main() {
  TestAddition();
  TestSubtraction();
  TestMultiplication();
  return 0;
}