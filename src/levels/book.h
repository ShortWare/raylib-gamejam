//
// Created by Pd on 7/6/26.
//
#pragma once
#include "raylib.h"
#include "../enums.h"
#include "../tools/mouseHelper.h"

class Book {


public:
    void render(RenderTexture2D target, int frameCounter, float screenWidth, float screenHeight, GameScreen* gameScreen, MouseHelper mouseHelper) {
        BeginTextureMode(target);
        ClearBackground(RAYWHITE);

        DrawText("Book", 160, 90, 120, MAROON);

        EndTextureMode();


        BeginDrawing();
        ClearBackground(RAYWHITE);


        DrawTexturePro(target.texture, (Rectangle){ 0, 0, (float)target.texture.width, -(float)target.texture.height },
            (Rectangle){ 0, 0, (float)target.texture.width, (float)target.texture.height }, (Vector2){ 0, 0 }, 0.0f, WHITE);

        EndDrawing();

        if (mouseHelper.isButtonClicked(0)) {
            *gameScreen = GameScreen::SCREEN_SHOP;
        }
    }
};