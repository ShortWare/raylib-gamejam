//
// Created by Pd on 7/6/26.
//
#pragma once
#include "raylib.h"
#include "../enums.h"

class Book {


public:
    void render(RenderTexture2D target, int frameCounter, float screenWidth, float screenHeight, GameScreen* gameScreen, bool clickedLeft) {
        BeginTextureMode(target);
        ClearBackground(RAYWHITE);

        DrawText("Book", 160, 90, 120, MAROON);

        EndTextureMode();


        BeginDrawing();
        ClearBackground(RAYWHITE);


        DrawTexturePro(target.texture, (Rectangle){ 0, 0, (float)target.texture.width, -(float)target.texture.height },
            (Rectangle){ 0, 0, (float)target.texture.width, (float)target.texture.height }, (Vector2){ 0, 0 }, 0.0f, WHITE);

        EndDrawing();

        if (clickedLeft) {
            *gameScreen = GameScreen::SCREEN_SHOP;
        }
    }
};