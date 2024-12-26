#include <stdexcept>
#include <algorithm>
#include <string>

class ShotOutOfBounds {
 public:
  ShotOutOfBounds(std::pair<size_t, size_t> coor)
    : x{coor.first}, y{coor.second} {}

  std::string what() const {
    std::string msg = "Cell with coor x = " +
                      std::to_string(x) + " and y = " +
                      std::to_string(y) + " does't exist\n";

    return msg;
  }

 private:
  size_t x;
  size_t y;
};

class AbilityQueueIsEmpty {
 public:
  AbilityQueueIsEmpty() = default;

  std::string what() const {
    std::string msg = "Ability queue is empty\n";

    return msg;
  }
};

class UnknownAbility {
 public:
  UnknownAbility() = default;

  std::string what() const {
    std::string msg = "Use unknown ability\n";

    return msg;
  }
};
