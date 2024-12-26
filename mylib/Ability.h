#ifndef LAB1_ABILITY_H
#define LAB1_ABILITY_H

#include "Field.h"

#include "../myexeption/Exceptions.cpp"

class Ability {
 public:

  virtual bool Apply(Field& field, std::pair<size_t, size_t> coor) = 0;

  virtual std::string MyName() = 0;

  bool get_coor_need_();

 protected:
  bool coor_need_ = false;

};


#endif
