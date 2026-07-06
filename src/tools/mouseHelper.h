//
// Created by Pd on 7/6/26.
//

#include "raylib.h"

#ifndef RAYLIB_GAME_TEMPLATE_MOUSEHELPER_H
#define RAYLIB_GAME_TEMPLATE_MOUSEHELPER_H


class MouseHelper {
    bool wasButtonDown[3] = {};
    bool buttonClicked[3] = {};

public:
    void update() {
        for (int i = 0; i < 3; i++) {
            if (IsMouseButtonDown(i)) {
                wasButtonDown[i] = true;
            } else {
                buttonClicked[i] = wasButtonDown[i];
                wasButtonDown[i] = false;
            }
        }
    }

    bool isButtonClicked(int button) {
        return buttonClicked[button];
    }
};

#endif //RAYLIB_GAME_TEMPLATE_MOUSEHELPER_H
