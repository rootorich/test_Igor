#include "HealthManager.h"

HealthManager::HealthManager() : health_{SegmentHealth::kUntouched} {}


void HealthManager::DecreaseHealth(int value) {
  auto it = std::find(kHealthOrder.begin(), kHealthOrder.end(), health_);

  for (size_t i = 0; i < value; ++i) {
    if (it != kHealthOrder.begin()) {
      --it;
      health_ = *it;
    }
  }
}

void HealthManager::IncreaseHealth(int value) {
  auto it = std::find(kHealthOrder.begin(), kHealthOrder.end(), health_);

  for (size_t i = 0; i < value; ++i) {
    if (it != kHealthOrder.end() - 1) {
        ++it;
        health_ = *it;
    }
  }
}

SegmentHealth& HealthManager::get_health_() {
  return health_;
}

void HealthManager::set_health_(int value) {
  (value > 0) ? IncreaseHealth(value) : DecreaseHealth(-value);
}


/*
SegmentHealth HealthManager::operator + (int value) {
  auto it = std::find(kHealthOrder.begin(), kHealthOrder.end(), health_);

  for (size_t i = 0; i < value; ++i) {
    if (it != kHealthOrder.end() - 1) {
        ++it;
        health_ = *it;
    }
  }

  return health_;
}

SegmentHealth HealthManager::operator - (int value) {
  auto it = std::find(kHealthOrder.begin(), kHealthOrder.end(), health_);

  for (size_t i = 0; i < value; ++i) {
    if (it != kHealthOrder.begin()) {
      --it;
      health_ = *it;
    }
  }
}
*/

