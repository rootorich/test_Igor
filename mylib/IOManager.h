#ifndef LAB1_IOMANAGER_H
#define LAB1_IOMANAGER_H

#include "ShipManager.h"
#include "Field.h"

#include "AbilityManager.h"

#include <iostream>


class IOManager {
 public:
  IOManager();


  static void GetInfoShip(Ship ship);

  void GetInfoShips(ShipManager& ship_manager);

  bool RemoveShip(ShipManager& ship_manager);
  void AddShip(ShipManager& ship_manager);
  void ChangeShip(ShipManager& ship_manager);

  Field CreateField();

  void PlaceShip(Field& field, ShipManager& ship_manager);
  void ShowField(Field& field);
  void HideField(Field& field);
  void OpenField(Field& field);

  void HitCell(Field& field);
  void HealCell(Field& field);
  void ChangeHealthCell(Field& field, int value);

  void GetAbilityList(AbilityManager& abilityManager);
  void UseAbility(Field& field, AbilityManager& abilityManager);
  void ShotAbility(Field& field, AbilityManager& ability_manager);

  void BotShotAbility(Field& field, AbilityManager& ability_manager, size_t accuracy);

  void QuickStartShip(Field& field, ShipManager& ship_manager);
  void QuickStartField(Field& field, ShipManager& ship_manager);
  void QuickStartPlace(Field& field, ShipManager& ship_manager);
  void QuickStart(Field& field, ShipManager& ship_manager);

  bool QueryPlayerInfo();

 private:
  size_t GetShip(ShipManager& ship_manager);

};


#endif //LAB1_IOMANAGER_H
