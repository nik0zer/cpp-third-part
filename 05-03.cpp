#include <algorithm>
#include <cassert>
#include <iostream>
#include <memory>
#include <numeric>
#include <sstream>
#include <string>
#include <vector>

const int DEFAULT_HEALTH = 100;
const int DEFAULT_DAMAGE = 10;

class GameUnit {
public:
  virtual ~GameUnit() = default;

  void PlayTurn() {
    Prepare();
    Execute();
    Recover();
  }

  virtual void Add(std::shared_ptr<GameUnit> unit) { (void)unit; }

  virtual int GetTotalPower() const = 0;
  virtual std::string GetStatus() const = 0;

protected:
  virtual void Prepare() = 0;
  virtual void Execute() = 0;
  virtual void Recover() = 0;
};

class Soldier : public GameUnit {
public:
  Soldier(std::string name, int health, int damage)
      : name_(std::move(name)), health_(health), damage_(damage),
        status_("Idle") {}

  int GetTotalPower() const override { return damage_; }

  std::string GetStatus() const override { return status_; }

protected:
  void Prepare() override { status_ = name_ + " preparing weapon"; }

  void Execute() override {
    status_ = name_ + " attacking with " + std::to_string(damage_) + " damage";
  }

  void Recover() override { status_ = name_ + " reloading"; }

private:
  std::string name_;
  int health_;
  int damage_;
  std::string status_;
};

class Squad : public GameUnit {
public:
  void Add(std::shared_ptr<GameUnit> unit) override { units_.push_back(unit); }

  int GetTotalPower() const override {
    int total = 0;
    for (const auto &unit : units_) {
      total += unit->GetTotalPower();
    }
    return total;
  }

  std::string GetStatus() const override { return lastLog_; }

protected:
  void Prepare() override { lastLog_ = "Squad formation set"; }

  void Execute() override {
    for (auto &unit : units_) {
      unit->PlayTurn();
    }
    lastLog_ = "Squad attack coordinated";
  }

  void Recover() override { lastLog_ = "Squad regrouping"; }

private:
  std::vector<std::shared_ptr<GameUnit>> units_;
  std::string lastLog_;
};

class SoldierBuilder {
public:
  SoldierBuilder() { Reset(); }

  SoldierBuilder &SetName(std::string name) {
    name_ = std::move(name);
    return *this;
  }

  SoldierBuilder &SetHealth(int health) {
    health_ = health;
    return *this;
  }

  SoldierBuilder &SetDamage(int damage) {
    damage_ = damage;
    return *this;
  }

  std::shared_ptr<Soldier> Build() {
    auto soldier = std::make_shared<Soldier>(name_, health_, damage_);
    Reset();
    return soldier;
  }

private:
  void Reset() {
    name_ = "Unknown";
    health_ = DEFAULT_HEALTH;
    damage_ = DEFAULT_DAMAGE;
  }

  std::string name_;
  int health_;
  int damage_;
};

void TestBuilder() {
  SoldierBuilder builder;
  auto soldier = builder.SetName("Sniper").SetDamage(50).SetHealth(80).Build();

  assert(soldier->GetTotalPower() == 50);
  assert(soldier->GetStatus() == "Idle");
}

void TestTemplateMethod() {
  SoldierBuilder builder;
  auto soldier = builder.SetName("Grunt").Build();

  assert(soldier->GetStatus() == "Idle");

  soldier->PlayTurn();

  assert(soldier->GetStatus() == "Grunt reloading");
}

void TestComposite() {
  auto squad = std::make_shared<Squad>();
  SoldierBuilder builder;

  auto s1 = builder.SetName("Alpha").SetDamage(10).Build();
  auto s2 = builder.SetName("Beta").SetDamage(20).Build();

  squad->Add(s1);
  squad->Add(s2);

  assert(squad->GetTotalPower() == 30);

  squad->PlayTurn();

  assert(s1->GetStatus() == "Alpha reloading");
  assert(s2->GetStatus() == "Beta reloading");
  assert(squad->GetStatus() == "Squad regrouping");
}

int main() {
  TestBuilder();
  TestTemplateMethod();
  TestComposite();
  return 0;
}