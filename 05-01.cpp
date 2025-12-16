#include <cassert>
#include <string>
#include <utility>

class Person {
public:
  void SetName(std::string name) { name_ = std::move(name); }

  const std::string &GetName() const { return name_; }

  void SetAge(int age) { age_ = age; }

  int GetAge() const { return age_; }

  void SetGrade(int grade) { grade_ = grade; }

  int GetGrade() const { return grade_; }

private:
  std::string name_;
  int age_ = 0;
  int grade_ = 0;
};

class Builder {
public:
  Builder() = default;

  Builder &Name(std::string name) {
    person_.SetName(std::move(name));
    return *this;
  }

  Builder &Age(int age) {
    person_.SetAge(age);
    return *this;
  }

  Builder &Grade(int grade) {
    person_.SetGrade(grade);
    return *this;
  }

  Person Get() { return std::move(person_); }

private:
  Person person_;
};

void TestBuilder() {
  Builder builder;
  Person person = builder.Name("Ivan").Age(25).Grade(10).Get();

  assert(person.GetName() == "Ivan");
  assert(person.GetAge() == 25);
  assert(person.GetGrade() == 10);
}

void TestDefaults() {
  Builder builder;
  Person person = builder.Get();

  assert(person.GetName().empty());
  assert(person.GetAge() == 0);
  assert(person.GetGrade() == 0);
}

void TestPartialBuild() {
  Builder builder;
  Person person = builder.Name("Maria").Grade(5).Get();

  assert(person.GetName() == "Maria");
  assert(person.GetAge() == 0);
  assert(person.GetGrade() == 5);
}

int main() {
  TestBuilder();
  TestDefaults();
  TestPartialBuild();
  return 0;
}