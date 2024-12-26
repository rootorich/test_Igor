#ifndef LAB1_MYLIB_HEALTHMANAGER_H_
#define LAB1_MYLIB_HEALTHMANAGER_H_

#include <array>
#include <algorithm>

enum class SegmentHealth {
  kDestroyed = 0,
  kInjured = 1,
  kUntouched = 2,
};

class HealthManager {
 public:
  HealthManager();

  SegmentHealth& get_health_();
  void set_health_(int value);
/*
  SegmentHealth operator + (int value);
  SegmentHealth operator - (int value);
*/
 private:
  void DecreaseHealth(int value);
  void IncreaseHealth(int value);

  SegmentHealth health_;

  std::array<SegmentHealth, 3> kHealthOrder = {SegmentHealth::kDestroyed, SegmentHealth::kInjured, SegmentHealth::kUntouched};


};

#endif
