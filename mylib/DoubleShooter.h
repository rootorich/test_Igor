#ifndef LAB1_DOUBLESHOOTER_H
#define LAB1_DOUBLESHOOTER_H

#include "Shooter.h"


class DoubleShooter : public Shooter {
 public:
  DoubleShooter();

  bool Apply(Field& field, std::pair<size_t, size_t> coor) override;

  bool DoubleShot(Field& field, std::pair<size_t, size_t> coor);

  std::string MyName() override;

};

#endif

