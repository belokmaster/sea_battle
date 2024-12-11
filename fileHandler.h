#ifndef FILE_HANDLER_H
#define FILE_HANDLER_H

#include <iostream>
#include <vector>
#include <stdexcept>
#include <iomanip>
#include <sstream>
#include <string>
#include <fstream>
#include "nlohmann/json.hpp"

using json = nlohmann::json;

class FileHandler {
private:
    std::string filename;
    std::ifstream infile;
    std::ofstream outfile;

public:
    FileHandler(const std::string& fname) : filename(fname) {}

    void open_for_read();

    void open_for_write();

    void write(const json& j);

    void read(json& j);

    void close_read();

    void close_write();

    ~FileHandler() {
        close_read();
        close_write();
    }
};

#endif