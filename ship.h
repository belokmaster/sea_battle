#ifndef SHIP_H
#define SHIP_H

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
    Ship(int length, bool is_vertical);

    int getLength() const;
    bool isVertical() const;
    void setVertical(bool trigger);

    int getSegmentState(int index) const;
    void attackSegment(int index);
    bool isDestroyed();
     
    int get_x() const;
    void set_x(int new_x);
    int get_y() const;
    void set_y(int new_y);

    std::vector<segment> segments;
};

#endif