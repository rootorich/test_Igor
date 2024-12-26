#ifndef LAB1_MYLIB_PLAYER_H_
#define LAB1_MYLIB_PLAYER_H_

#include "Field.h"
#include "IOManager.h"

class Player {
 public:
  Player();
  Player(bool is_bot, size_t stage);

  void set_field_(Field field);
  Field& get_field_();

  AbilityManager& get_ability_manager_();

  void ChangeTurn();
  bool get_player_turn_();
  size_t get_bot_accuracity_();

 private:
  bool is_bot_;
  int bot_accuracity_;

  bool player_turn_;

  AbilityManager ability_manager_;

  Field field_;


};

#endif
