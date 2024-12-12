#include "ship.h"


Ship::Ship(int length, bool vertical) : length(length), vertical(vertical) {
    if (length < 1 || length > 4) {
        throw std::out_of_range("Ship length must be between 1 and 4.");
    }
    
    segments.resize(length, INTACT);
}

int Ship::getLength() const{
     return length; 
}


bool Ship::isVertical() const {
    return vertical;
}


void Ship::setVertical(bool trigger) {
    vertical = trigger;
}

int Ship::getSegmentState(int index) const {
    if (index < 0 || index >= length) {
        throw std::out_of_range("Segment index out of range.");
    }

    return segments[index];
}

void Ship::setSegmentState(int index, int value) {
    if (value == 0)
        segments[index] = INTACT;
    if (value == 1)
        segments[index] = DAMAGED;
    if (value == 2)
        segments[index] = DESTROYED;
}


void Ship::attackSegment(int index) {
    if (index < 0 || index >= length) {
        throw std::out_of_range("Segment index out of range.");
    }
    
    if (segments[index] == INTACT) {
        segments[index] = DAMAGED;
    
    } else if (segments[index] == DAMAGED) {
        segments[index] = DESTROYED;
    }
}

bool Ship::isDestroyed() {
    int destroy_segments = 0;
    for (int i = 0; i < length; i++) {
        int state = getSegmentState(i);
        if (state == DESTROYED) {
            destroy_segments++;
        }
    }
    
    if (destroy_segments == length) {
        return true;
    } 
    
    return false;
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