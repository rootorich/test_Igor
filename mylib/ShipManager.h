#ifndef LAB1_MYLIB_SHIPMANAGER_H_
#define LAB1_MYLIB_SHIPMANAGER_H_

#include <vector>

#include "Ship.h"
#include "HealthManager.h"

class ShipManager {
 public:
  ShipManager();
  ShipManager(std::vector<ShipSize> sizes, std::vector<ShipOrientation> orientations);

  void AddShip(ShipSize size, ShipOrientation orientation);

  void RemoveShip(size_t ship_num);

  std::vector<Ship>& get_ships_();
  std::vector<ShipSize> get_ship_sizes_();
  std::vector<ShipOrientation> get_ship_orientations_();
  std::vector<bool>& get_is_used_();
  void set_is_used_(size_t ship_num);


 private:
  std::vector<Ship> ships_;

  std::vector<bool> is_used_;


};

#endif
