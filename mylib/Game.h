#ifndef LAB1_MYLIB_GAME_H_
#define LAB1_MYLIB_GAME_H_

#include "Player.h"
#include "IOManager.h"
#include "Field.h"
#include "ShipManager.h"
#include "Saver.h"

#include <vector>

struct SavedCellProperties {
    int ship_number;
    size_t segment_num;
    CellStatus status;
    bool vision;
};

class Game {
public:
  Game();

  void Process();
  void MainMenu();
  void ExitGame();

  bool BotMove();

  void Save();
  void Load();

  void CreatePlayer();


  void CreateShips(ShipManager& ship_manager);
  void CreateBot(Field field, ShipManager ship_manager);
  void NewGame();

  void PrepareGame();


  void ChangeTurn();


 private:
  std::vector<Player> players_;

  IOManager io_manager_;

  bool game_is_start_;

  size_t stage_;

    void SaveField(Saver &saver, Field &field);

    void SaveShip(Saver &saver, Ship ship);

    Ship *LoadShip(Saver &saver);

    void SaveCellProperties(Saver &saver, SavedCellProperties savedCellProperties);

    Field *LoadField(Saver &saver);

    SavedCellProperties LoadCellProperties(Saver &saver);
};

#endif
