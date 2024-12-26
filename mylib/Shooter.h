#ifndef LAB1_SHOOTER_H
#define LAB1_SHOOTER_H

#include "Ability.h"


class Shooter : public Ability {
 public:
  Shooter();

  bool Apply(Field& field, std::pair<size_t, size_t> coor) override;

  bool Shot(Field& field, std::pair<size_t, size_t> coor);

  std::string MyName() override;

 protected:
  int damage_;
};


#endif
