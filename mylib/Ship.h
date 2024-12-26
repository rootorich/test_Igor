#ifndef LAB1_MYLIB_SHIP_H_
#define LAB1_MYLIB_SHIP_H_

#include <vector>
#include "HealthManager.h"


enum class ShipOrientation {
  kHorizontal = 0,
  kVertical = 1,
};

enum class ShipSize {
  kTiny = 1,
  kSmall = 2,
  kMedium = 3,
  kHuge = 4,
};

class Ship {
 public:
  Ship(ShipSize size = ShipSize::kTiny, ShipOrientation orientation = ShipOrientation::kHorizontal);

  ShipSize get_segments_();
  ShipOrientation get_orientation_();
  std::vector<HealthManager>& get_segments_health_();


 private:

  ShipSize segments_;
  ShipOrientation orientation_;
  std::vector<HealthManager> segments_health_;

  std::array<ShipSize, 4> kSizeOrder = {ShipSize::kTiny, ShipSize::kSmall, ShipSize::kMedium, ShipSize::kHuge};

};

#endif
