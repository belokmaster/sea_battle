#ifndef SHIP_H
#define SHIP_H

#include <iostream>
#include <vector>
#include <memory>


class Ship {
private:
enum segment {
    intact,
    damaged,
    destroyed
    };
    
    int length;
    bool is_vertical;
    int x, y;
public:
    std::vector<segment> segments;
    Ship(int length, bool is_vertical);

    void damage_segment(int index);
    int get_segment_state(int index) const;
    void set_segment_state(int index, int value);

    int get_length() const;
    bool is_orientation_vertical() const;
    void set_orientation(bool trigger);
    bool is_destroy();
     
    int get_x() const;
    void set_x(int new_x);
    int get_y() const;
    void set_y(int new_y);

};

#endif