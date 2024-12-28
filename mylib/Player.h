#ifndef LAB1_MYLIB_PLAYER_H_
#define LAB1_MYLIB_PLAYER_H_

#include "Field.h"
#include "IOManager.h"

class Player {
 public:
  Player();
  Player(bool is_bot, size_t stage);

  void set_field_(Field field);
  void set_ability_manager_(AbilityManager& ability_manager);
  void set_ship_manager(ShipManager& ship_manager);

  Field& get_field_();
  AbilityManager& get_ability_manager_();
  ShipManager& get_ship_manager();

  void ChangeTurn();
  void set_turn_(bool turn);
  bool get_player_turn_();
  size_t get_bot_accuracy_();
  bool is_it_bot_();

private:
  bool is_bot_;
  int bot_accuracy_;

  bool player_turn_;

  AbilityManager ability_manager_;

  ShipManager ship_manager_;
  Field field_;
};

#endif
