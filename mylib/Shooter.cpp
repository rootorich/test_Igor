#include "Shooter.h"

Shooter::Shooter() : damage_{-1} {
  coor_need_ = true;
}

bool Shooter::Apply(Field& field, std::pair<size_t, size_t> coor) {
  return Shot(field, coor);
}

bool Shooter::Shot(Field& field, std::pair<size_t, size_t> coor) {
  auto [x, y] = coor;
  if (field.get_cells_().size()    <= x ||
      field.get_cells_()[0].size() <= y) {
//    throw std::runtime_error("Shot out of bounds");
      throw ShotOutOfBounds(coor);
  }

  CellProperties& cell = field.get_cell_(x, y);

  if (cell.status == CellStatus::kShip ||
      cell.status == CellStatus::kInjured) {
    Ship* ship = cell.ship_p;
    ship->get_segments_health_()[cell.segment_num].set_health_(damage_);

    SegmentHealth health = ship->get_segments_health_()[cell.segment_num].get_health_();
    CellStatus status = field.ConvertSegmentHealthToCellStatus(health);
    field.ChangeCellStatus(x, y, status);
    //field.get_cells_()[coor.first][coor.second].ship_p->get_segments_health_()[cell.segment_num].set_health_(damage_);
  } else {
    return false;
  }

  return true;
}
std::string Shooter::MyName() {
  return "StandartShooter";
}
