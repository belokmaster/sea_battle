#include "work_with_file.h"


WorkFile::WorkFile(string filename){
    this -> filename = filename;
}

ifstream& WorkFile::open_for_read() {
    try {
        input_file.open(filename);
    if (!input_file.is_open()) {
        throw WorkFileError("Невозможно открыть файл для чтения.\n");
    }
    } catch(WorkFileError& e){
        cout << e.what();
    }
    return input_file;
}

ofstream& WorkFile::open_for_write() {
    try {
        output_file.open(filename);
    if (!output_file.is_open()) {
        throw WorkFileError("Невозможно открыть файл для записи.\n");
    }
    } catch(WorkFileError& e){
        cout << e.what();
    }
    return output_file;
}

void WorkFile::close_read() {
    if (input_file.is_open()) {
        input_file.close();
    }
}

void WorkFile::close_write() {
    if (output_file.is_open()) {
        output_file.close();
    }
}

WorkFile::~WorkFile() {
    close_read();
    close_write();
}