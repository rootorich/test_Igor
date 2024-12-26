#include "Ship.h"

Ship::Ship(ShipSize size, ShipOrientation orientation) : segments_{size}, orientation_{orientation}
{
  auto it_size = std::find(kSizeOrder.begin(), kSizeOrder.end(), size);

  for (auto it = kSizeOrder.begin(); it != it_size + 1; ++it) {
    segments_health_.emplace_back();
  }
}

ShipSize Ship::get_segments_() {
  return segments_;
}

ShipOrientation Ship::get_orientation_() {
  return orientation_;
}

std::vector<HealthManager>& Ship::get_segments_health_() {
  return segments_health_;
}

