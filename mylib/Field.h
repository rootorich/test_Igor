#ifndef LAB1_MYLIB_FIELD_H_
#define LAB1_MYLIB_FIELD_H_

#include <vector>

#include "Ship.h"
#include "HealthManager.h"

enum class CellStatus {
  kNull = 0,
  kEmpty = 1,
  kShip = 2,
  kInjured = 3,
  kDestroyed = 4,
};

struct CellProperties {
  Ship* ship_p;
  size_t segment_num;
  CellStatus status;
  bool vision;
};

class Field {
 public:
  Field(size_t width = 8, size_t height = 8);

  Field(const Field&) = default;
  Field(Field&&) = default;

  Field& operator = (const Field&) = default;
  Field& operator = (Field&& other) = default;

  ~Field() = default;

  bool PlaceShipToField(Ship& ship, size_t x, size_t y);

  std::vector<std::vector<CellProperties>> get_cells_();
  CellProperties& get_cell_(size_t x, size_t y);

  void HideCells();
  void OpenCells();

  CellStatus ConvertSegmentHealthToCellStatus(SegmentHealth health);
  void ChangeHealthCell(size_t x, size_t y, int value);

  bool is_live(size_t x, size_t y);

  void OpenCell(size_t x, size_t y);
  void ChangeCellStatus(size_t x, size_t y, CellStatus status);

  void SetCell(size_t x, size_t y, CellProperties cellProperties);

  void SetVision(size_t x, size_t y, bool vision);

  size_t CountHittableCells();

 private:
  bool HasCollisionWithBorders(ShipSize size, ShipOrientation orientation, size_t x, size_t y) const;
  bool HasCollisionWithShips(ShipSize size, ShipOrientation orientation, size_t x, size_t y);

  std::vector<std::vector<CellProperties>> cells_;


  size_t width_;
  size_t height_;

};

#endif
