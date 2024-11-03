#include "ship.h"


Ship::Ship(int length, bool vertical) : length(length), vertical(vertical) {
    if (length < 1 || length > 4) {
        throw std::invalid_argument("Ship length must be between 1 and 4.");
    }

    segments.resize(length, INTACT);
}

int Ship::getLength() const{
     return length; 
}

bool Ship::isVertical() const {
    return vertical;
}

void Ship::setVertical(bool isVertical) {
    vertical = isVertical;
}

int Ship::getSegmentState(int index) const {
    if (index < 0 || index >= length) {
        throw std::out_of_range("Segment index out of range.");
    }

    return segments[index];
}

void Ship::attackSegment(int index) {
    if (index < 0 || index >= length) {
        throw std::out_of_range("Segment index out of range.");
    }

    int segmentState = getSegmentState(index);
    if (segmentState == INTACT) { 
        segments[index] = DAMAGED; 
    } 
    else if (segmentState == DAMAGED) { 
        segments[index] = DESTROYED; 
    }
}

bool Ship::isDestroyed() {
    int destroySegments = 0;

    for (int i = 0; i < length; i++) {
        int segmentState = getSegmentState(i);
        if (segmentState == DESTROYED) { 
            destroySegments++; 
        }
    }

    return destroySegments == length;
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