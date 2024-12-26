#include "DoubleShooter.h"

DoubleShooter::DoubleShooter() {
  damage_ = -2;
  coor_need_ = true;
}

bool DoubleShooter::Apply(Field& field, std::pair<size_t, size_t> coor) {
  return DoubleShot(field, coor);
}

bool DoubleShooter::DoubleShot(Field& field, std::pair<size_t, size_t> coor) {
  return Shot(field, coor);
}
std::string DoubleShooter::MyName() {
  return "DoubleShooter";
}
