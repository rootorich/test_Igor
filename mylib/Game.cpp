#include "Game.h"

Game::Game() {
  io_manager_ = IOManager();

  game_is_start_ = false;
  stage_ = 1;

  std::cout << "Start Game!\n";

  MainMenu();

}

void Game::Process() {

  size_t user_command = 0;

  while (true) {
    std::cout << "\nYour field:\n\n";
    io_manager_.ShowField(players_[0].get_field_());

    std::cout << "\nEnemy field:\n\n";
    io_manager_.ShowField(players_[1].get_field_());

    std::cout << "\nAvailable options:\n\n";

    std::cout << "1) Shot\n";
    std::cout << "2) Use Ability\n";
    std::cout << "3) Ability List\n";
    std::cout << "4) Open Field\n";

    std::cout << "9) Save\n";
    std::cout << "0) Exit\n";


    std::cout << "Enter num of command:";
    std::cin >> user_command;

    switch (user_command) {
      case 1:
        io_manager_.ShotAbility(players_[1].get_field_(), players_[0].get_ability_manager_());
        ChangeTurn();
        break;

      case 2:
        io_manager_.UseAbility(players_[1].get_field_(), players_[0].get_ability_manager_());
        ChangeTurn();
        break;

      case 3:
        io_manager_.GetAbilityList(players_[0].get_ability_manager_());
        break;

      case 4:
        io_manager_.OpenField(players_[1].get_field_());
        break;

      case 9:
        Save();
        break;

      case 0:
        ExitGame();
        break;

      default:
        break;
    }

    if (is_dead(players_[1])) {
      Win();
      continue;
    }

    if (players_[1].get_player_turn_()) {
      BotMove();
      ChangeTurn();
    }

    if (is_dead(players_[0])) {
      Lose();
      break;
    }

  }
}

void Game::MainMenu() {
  size_t user_command = 0;

  while (true) {
    std::cout << "\nAvailable options:\n\n";

    std::cout << "1. New Game\n";
    std::cout << "2. Load Game\n";
    std::cout << "Any other. Exit Game\n";

    std::cout << "Enter num of command:";
    std::cin >> user_command;

    switch (user_command) {
      case 1:
        NewGame();
        break;
      case 2:
        Load();
        break;

      default:
        ExitGame();
        break;
    }
  }
}

void Game::ExitGame() {
  if (game_is_start_) {
    size_t user_command = 0;

    std::cout << "Save Game?\n";
    std::cout << "1. Yes\n";
    std::cout << "Any other. No\n";

    std::cout << "Enter num of command:";
    std::cin >> user_command;

    if (user_command == 1) {
      Save();
    }
  }

  std::cout << "\nGoodbye\n";
  exit(1);
}

void Game::Save() {
    Saver saver("file.txt");

    saver.saveData(stage_);

    SavePlayer(saver,players_[0]);
    SavePlayer(saver,players_[1]);
}

void Game::Load() {
    Saver saver("file.txt");

    stage_ = saver.loadData<int>();

    Player player0 = LoadPlayer(saver, stage_);
    Player player1 = LoadPlayer(saver, stage_);

    players_.emplace_back(player0);
    players_.emplace_back(player1);


    game_is_start_ = true;
    Process();
}


void Game::SaveField(Saver& saver, Player& player){
  std::vector<std::vector<CellProperties>> cells = player.get_field_().get_cells_();

  saver.saveData(cells.size());
  saver.saveData(cells[0].size());

  for (int y = 0; y < cells.size(); ++y){
    for (int x = 0; x < cells[0].size(); ++x){
      saver.saveData(cells[y][x].vision);
    }
  }

  saver.saveData(player.get_ship_manager().get_ships_().size());

  for (int y = 0; y < cells.size(); ++y) {
    for (int x = 0; x < cells[0].size(); ++x) {
      if (cells[y][x].segment_num == 0 && cells[y][x].ship_p != nullptr) {
        Ship* ship = cells[y][x].ship_p;

        saver.saveData(y);
        saver.saveData(x);
        saver.saveData((int)(*ship).get_segments_());
        saver.saveData((int)(*ship).get_orientation_());

        for (int i = 0; i < (int)(*ship).get_segments_(); ++i) {
          saver.saveData((int)(*ship).get_segments_health_()[i].get_health_());
        }
      }
    }
  }
}

void Game::CreatePlayer() {
    players_.emplace_back();
}

void Game::LoadField(Saver& saver, Player& player) {
  int height = saver.loadData<int>();
  int width = saver.loadData<int>();

  Field field = Field(width, height);

  std::vector<std::vector<bool>> cells_vision;

  for (int y = 0; y < height; ++y) {
    cells_vision.emplace_back();
    for (int x = 0; x < width; ++x) {
      cells_vision[y].emplace_back(saver.loadData<bool>());
    }
  }


  int ships_count = saver.loadData<int>();

  ShipManager ship_manager = ShipManager();

  for (int i = 0; i < ships_count; ++i){
    int y = saver.loadData<int>();
    int x = saver.loadData<int>();
    auto ship_size = (ShipSize)saver.loadData<int>();
    auto ship_orientation = (ShipOrientation)saver.loadData<int>();

    ship_manager.AddShip(ship_size, ship_orientation);

    for (int j = 0; j < (int)ship_size; ++j) {
      ship_manager.get_ships_()[i].get_segments_health_()[j].ValueToHealth(saver.loadData<int>());
    }

    field.PlaceShipToField(ship_manager.get_ships_()[i], x, y);
  }

  for (int y = 0; y < height; ++y) {
    for (int x = 0; x < width; ++x) {
      field.SetVision(x, y, cells_vision[y][x]);

      if (field.get_cells_()[y][x].ship_p) {
        SegmentHealth segment_health = field.get_cells_()[y][x].ship_p->get_segments_health_()[field.get_cells_()[y][x].segment_num].get_health_();
        field.ChangeHealthCell(x, y, (int)segment_health);

      }
    }
  }

  player.set_field_(field);
  player.set_ship_manager(ship_manager);
}

void Game::SavePlayer(Saver& saver, Player& player){
  bool is_it_bot = player.is_it_bot_();
  bool turn = player.get_player_turn_();

  saver.saveData(is_it_bot);
  saver.saveData(turn);

  std::queue<AbilityNames> unique_abilities = player.get_ability_manager_().get_queue_ability();
  SavePlayerAbilities(saver,unique_abilities);

  SaveField(saver, player);
}

Player Game::LoadPlayer(Saver& saver, int stage){
  bool is_it_bot = saver.loadData<bool>();
  bool turn = saver.loadData<bool>();


  AbilityManager abilityManager = LoadPlayerAbilities(saver);

  Player player = Player(is_it_bot, stage);

  LoadField(saver, player);

  player.set_turn_(turn);
  player.set_ability_manager_(abilityManager);

  return player;

}

void Game::SavePlayerAbilities(Saver& saver,std::queue<AbilityNames>abilities){

  saver.saveData(abilities.size());

  while(!abilities.empty()){
    AbilityNames ability = abilities.front();
    saver.saveData((int)ability);
    abilities.pop();
  }
}

AbilityManager Game::LoadPlayerAbilities(Saver& saver){
  int size = saver.loadData<int>();

  std::queue<AbilityNames> abilities;

  for (int i = 0; i < size; ++i){
    auto ability = (AbilityNames)saver.loadData<int>();
    abilities.push(ability);
  }

  AbilityManager abilityManager(abilities);

  return abilityManager;
}

/*
void Game::SaveShip(Saver& saver, Ship ship) {

    ShipSize ship_size = ship.get_segments_();
    ShipOrientation ship_orientation = ship.get_orientation_();

    saver.saveData((int)ship_size);
    saver.saveData((int)ship_orientation);
}
*/
/*
void Game::SaveShips(Saver& saver, Field field) {

  std::vector<std::vector<CellProperties>> cells = field.get_cells_();

  for (int y = 0; y < cells.size(); ++y) {
    for (int x = 0; x < cells.size(); ++x) {
      if (cells[y][x].segment_num == 0) {
        Ship* ship = cells[y][x].ship_p;


        saver.saveData(y);
        saver.saveData(x);
        saver.saveData((int)(*ship).get_segments_());
        saver.saveData((int)(*ship).get_orientation_());
        for (int i = 0; i < (int)(*ship).get_segments_(); ++i) {
          saver.saveData((int)(*ship).get_segments_health_()[i].get_health_());
        }
      }
    }
  }

}

Ship* Game::LoadShip(Saver& saver) {
    auto ship_size = (ShipSize)saver.loadData<int>();
    auto ship_orientation = (ShipOrientation)saver.loadData<int>();

    Ship* ship = new Ship(ship_size, ship_orientation);

    return ship;
}

Ship* LoadShips(Saver &saver) {

}
*/

/*
void Game::SaveCellProperties(Saver& saver, SavedCellProperties savedCellProperties) {
    saver.saveData((int)savedCellProperties.ship_number);
    saver.saveData(savedCellProperties.segment_num);
    saver.saveData((int)savedCellProperties.status);
    saver.saveData(savedCellProperties.vision);
}

SavedCellProperties Game::LoadCellProperties(Saver& saver) {
    SavedCellProperties savedCellProperties{};
    savedCellProperties.ship_number = saver.loadData<int>();
    savedCellProperties.segment_num = saver.loadData<int>();
    savedCellProperties.status = (CellStatus)saver.loadData<int>();
    savedCellProperties.vision = saver.loadData<bool>();

    return savedCellProperties;
}
*/

void Game::CreateShips(Player& player) {
  bool is_exit = false;
  size_t user_command = 0;

  while (true) {
    std::cout << "Create Ship:\n\n";


    std::cout << "1. Create Ship\n";
    std::cout << "2. Remove Ship\n";
    std::cout << "3. Place Ship\n";

    std::cout << "0. Finish Creation\n";


    std::cout << "Enter num of command:";
    std::cin >> user_command;

    switch (user_command) {
      case 1:
        io_manager_.AddShip(player.get_ship_manager());
        break;
      case 2:
        io_manager_.RemoveShip(player.get_ship_manager());
        break;
      case 3:
        io_manager_.PlaceShip(player.get_field_(), player.get_ship_manager());
        break;
      case 0:
        is_exit = true;
        break;

      default:
        std::cout << "unknown command\n";
        break;
    }

    if (is_exit) {
      break;
    } else {
      io_manager_.GetInfoShips(player.get_ship_manager());
    }
  }
}

void Game::CreateBot(Field field, ShipManager ship_manager){
  players_.emplace_back(true, stage_);

  size_t width = field.get_cells_().size();
  size_t height = field.get_cells_()[0].size();

  players_[1].set_field_(Field(width, height));
  players_[1].set_ship_manager(ship_manager);

  for (int i = 0; i < ship_manager.get_ships_().size(); ++i) {
    for (int j = 0; j < 30; ++j) {
      int y = std::rand() % field.get_cells_().size();
      int x = std::rand() % field.get_cells_()[0].size();

      if (players_[1].get_field_().PlaceShipToField(players_[1].get_ship_manager().get_ships_()[i], x, y)) {
        break;
      }
    }
  }

}

void Game::NewGame() {
  CreatePlayer();

  Field field = io_manager_.CreateField();
  players_[0].set_field_(field);

  ShipManager ship_manager = ShipManager();
  players_[0].set_ship_manager(ship_manager);
  CreateShips(players_[0]);


  //io_manager_.ShotAbility(players_[0].get_field_(), players_[0].get_ability_manager_());

  CreateBot(players_[0].get_field_(), players_[0].get_ship_manager()); // check
  //io_manager_.ShotAbility(players_[1].get_field_(), players_[0].get_ability_manager_());

  players_[0].get_field_().OpenCells();

  Process();
}

void Game::ChangeTurn() {
  players_[0].ChangeTurn();
  players_[1].ChangeTurn();
}

void Game::BotMove() {
  //io_manager_.ShotAbility(players_[0].get_field_(), players_[1].get_ability_manager_());

  io_manager_.BotShotAbility(players_[1].get_field_(), players_[1].get_ability_manager_(), players_[1].get_bot_accuracy_());
  /*
  int rand_num = std::rand() % 100;

  std::cout << "rand_num = " << rand_num << "\n";

  if (rand_num < players_[1].get_bot_accuracy_()) {
    std::unique_ptr<Ability> ability = players_[1].get_ability_manager_().GetRandomShot();
    ability->Apply(players_[0].get_field_(), {0,0});

    return true;
  } else {
    return false;
  }
  */
}

void Game::Win() {
  std::cout << "\nYou Win!\n";
  std::cout << "\nStage " << stage_ << "is clear!\n\n";

  stage_++;

  players_.pop_back();

  ShipManager ship_manager = ShipManager(players_[0].get_ship_manager().get_ship_sizes_(),
                                         players_[0].get_ship_manager().get_ship_orientations_());

  CreateBot(players_[0].get_field_(), ship_manager);
}

void Game::Lose() {
  std::cout << "\nYou Lost!\n";

  std::cout << "\nOpen enemy field!\n";
  players_[1].get_field_().OpenCells();

  players_.clear();
}

bool Game::is_dead(Player& player) {
  if (player.get_field_().CountHittableCells() == 0) {
    return true;
  } else {
    return false;
  }
}


