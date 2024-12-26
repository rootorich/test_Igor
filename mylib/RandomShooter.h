#ifndef LAB1_RANDOMSHOOTER_H
#define LAB1_RANDOMSHOOTER_H

#include "Shooter.h"


class RandomShooter : public Shooter {
 public:
  RandomShooter();

  bool Apply(Field& field, std::pair<size_t, size_t> coor) override;

  bool RandomShot(Field& field);

  std::string MyName() override;

};

#endif
