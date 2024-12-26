#include <iostream>

#include "mylib/IOManager.h"
#include "mylib/ShipManager.h"

int main() {

  bool has_field = false;
  size_t user_command = 0;

  std::cout << "Start program!\n";

  ShipManager ship_manager = ShipManager();
  Field field;
  IOManager io_manager = IOManager();
  AbilityManager ability_manager = AbilityManager();




  while (true) {
    std::cout << "\nAvailable options:\n";
    std::cout << "1) Create Ship\n";
    std::cout << "2) Remove Ship\n";
    std::cout << "3) Change Ship\n";
    std::cout << "4) Get info Ships\n";
    if (has_field) {
      std::cout << "5) Place Ship\n";
      std::cout << "6) Show Field\n";
      std::cout << "7) Hide Field\n";
      std::cout << "8) Open Field\n";
      std::cout << "9) Hit Cell\n";
      std::cout << "10) Heal Cell\n";
    } else {
      std::cout << "5) Create Field\n";
    }

    std::cout << "21) Quick Start (Ships)\n";
    std::cout << "22) Quick Start (Field)\n";
    std::cout << "23) Quick Start (Place Ships)\n";
    std::cout << "24) Quick Start (All)\n";

    std::cout << "30) Ability List\n";
    std::cout << "31) Use Ability\n";

    std::cout << "0) Exit\n";

    std::cout << "Enter num of command:";

    std::cin >> user_command;

    switch (user_command) {
      case 1:
        io_manager.AddShip(ship_manager);
        break;

      case 2:
        io_manager.RemoveShip(ship_manager);
        break;

      case 3:
        io_manager.ChangeShip(ship_manager);
        break;

      case 4:
        io_manager.GetInfoShips(ship_manager);
        break;

      case 5:
        if (has_field) {
          io_manager.PlaceShip(field, ship_manager);
        } else {
          field = io_manager.CreateField();
          has_field = true;
        }
        break;

      case 6:
        if (has_field) {
          io_manager.ShowField(field);
        } else {
          std::cout << "uncorrected input\n";
        }
        break;

      case 7:
        if (has_field) {
          io_manager.HideField(field);
        } else {
          std::cout << "uncorrected input\n";
        }
        break;


      case 8:
        if (has_field) {
          io_manager.OpenField(field);
        } else {
          std::cout << "uncorrected input\n";
        }
        break;

      case 9:
        if (has_field) {
          io_manager.HitCell(field);
        } else {
          std::cout << "uncorrected input\n";
        }
        break;

      case 10:
        if (has_field) {
          io_manager.HealCell(field);
        } else {
          std::cout << "uncorrected input\n";
        }
        break;

      case 21:
        io_manager.QuickStartShip(field, ship_manager);
        break;

      case 22:
        io_manager.QuickStartField(field, ship_manager);
        has_field = true;
        break;

      case 23:
        io_manager.QuickStartPlace(field, ship_manager);
        break;

      case 24:
        io_manager.QuickStart(field, ship_manager);
        has_field = true;
        break;

      case 30:
        io_manager.GetAbilityList(ability_manager);
        break;

      case 31:
        io_manager.UseAbility(field, ability_manager);
        break;

      case 32:
        io_manager.ShotAbility(field, ability_manager);
        break;

      case 0:
        std::cout << "End program\n";
        return 0;

      default:
        std::cout << "uncorrected input\n";
        break;
    }
  }





  return 0;
}
