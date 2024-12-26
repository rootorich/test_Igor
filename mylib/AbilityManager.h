#ifndef LAB1_ABILITYMANAGER_H
#define LAB1_ABILITYMANAGER_H

#include <queue>
#include <map>
#include <memory>
#include <ctime>
#include <cstdlib>
#include <algorithm>
#include <random>

#include "Scanner.h"
#include "RandomShooter.h"
#include "DoubleShooter.h"

enum class AbilityNames {
//  None = 0,
  Scanner = 0,
  RandomShooter = 1,
  DoubleShooter = 2,

  Last
};

class AbilityManager {
 public:
  AbilityManager();
  explicit AbilityManager(std::queue<AbilityNames>& abilities);

  std::unique_ptr<Ability> GetAbility();

  std::queue<AbilityNames> get_queue_ability();

  void SetRandomAbility();

  std::unique_ptr<Ability> GetStandartShot();
  std::unique_ptr<Ability> GetRandomShot();

 private:
  std::queue<AbilityNames> queue_ability;
};

#endif
