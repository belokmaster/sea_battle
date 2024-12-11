#include "ship.h"


Ship::Ship(int length, bool is_vertical) : length(length), is_vertical(is_vertical) {
    if (length < 1 || length > 4) {
        throw std::out_of_range("Ship length must be between 1 and 4.");
    }
    
    segments.resize(length, intact);
}

int Ship::get_length() const{
     return length; 
}

bool Ship::is_orientation_vertical() const {
    return is_vertical; 
}

void Ship::set_orientation(bool trigger) {
    is_vertical = trigger;
}

int Ship::get_x() const {
    return x;
}

void Ship::set_x(int new_x) {
    x = new_x;
}

int Ship::get_y() const {
    return y;
}

void Ship::set_y(int new_y) {
    y = new_y;
}

void Ship::damage_segment(int index) {
    if (index < 0 || index >= length) {
        throw std::out_of_range("Segment index out of range.");
    }
    
    if (segments[index] == intact) {
        segments[index] = damaged;
    
    } else if (segments[index] == damaged) {
        segments[index] = destroyed;
    }
}

int Ship::get_segment_state(int index) const {
    if (index < 0 || index >= length) {
        throw std::out_of_range("Segment index out of range.");
    }
    
    return segments[index];
}

void Ship::set_segment_state(int index, int value) {
    if(value == 0)
        segments[index] = intact;
    if(value == 1)
        segments[index] = damaged;
    if(value == 2)
        segments[index] = destroyed;
}

bool Ship::is_destroy() {
    int destroy_segments = 0;
    for(int i = 0; i < length; i++) {
        int state = get_segment_state(i);
        if(state == destroyed) {
            destroy_segments += 1;
        }
    }
    
    if(destroy_segments == length) {
        return true;
    
    } else {
        return false;
    }
}
