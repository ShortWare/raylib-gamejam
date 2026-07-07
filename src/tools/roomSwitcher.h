//
// Created by Pd on 7/7/26.
//

#ifndef RAYLIB_GAME_TEMPLATE_ROOMSWITCHER_H
#define RAYLIB_GAME_TEMPLATE_ROOMSWITCHER_H

#include "../tools/textureManager.h"
#include "../enums.h"


class RoomSwitcher {
    static int progress;
    static bool right;
    static bool active;
    static bool returning;
    static GameScreen switchingTo;

public:

    static bool isActive() { return active; }

    static void switchRoom(GameScreen screen, bool side) {
        switchingTo = screen;
        right = side;
        progress = 0;
        active = true;
        returning = false;
    }

    static void render(GameScreen* gameScreen) {
        if (!active) return;

        progress += 40;

        int pos = returning ? 0 : 720;
        if (!right) pos *= -1;
        pos += right ? -progress : progress;

        BeginDrawing();

        DrawTexture(TextureManager::GetTexture(TextureManager::WALL),pos,0,WHITE);

        EndDrawing();

        if (progress == 720) {
            if (*gameScreen == switchingTo) {
                active = false;
            } else {
                *gameScreen = switchingTo;
                returning = true;
                progress = 0;
            }
        }
    }
};


#endif //RAYLIB_GAME_TEMPLATE_ROOMSWITCHER_H
