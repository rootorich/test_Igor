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
    std::cout << "\nAvailable options:\n\n";

    std::cout << "1) Shot\n";
    std::cout << "2) Use Ability\n";
    std::cout << "3) Ability List\n";

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

      case 9:
        Save();
        break;

      case 0:
        ExitGame();
        break;

      default:
        break;
    }

    if (players_[1].get_player_turn_()) {
      BotMove();
      ChangeTurn();
    }

    break;

  }
}

void Game::MainMenu() {
  size_t user_command = 0;

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

    int stage = players_[0].get_bot_accuracity_() / 10;
    saver.saveData(stage);

    SavePlayer(saver,players_[0]);
    SavePlayer(saver,players_[1]);
}

void Game::Load() {
    Saver saver("file.txt");

    int stage = saver.loadData<int>();

    Player player0 = LoadPlayer(saver, stage);
    Player player1 = LoadPlayer(saver, stage);

    players_[0] = player0;
    players_[1] = player1;


    game_is_start_ = true;
    Process();
}


void Game::SaveField(Saver& saver, Field& field){
    std::vector<std::vector<CellProperties>> cells = field.get_cells_();

    std::map<Ship*, size_t> map;
    std::vector<Ship*> ships;

    for (auto & cell : cells){
        for (auto & item : cell){
            if (item.segment_num == 0){
                map[item.ship_p] = ships.size();
                ships.push_back(item.ship_p);
            }
        }
    }

    saver.saveData(ships.size());

    for (auto & ship : ships){
        SaveShip(saver, *ship);
    }

    saver.saveData(cells.size());
    saver.saveData(cells[0].size());

    for (int i = 0; i < cells.size(); ++i){
        for (int j = 0; j < cells[i].size(); ++j){
            SavedCellProperties savedCellProperties{};
            savedCellProperties.ship_number = map[cells[i][j].ship_p];
            savedCellProperties.segment_num = cells[i][j].segment_num;
            savedCellProperties.status = cells[i][j].status;
            savedCellProperties.vision = cells[i][j].vision;

            SaveCellProperties(saver, savedCellProperties);
        }
    }
}

void Game::CreatePlayer() {
    players_.push_back(Player());
}

Field Game::LoadField(Saver& saver) {
    int ships_size = saver.loadData<int>();

    std::vector<Ship*> ships;

    for (int i = 0; i < ships_size; ++i){
        ships.push_back(LoadShip(saver));
    }

    int rows = saver.loadData<int>();
    int colls = saver.loadData<int>();

    Field field;

    for (int i = 0; i < rows; ++i){
        for (int j = 0; j < colls; ++j){
            SavedCellProperties savedCellProperties = LoadCellProperties(saver);

            CellProperties cellProperties = {};
            cellProperties.ship_p = ships[savedCellProperties.ship_number];
            cellProperties.segment_num = savedCellProperties.segment_num;
            cellProperties.vision = savedCellProperties.vision;
            cellProperties.status = savedCellProperties.status;

            field.SetCell(i, j, cellProperties);
        }
    }

    return field;
}

void Game::SavePlayer(Saver& saver, Player& player){
    bool is_it_bot = player.is_it_bot_();
    bool turn = player.get_player_turn_();

    saver.saveData(is_it_bot);
    saver.saveData(turn);

    std::queue<AbilityNames> unique_abilities = player.get_ability_manager_().get_queue_ability();
    SavePlayerAbilities(saver,unique_abilities);

    SaveField(saver, player.get_field_());
}

Player Game::LoadPlayer(Saver& saver, int stage){
    bool is_it_bot = saver.loadData<bool>();
    bool turn = saver.loadData<bool>();


    AbilityManager abilityManager = LoadPlayerAbilities(saver);
    Field field = LoadField(saver);

    Player player = Player(is_it_bot, stage);

    player.set_turn_(turn);
    player.set_ability_manager_(abilityManager);
    player.set_field_(field);

    return player;

}

void Game::SavePlayerAbilities(Saver& saver,std::queue<AbilityNames>&abilities){

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

void Game::SaveShip(Saver& saver, Ship ship) {

    ShipSize ship_size = ship.get_segments_();
    ShipOrientation ship_orientation = ship.get_orientation_();

    saver.saveData((int)ship_size);
    saver.saveData((int)ship_orientation);
}

Ship* Game::LoadShip(Saver& saver) {
    auto ship_size = (ShipSize)saver.loadData<int>();
    auto ship_orientation = (ShipOrientation)saver.loadData<int>();

    Ship* ship = new Ship(ship_size, ship_orientation);

    return ship;
}

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

void Game::CreateShips(ShipManager& ship_manager) {
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
        io_manager_.AddShip(ship_manager);
        break;
      case 2:
        io_manager_.RemoveShip(ship_manager);
        break;
      case 3:
        io_manager_.PlaceShip(players_[0].get_field_(), ship_manager);
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
      io_manager_.GetInfoShips(ship_manager);
    }
  }
}

void Game::CreateBot(Field field, ShipManager ship_manager){
  players_.emplace_back(true, stage_);

  size_t width = field.get_cells_().size();
  size_t height = field.get_cells_()[0].size();

  players_[1].set_field_(Field(width, height));

  //for (size_t i = ship_manager.get_ships_().size(); i >= 0; --i) {

  //}

  // Place Ships to Field;
}

void Game::NewGame() {
  CreatePlayer();

  Field field = io_manager_.CreateField();
  players_[0].set_field_(field);

  ShipManager ship_manager = ShipManager();
  CreateShips(ship_manager);

  ShipManager bot_ship_manager = ship_manager;

  io_manager_.ShotAbility(players_[0].get_field_(), players_[0].get_ability_manager_());

  CreateBot(field, bot_ship_manager); // check
  io_manager_.ShotAbility(players_[1].get_field_(), players_[0].get_ability_manager_());


  Process();
}

void Game::ChangeTurn() {
  players_[0].ChangeTurn();
  players_[1].ChangeTurn();
}

bool Game::BotMove() {
  io_manager_.ShotAbility(players_[0].get_field_(), players_[1].get_ability_manager_());

  if (std::rand() % 100 < players_[1].get_bot_accuracity_()) {
    players_[1].get_ability_manager_().GetRandomShot()->Apply(players_[0].get_field_(), {0,0});
    return true;
  } else {
    return false;
  }
}



