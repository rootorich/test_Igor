#ifndef LAB1_SCANNER_H
#define LAB1_SCANNER_H

#include "Ability.h"

#include <iostream>

class Scanner : public Ability {
 public:
  Scanner();

  bool Apply(Field& field, std::pair<size_t, size_t> coor) override;

  bool Scan(Field& field, std::pair<size_t, size_t> coor);

  std::string MyName() override;

};


#endif
