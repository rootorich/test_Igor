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
