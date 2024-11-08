#include "ship.h"
#include "exception.h"


Ship::Ship(int length, bool isVertical) : length(length), vertical(vertical) {
    if (length < 1 || length > 4) {
        throw InvalidShipLengthException("Ship length must be between 1 and 4.");
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
        throw InvalidSegmentIndexException("Segment index out of range.");
    }

    return segments[index];
}


void Ship::attackSegment(int index) {
    if (index < 0 || index >= length) {
        throw InvalidSegmentIndexException("Segment index out of range.");
    }

    if (segments[index] == INTACT) {
        segments[index] = DAMAGED;

    }
    else if (segments[index] == DAMAGED) {
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

