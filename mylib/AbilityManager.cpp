#include "AbilityManager.h"


AbilityManager::AbilityManager() {
  srand(time(nullptr));

  int size = (int) AbilityNames::Last;
  std::vector<AbilityNames> names;

  for (int i = 0; i < size; ++i) {
    names.emplace_back((static_cast<AbilityNames>(i)));
  }

  std::shuffle(names.begin(), names.end(), std::mt19937(std::random_device()()));

  for (int i = 0; i < size; ++i) {
    queue_ability.push(names[i]);
  }
}

AbilityManager::AbilityManager(std::queue<AbilityNames> &abilities) {
    queue_ability = abilities;
}

std::unique_ptr<Ability> AbilityManager::GetAbility() {
  if (queue_ability.empty()) {
    throw AbilityQueueIsEmpty();
    throw std::runtime_error("Ability queue is empty!");
  }

  AbilityNames abilityName = queue_ability.front();
  queue_ability.pop();

  switch (abilityName) {
    case AbilityNames::Scanner:
      return std::make_unique<Scanner>();

    case AbilityNames::RandomShooter:
      return std::make_unique<RandomShooter>();

    case AbilityNames::DoubleShooter:
      return std::make_unique<DoubleShooter>();

    default:
      throw UnknownAbility();
      throw std::runtime_error("Unknown ability!");
  }
}

void AbilityManager::SetRandomAbility() {
  int size = (int) AbilityNames::Last;
  int rand = std::rand() % size;

  queue_ability.push(static_cast<AbilityNames>(rand));
}
std::queue<AbilityNames> AbilityManager::get_queue_ability() {
  if (queue_ability.empty()) {
    throw AbilityQueueIsEmpty();
    throw std::runtime_error("Ability queue is empty!");
  }
  
  return queue_ability;
}
std::unique_ptr<Ability> AbilityManager::GetStandartShot() {
  return std::make_unique<Shooter>();
}

std::unique_ptr<Ability> AbilityManager::GetRandomShot() {
  return std::make_unique<RandomShooter>();
}



