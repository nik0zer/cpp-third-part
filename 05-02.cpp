#include <cassert>
#include <iostream>
#include <string>
#include <utility>

class Entity {
public:
  virtual ~Entity() = default;
  virtual std::string GetData() const = 0;
};

class ConcreteEntity : public virtual Entity {
public:
  std::string GetData() const override { return "Concrete"; }
};

template <typename Base> class Decorator : public Base, public virtual Entity {
public:
};

template <typename Base> class BracketDecorator : public Decorator<Base> {
public:
  std::string GetData() const override { return "[" + Base::GetData() + "]"; }
};

template <typename Base> class ParenDecorator : public Decorator<Base> {
public:
  std::string GetData() const override { return "(" + Base::GetData() + ")"; }
};

template <typename Base> class BraceDecorator : public Decorator<Base> {
public:
  std::string GetData() const override { return "{" + Base::GetData() + "}"; }
};

void TestConcrete() {
  ConcreteEntity entity;
  assert(entity.GetData() == "Concrete");
}

void TestSingleDecoration() {
  BracketDecorator<ConcreteEntity> entity;
  assert(entity.GetData() == "[Concrete]");
}

void TestMultipleDecoration() {
  ParenDecorator<BracketDecorator<ConcreteEntity>> entity;
  assert(entity.GetData() == "([Concrete])");
}

void TestComplexDecoration() {
  BraceDecorator<ParenDecorator<BracketDecorator<ConcreteEntity>>> entity;
  assert(entity.GetData() == "{([Concrete])}");
}

void TestAmbiguityResolution() {
  BracketDecorator<ParenDecorator<ConcreteEntity>> entity;
  const Entity &interfaceRef = entity;
  assert(interfaceRef.GetData() == "[(Concrete)]");
}

int main() {
  TestConcrete();
  TestSingleDecoration();
  TestMultipleDecoration();
  TestComplexDecoration();
  TestAmbiguityResolution();
  return 0;
}