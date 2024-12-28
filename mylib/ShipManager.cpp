#include "ShipManager.h"

ShipManager::ShipManager() {}

ShipManager::ShipManager(std::vector<ShipSize> sizes, std::vector<ShipOrientation> orientations) {
  for(auto size : sizes) {
    ships_.emplace_back(size);
    is_used_.emplace_back(false);
  }
}

void ShipManager::AddShip(ShipSize size, ShipOrientation orientation) {
  ships_.emplace_back(size, orientation);
  is_used_.emplace_back(false);
}

void ShipManager::RemoveShip(size_t ship_num) {
  ships_.erase(ships_.begin() - 1 + ship_num);
}

std::vector<Ship>& ShipManager::get_ships_() {
  return ships_;
}
std::vector<bool>& ShipManager::get_is_used_() {
  return is_used_;
}

void ShipManager::set_is_used_(size_t ship_num) {
  is_used_[ship_num] = true;
}
std::vector<ShipSize> ShipManager::get_ship_sizes_() {
  std::vector<ShipSize> ship_sizes;

  for (auto ship : ships_) {
    ship_sizes.emplace_back(ship.get_segments_());
  }

  return ship_sizes;
}
std::vector<ShipOrientation> ShipManager::get_ship_orientations_() {
  std::vector<ShipOrientation> ship_orientations;

  for (auto ship : ships_) {
    ship_orientations.emplace_back(ship.get_orientation_());
  }

  return ship_orientations;
}
