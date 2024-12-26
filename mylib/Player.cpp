#include "Player.h"

#include <utility>

Player::Player() {
  is_bot_ = false;
  ability_manager_ = AbilityManager();
}

Player::Player(bool is_bot, size_t stage) {
  is_bot_ = is_bot;
  player_turn_ = !is_bot;
  bot_accuracity_ = 10 * stage;
}

void Player::set_field_(Field field) {
  field_ = std::move(field);
}

void Player::set_ability_manager_(AbilityManager& abilityManager){
    ability_manager_ = abilityManager;
}

Field& Player::get_field_() {
  return field_;
}

bool Player::is_it_bot_(){
    return is_bot_;
}


AbilityManager& Player::get_ability_manager_() {
  return ability_manager_;
}

void Player::ChangeTurn() {
  player_turn_ = !player_turn_;
}

bool Player::get_player_turn_() {
  return player_turn_;
}

size_t Player::get_bot_accuracity_() {
  return bot_accuracity_;
}
