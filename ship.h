#ifndef SHIP_H
#define SHIP_H

#include <iostream>
#include <vector>
#include <memory>


class Ship {
private:
enum segment {
        INTACT,
        DAMAGED,
        DESTROYED,
    };
    
    int length;
    bool vertical;
    int x, y;

public:
    std::vector<segment> segments;
    Ship(int length, bool vertical);

    int getLength() const;
    bool isVertical() const;
    void setVertical(bool trigger);

    int getSegmentState(int index) const;
    void setSegmentState(int index, int value);
    void attackSegment(int index);
    bool isDestroyed();
     
    int get_x() const;
    void set_x(int new_x);
    int get_y() const;
    void set_y(int new_y);
};

#endif