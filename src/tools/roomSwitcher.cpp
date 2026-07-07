//
// Created by Pd on 7/7/26.
//

#include "roomSwitcher.h"

int RoomSwitcher::progress = 0;
bool RoomSwitcher::right = true;
bool RoomSwitcher::active = false;
bool RoomSwitcher::returning = false;
GameScreen RoomSwitcher::switchingTo = GameScreen::SCREEN_SHOP;