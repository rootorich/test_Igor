#include "IOManager.h"



IOManager::IOManager() {}

void IOManager::GetInfoShip(Ship shiper) {
  std::cout << "count segments = " << static_cast<int>(shiper.get_segments_())   << "\n";
}

void IOManager::GetInfoShips(ShipManager& ship_manager) {
  std::vector<Ship> ships = ship_manager.get_ships_();
  std::vector<bool> is_used = ship_manager.get_is_used_();


  if (ships.empty()) {
    std::cout << "I don't have ships\n";
  } else {
    for (size_t i = 0; i < ships.size(); ++i) {
      std::cout << i + 1 << ") ";

      std::cout << "size = ";

      switch (ships[i].get_segments_()) {
        case ShipSize::kTiny:
          std::cout << 1;
          break;

        case ShipSize::kSmall:
          std::cout << 2;
          break;

        case ShipSize::kMedium:
          std::cout << 3;
          break;

        case ShipSize::kHuge:
          std::cout << 4;
          break;

        default:
          std::cout << "unknown error";
      }

      std::cout << ", orientation = ";

      switch (ships[i].get_orientation_()) {
        case ShipOrientation::kHorizontal:
          std::cout << "horizontal";
          break;

        case ShipOrientation::kVertical:
          std::cout << "vertical";
          break;

        default:
          std::cout << "unknown error";
      }

      std::cout << ", is_used = ";
      std::cout << ((is_used[i]) ? "yes" : "no");

      std::cout << "\n";
    }
  }
  std::cout << "\n";
}
bool IOManager::RemoveShip(ShipManager& ship_manager) {
  size_t ship_num = IOManager::GetShip(ship_manager);

  if (ship_manager.get_ships_().empty()) {
    std::cout << "I don't have ships\n";
  } else if (ship_manager.get_is_used_()[ship_num]) {
    std::cout << "Ship is used\n";
  } else {
    ship_manager.RemoveShip(ship_num);
    return true;
  }

  return false;
}

void IOManager::AddShip(ShipManager& ship_manager) {
  size_t player_size;
  std::string player_orientation;
  ShipSize size;
  ShipOrientation orientation;

  while (true) {
    std::cout << "Enter size (from 1 to 4): ";
    std::cin >> player_size;
    if (player_size >= 1 && player_size <= 4) {
      size = ShipSize(player_size);
      break;
    } else {
      std::cout << "uncorrected size\n";
    }
  }

  while (true) {
    std::cout << "Enter orientation (horizontal (0) or vertical (1)): ";
    std::cin >> player_orientation;
    if (player_orientation == "horizontal" || player_orientation == "0") {
      orientation = ShipOrientation::kHorizontal;
      break;
    } else if (player_orientation == "vertical" || player_orientation == "1") {
      orientation = ShipOrientation::kVertical;
      break;
    } else {
      std::cout << "uncorrected orientation\n";
    }
  }

  std::cout << "\n";

  ship_manager.AddShip(size, orientation);
}

void IOManager::ChangeShip(ShipManager& ship_manager) {
  if (IOManager::RemoveShip(ship_manager)) {
    IOManager::AddShip(ship_manager);
  }
}

Field IOManager::CreateField() {
  int width;
  int height;

  while (true) {
    std::cout << "Enter width and height sizes field (less than 50x50): ";
    std::cin >> width >> height;

    if (width < 0 || height < 0) {
      std::cout << "width and height should be greater than 0\n";
    } else if (width > 50 || height > 50) {
      std::cout << "width and height should be not greater than 50\n";
    } else {
      std::cout << "Set width = " << width << " and height = " << height << "\n\n";
      break;
    }
  }

  return Field(width, height);
}

void IOManager::PlaceShip(Field& field, ShipManager& ship_manager) {
  size_t ship_num = IOManager::GetShip(ship_manager);

  if (ship_manager.get_is_used_()[ship_num]) {
    std::cout << "Ship is used\n";

  } else {
    int x;
    int y;
    Ship& ship = ship_manager.get_ships_()[ship_num];

    while (true) {
      std::cout << "Enter left-top position ship (coord x and y): ";
      std::cin >> x >> y;

      if (x < 1 || y < 1) {
        std::cout << "uncorrected position\n";
        std::cout << "inputs less 1\n";
      } else {
        if (field.PlaceShipToField(ship, x - 1, y - 1)) {
          ship_manager.set_is_used_(ship_num);
          std::cout << "Ship is placed\n\n";
          break;
        } else {
          std::cout << "uncorrected position\n";
        }
      }
    }
  }
}

size_t IOManager::GetShip(ShipManager& ship_manager) {
  size_t ship_num;

  while (true) {
    std::cout << "Enter num of ship: ";

    std::cin >> ship_num;

    if (ship_num > 0 && ship_num <= ship_manager.get_ships_().size()) {
      break;
    } else {
      std::cout << "uncorrected num of ship\n";
    }
  }

  return ship_num - 1;
}

void IOManager::ShowField(Field& field) {
  std::vector<std::vector<CellProperties>> cells_status = field.get_cells_();

  for (const auto& rows : cells_status) {
    std::cout << "    ";
    for (auto cell : rows) {
      std::cout << " ";

      if (!cell.vision) {
        std::cout << "?";
      } else {
        switch (cell.status) {
          case CellStatus::kEmpty:
            std::cout << "0";
            break;

          case CellStatus::kShip:
            std::cout << "#";
            break;

          case CellStatus::kInjured:
            std::cout << "*";
            break;

          case CellStatus::kDestroyed:
            std::cout << "X";
            break;

          default:
            std::cout << "W";
            break;

        }
      }

    }

    std::cout << "\n";
  }

  std::cout << "\n";
}

void IOManager::HideField(Field& field) {
  field.HideCells();

  std::cout << "Field is closed\n\n";
}

void IOManager::OpenField(Field& field) {
  field.OpenCells();

  std::cout << "Field is opened\n\n";
}

void IOManager::HitCell(Field& field) {
  int damage_value;

  while (true) {
    std::cout << "Enter damage value (>= 0): ";

    std::cin >> damage_value;

    if (damage_value >= 0) {
      break;
    } else {
      std::cout << "uncorrected value (less 0)\n";
    }
  }
  std::cout << "damage = " << damage_value << "\n";

  IOManager::ChangeHealthCell(field, -damage_value);
}

void IOManager::HealCell(Field& field) {
  int heal_value;

  while (true) {
    std::cout << "Enter heal value (>= 0): ";

    std::cin >> heal_value;

    if (heal_value >= 0) {
      break;
    } else {
      std::cout << "uncorrected value (less 0)\n";
    }
  }
  std::cout << "heal = " << heal_value << "\n";

  IOManager::ChangeHealthCell(field, heal_value);
}

void IOManager::ChangeHealthCell(Field& field, int value) {
  int x, y;
  size_t height = field.get_cells_().size();
  size_t width = field.get_cells_()[0].size();

  while (true) {
    std::cout << "Enter cell's coordinates (coord x and y): ";
    std::cin >> y >> x;

    if (x < 1 || y < 1 || x > width || y > height) {
      std::cout << "uncorrected position\n";
      std::cout << "inputs less 1 or greater " << width << " or " << height << "\n";
    } else {
      field.ChangeHealthCell(x - 1, y - 1, value);
      break;
    }
  }
}

void IOManager::GetAbilityList(AbilityManager& abilityManager) {
  std::queue<AbilityNames> abilityList;
  size_t count = 0;

  try {
    abilityList = abilityManager.get_queue_ability();;
  }
  catch (const AbilityQueueIsEmpty& error) {
    std::cout << error.what() << "\n";
  }

  std::cout << "Queue Ability\n";

  while (!abilityList.empty()) {
    AbilityNames abilityName = abilityList.front();
    abilityList.pop();

    count++;

    std::cout << "#";
    std::cout << count;

    switch (abilityName) {
      case AbilityNames::Scanner:
        std::cout << ": Scanner\n";
        break;

      case AbilityNames::RandomShooter:
        std::cout << ": RandomShooter\n";
        break;

      case AbilityNames::DoubleShooter:
        std::cout << ": DoubleShooter\n";
        break;

      default:
        std::cout << ": Unknowed ability\n";
    }
  }
}

void IOManager::UseAbility(Field& field, AbilityManager& abilityManager) {
  int x, y;
  std::unique_ptr<Ability> ability;

  size_t hittable_cells = field.CountHittableCells();

  bool is_success;

  try {
    ability = abilityManager.GetAbility();
  }
  catch (const AbilityQueueIsEmpty& error) {
    std::cout << error.what() << "\n";

    std::cout << "Use Standart Shot";

    ability = abilityManager.GetStandartShot();

  }
  catch (const UnknownAbility& error) {
    std::cout << error.what() << "\n";

    std::cout << "Use Standart Shot";

    ability = abilityManager.GetStandartShot();
  }

  while (true) {
    if (ability->get_coor_need_()) {
      std::cout << "Enter cell's coordinates (coord x and y): ";
      std::cin >> y >> x;

      y = y - 1;
      x = x - 1;

      try {
        is_success = ability->Apply(field, std::pair<int, int>(x, y));
      }
      catch (const ShotOutOfBounds& error) {
        std::cout << error.what();
        continue;
      }


      if (ability->MyName() == "Scanner") {
        if (is_success) {
          std::cout << "Has ";
        } else {
          std:: cout << "Hasn't ";
        }
        std::cout << "Ship here\n";
      } else if (ability->MyName() == "DoubleShooter") {
        if (is_success) {
          std::cout << "Hit";
          field.OpenCell(x, y);
        } else {
          std::cout << "Miss";
        }
        std::cout << "\n";
      }
    }

    break;
  }

  if (hittable_cells < field.CountHittableCells()) {
    abilityManager.SetRandomAbility();
  }
}

void IOManager::ShotAbility(Field& field, AbilityManager& abilityManager) {
  std::unique_ptr<Ability> ability = abilityManager.GetStandartShot();

  int x, y;
  bool is_success;

  size_t hittable_cells = field.CountHittableCells();

  while (true) {
    std::cout << "Enter cell's coordinates (coord x and y): ";
    std::cin >> y >> x;

    x--;
    y--;


    try {
      is_success = ability->Apply(field, std::pair<int, int>(x,y));
    }
    catch (const ShotOutOfBounds& error) {
      std::cout << error.what();
      continue;
    }

    if (is_success) {
      std::cout << "Hit";
    } else {
      std::cout << "Miss";
    }
    field.OpenCell(x, y);

    break;
  }

  if (hittable_cells < field.CountHittableCells()) {
    abilityManager.SetRandomAbility();
  }
}

void IOManager::QuickStartShip(Field& field, ShipManager& ship_manager) {
  ship_manager.AddShip(ShipSize::kHuge, ShipOrientation::kHorizontal);
  ship_manager.AddShip(ShipSize::kHuge, ShipOrientation::kVertical);
  ship_manager.AddShip(ShipSize::kMedium, ShipOrientation::kHorizontal);
  ship_manager.AddShip(ShipSize::kMedium, ShipOrientation::kVertical);
  ship_manager.AddShip(ShipSize::kSmall, ShipOrientation::kHorizontal);
  ship_manager.AddShip(ShipSize::kSmall, ShipOrientation::kVertical);
  ship_manager.AddShip(ShipSize::kTiny, ShipOrientation::kHorizontal);
  ship_manager.AddShip(ShipSize::kTiny, ShipOrientation::kVertical);
}

void IOManager::QuickStartField(Field& field, ShipManager& ship_manager) {
  field = Field(8, 8);
}

void IOManager::QuickStartPlace(Field& field, ShipManager& ship_manager) {
  field.PlaceShipToField(ship_manager.get_ships_()[0], 0, 0);
  field.PlaceShipToField(ship_manager.get_ships_()[1], 0, 2);
  field.PlaceShipToField(ship_manager.get_ships_()[2], 2, 2);
  field.PlaceShipToField(ship_manager.get_ships_()[3], 4, 4);
  field.PlaceShipToField(ship_manager.get_ships_()[6], 6, 6);
  field.PlaceShipToField(ship_manager.get_ships_()[7], 7, 0);
}

void IOManager::QuickStart(Field& field, ShipManager& ship_manager) {
  IOManager::QuickStartShip(field, ship_manager);
  IOManager::QuickStartField(field, ship_manager);
  IOManager::QuickStartPlace(field, ship_manager);
}
bool IOManager::QueryPlayerInfo() {
  int choose;

  while(true) {

    std::cout << "Who is player?\n";
    std::cout << "1. Human\n";
    std::cout << "2. Bot\n";

    std::cin >> choose;

    if (choose == 1 || choose == 2) {
      break;
    } else {
      std::cout << "Incorrect input\n\n";
    }
  }

  choose--;
  return choose;
}





