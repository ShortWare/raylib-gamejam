//
// Created by Pd on 7/9/26.
//


#include "scrollInventory.h"
#include "../levels/workshop.h"

void ScrollInventory::selectScroll(int id, float x1, float y1, float x2, float y2) {
    bool success = workshop->pickupScroll(scrolls[id]);
    if (success) {
        scrolls.erase(scrolls.begin() + id);
        updateScrolls(x1,y1,x2,y2);
    }
}


ScrollInventory::ScrollInventory(int _capacity, Workshop *_workshop) {
    capacity = _capacity;
    workshop = _workshop;
}