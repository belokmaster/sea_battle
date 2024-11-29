#ifndef EXCEPTION_H
#define EXCEPTION_H


#include <iostream>
using namespace std;



class Exception: public invalid_argument{
public:
    Exception(const char* msg): invalid_argument(msg) {}
};


class IncorrectCoordinatesException: public Exception {
public:
    explicit IncorrectCoordinatesException(const char* msg): Exception(msg){}
};


class PlaceShipException: public Exception {
private:
    int x_error;
    int y_error;
    
public:
    explicit PlaceShipException(const char* msg, int x, int y): Exception(msg), x_error(x), y_error(y) {}
    int getxerror(){
        return x_error;
    }
    int getyerror(){
        return y_error;
    }
};


class IncorrectFieldSize: public Exception {
public:
    explicit IncorrectFieldSize(const char* msg): Exception(msg){}
};


class IncorrectQuantity: public Exception {
public:
    explicit IncorrectQuantity(const char* msg): Exception(msg){}
};

class WorkFileError: public Exception {
public:
    explicit WorkFileError(const char* msg): Exception(msg){}
};

#endif