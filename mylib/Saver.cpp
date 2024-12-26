#include "Saver.h"
#include <stdexcept>

Saver::Saver(const std::string& filename)
        : filename(filename) {
    std::ofstream file(filename, std::ios::app);
    if (!file.is_open()) {
        throw std::ios_base::failure("Failed to create or open file: " + filename);
    }
}

Saver::~Saver() {
}

