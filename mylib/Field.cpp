#include "Field.h"

Field::Field(size_t width, size_t height) : width_{width}, height_{height} {
  cells_.resize(height, std::vector<CellProperties>(width, CellProperties{nullptr, 0, CellStatus::kEmpty, false}));
}


//Field::Field(const Field& other)
//        : width_(other.width_), height_(other.height_), cells_(other.cells_) {
//  for (size_t i = 0; i < height_; ++i) {
//    for (size_t j = 0; j < width_; ++j) {
//      if (cells_[i][j].ship_p) {
//        cells_[i][j].ship_p = new Ship(*(other.cells_[i][j].ship_p));
//      }
//    }
//  }
//}
//
//Field::Field(Field&& other) noexcept
//        : width_(other.width_), height_(other.height_), cells_(std::move(other.cells_)) {
//  other.width_ = 0;
//  other.height_ = 0;
//}
//
//Field& Field::operator=(const Field& other) {
//  if (this != &other) {
//    width_ = other.width_;
//    height_ = other.height_;
//    cells_ = other.cells_;
//
//    for (size_t i = 0; i < height_; ++i) {
//      for (size_t j = 0; j < width_; ++j) {
//        if (cells_[i][j].ship_p) {
//          cells_[i][j].ship_p = new Ship(*(other.cells_[i][j].ship_p));
//        }
//      }
//    }
//  }
//  return *this;
//}
//
//Field& Field::operator=(Field&& other) noexcept {
//  if (this != &other) {
//    width_ = other.width_;
//    height_ = other.height_;
//    cells_ = std::move(other.cells_);
//
//    other.width_ = 0;
//    other.height_ = 0;
//  }
//  return *this;
//}

bool Field::HasCollisionWithBorders(const ShipSize size, const ShipOrientation orientation, const size_t x, const size_t y) const {
  if (orientation == ShipOrientation::kHorizontal) {
    if (x + static_cast<int>(size) > width_ || y + 1 > height_) {
      return true;
    }
  } else {
    if (x + 1 > width_ || y + static_cast<int>(size) > height_) {
      return true;
    }
  }

  return false;
}

bool Field::HasCollisionWithShips(const ShipSize size, const ShipOrientation orientation, const size_t x, const size_t y) {
  std::pair <int, int> point_1 (x - 1, y - 1);
  std::pair <int, int> point_2;

  if (orientation == ShipOrientation::kHorizontal) {
    point_2 = std::make_pair(x + static_cast<int>(size), y + 1);
  } else {
    point_2 = std::make_pair(x + 1, y + static_cast<int>(size));
  }

  for (int i = 0; i < cells_.size(); ++i) {
    for (int j = 0; j < cells_[i].size(); ++j) {
      if (cells_[i][j].ship_p) {
        if (i >= point_1.second &&
            i <= point_2.second &&
            j >= point_1.first  &&
            j <= point_2.first) {
          return true;
        }
      }
    }
  }

  return false;
}

bool Field::PlaceShipToField(Ship& ship, size_t x, size_t y) {
  const ShipOrientation orientation = ship.get_orientation_();
  const ShipSize size = ship.get_segments_();

  if (HasCollisionWithBorders(size, orientation, x, y)) {
    return false;
  }

  if (HasCollisionWithShips(size, orientation, x, y)) {
    return false;
  }

  // FIX FIX FIX FIX FIX FIX FIX FIX FIX FIX FIX FIX FIX FIX FIX FIX FIX FIX FIX FIX
  // CellStatus::kShip to CellStatus::kUnknown

  if (orientation == ShipOrientation::kHorizontal) {
    for (size_t i = 0; i < static_cast<int>(size); ++i) {
      cells_[y][x + i] = CellProperties{&ship, i, CellStatus::kShip};
    }
  } else {
    for (size_t i = 0; i < static_cast<size_t>(size); ++i) {
      cells_[y + i][x] = CellProperties{&ship, i, CellStatus::kShip};
    }
  }
  // FIX FIX FIX FIX FIX FIX FIX FIX FIX FIX FIX FIX FIX FIX FIX FIX FIX FIX FIX FIX
  return true;
}

std::vector<std::vector<CellProperties>> Field::get_cells_() {
//  std::vector<std::vector<CellProperties>> cells_status;

//  for (size_t i = 0; i < cells_.size(); ++i) {
//    cells_status.emplace_back();
//    for (size_t j = 0; j < cells_[i].size(); ++j) {
//      cells_status[i].emplace_back(cells_[i][j]);
//    }
//  }

  return cells_;
}

CellProperties& Field::get_cell_(size_t x, size_t y) {
  return cells_[x][y];
}

void Field::HideCells() {
  for (auto& rows : cells_) {
    for (auto& cell : rows) {
      cell.vision = false;
    }
  }
}

void Field::OpenCells() {
  for (auto& rows : cells_) {
    for (auto& cell : rows) {
      if (cell.ship_p != nullptr) {
        cell.status = ConvertSegmentHealthToCellStatus(
                cell.ship_p->get_segments_health_()[cell.segment_num].get_health_());
      } else {
        cell.status = CellStatus::kEmpty;
      }
      cell.vision = true;
    }
  }
}

CellStatus Field::ConvertSegmentHealthToCellStatus(SegmentHealth health) {
  switch (health) {
    case SegmentHealth::kDestroyed:
      return CellStatus::kDestroyed;
    case SegmentHealth::kInjured:
      return CellStatus::kInjured;
    case SegmentHealth::kUntouched:
      return CellStatus::kShip;
    default:
      return CellStatus::kNull;
  }
}

void Field::ChangeHealthCell(size_t x, size_t y, int value) {
  if (cells_[x][y].ship_p) {
    cells_[x][y].ship_p->get_segments_health_()[cells_[x][y].segment_num].set_health_(value);
    cells_[x][y].status = ConvertSegmentHealthToCellStatus(
            cells_[x][y].ship_p->get_segments_health_()[cells_[x][y].segment_num].get_health_());
  } else {
    cells_[x][y].status = CellStatus::kEmpty;
  }
}

bool Field::is_live(size_t x, size_t y) {
  if (cells_[x][y].status != CellStatus::kEmpty && cells_[x][y].status != CellStatus::kNull) {
    for (auto segments : cells_[x][y].ship_p->get_segments_health_()) {
      if (segments.get_health_() != SegmentHealth::kDestroyed) {
        return true;
      }
    }
  }


  return false;
}
void Field::OpenCell(size_t x, size_t y) {
  cells_[x][y].vision = true;
}
void Field::ChangeCellStatus(size_t x, size_t y, CellStatus status) {
  cells_[x][y].status = status;
}
size_t Field::CountHittableCells() {
  size_t hittable_cells = 0;

  for (auto row : cells_) {
    for (auto cell : row) {
      if (cell.status == CellStatus::kShip ||
        cell.status == CellStatus::kInjured) {

        ++hittable_cells;
      }
    }
  };

  return hittable_cells;
}

void Field::SetCell(size_t x, size_t y, CellProperties cellProperties) {
    cells_[x][y] = cellProperties;
}




