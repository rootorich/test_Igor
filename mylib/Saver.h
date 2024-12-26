#ifndef LAB1_MYLIB_SAVEFILE_H_
#define LAB1_MYLIB_SAVEFILE_H_

#include <fstream>
#include <string>

class Saver {
public:
    explicit Saver(const std::string& filename);

    ~Saver();

    template <typename T>
    void saveData(const T& data);

    template <typename T>
    T loadData();

private:
    std::string filename;
};


template <typename T>
void Saver::saveData(const T& data) {
    std::ofstream outFile(filename, std::ios::app);
    if (!outFile.is_open()) {
        throw std::ios_base::failure("Failed to open file for writing: " + filename);
    }
    outFile << data << "\n";
}

template <typename T>
T Saver::loadData() {
    T data;
    std::ifstream inFile(filename, std::ios::in);
    if (!inFile.is_open()) {
        throw std::ios_base::failure("Failed to open file for reading: " + filename);
    }
    inFile >> data;
    return data;
}

#endif // LAB1_MYLIB_SAVEFILE_H_
