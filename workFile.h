#ifndef WORKFILE_H
#define WORKFILE_H

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <nlohmann/json.hpp>
#include "exception.h"

using namespace std;
using json = nlohmann::json;

class WorkFile {
private:
    string filename;
    ifstream input_file;
    ofstream output_file;

public:
    WorkFile(string filename);

    ifstream& open_for_read();
    ofstream& open_for_write();

    void close_read();
    void close_write();

    ~WorkFile();
};

#endif