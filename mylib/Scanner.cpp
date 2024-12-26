#include "Scanner.h"

Scanner::Scanner() {
  coor_need_ = true;
}

bool Scanner::Apply(Field& field, std::pair<size_t, size_t> coor) {
  return Scan(field, coor);
}

bool Scanner::Scan(Field& field, std::pair<size_t, size_t> coor) {
  for (size_t i = coor.first; i < coor.first + 1; ++i) {
    for (size_t j = coor.second; j < coor.second + 1; ++j) {
      std::cout << "Check i = " << i << " j = " << j << "\n";

      if (i <= field.get_cells_().size() &&
          j <= field.get_cells_()[i].size()) {

        if (field.get_cell_(i, j).ship_p != nullptr ||
            field.get_cell_(i, j).status != CellStatus::kDestroyed) {
          return true;
        }
      }
    }
  }

  return false;
}
std::string Scanner::MyName() {
  return "Scanner";
}
