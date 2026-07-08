//
// Created by Pd on 7/6/26.
//
#pragma once
#include "raylib.h"
#include "../enums.h"
#include "../tools/inputHelper.h"
#include "../gameplay/castingGrid.h"
#include "../gameplay/spells.h"
#include "../tools/soundManager.h"
#include "../tools/roomSwitcher.h"
#include "../gameplay/scrollInventory.h"

class Workshop {
    std::shared_ptr<CastingGrid> castingGrid = nullptr;
    std::vector<std::shared_ptr<CastingGrid>> castSpells{};
    std::vector<std::vector<Vector2>> castSpellsPoints{};
    ScrollInventory scrollInventory{30};

public:
    void render(RenderTexture2D target, int frameCounter, float screenWidth, float screenHeight, GameScreen* gameScreen, InputHelper inputHelper) {
        BeginTextureMode(target);

        DrawTexture(TextureManager::GetTexture(TextureManager::WORKSHOP_BG),0,0,WHITE);

        DrawText("Workshop", 160, 30, 80, MAROON);

        Vector2 mousePos = GetMousePosition();

        EndTextureMode();


        BeginDrawing();


        DrawTexturePro(target.texture, (Rectangle){ 0, 0, (float)target.texture.width, -(float)target.texture.height },
            (Rectangle){ 0, 0, (float)target.texture.width, (float)target.texture.height }, (Vector2){ 0, 0 }, 0.0f, WHITE);

        DrawRectangle(570, 300, 20, 270, BLUE);

        EndDrawing();

        if (inputHelper.isKeyClicked(KEY_A) && !RoomSwitcher::isActive()) {
            RoomSwitcher::switchRoom(GameScreen::SCREEN_SHOP, false);
            SoundManager::Play(SoundManager::MOVE);
        } else if (inputHelper.isKeyClicked(KEY_D) && !RoomSwitcher::isActive()) {
            RoomSwitcher::switchRoom(GameScreen::SCREEN_BOOK, true);
            SoundManager::Play(SoundManager::MOVE);
        }

        if (RoomSwitcher::isActive()) {
            RoomSwitcher::render(gameScreen);
            return;
        }

        if (mousePos.x >= screenWidth - 20) {
            DrawRectangle(screenWidth - 20, 0, 20, screenHeight, SKYBLUE);

            if (inputHelper.isButtonClicked(0) && !RoomSwitcher::isActive()) {
                RoomSwitcher::switchRoom(GameScreen::SCREEN_BOOK, true);
                SoundManager::Play(SoundManager::MOVE);
            }
        }
        if (mousePos.x < 20) {
            DrawRectangle(0, 0, 20, screenHeight, SKYBLUE);

            if (inputHelper.isButtonClicked(0) && !RoomSwitcher::isActive()) {
                RoomSwitcher::switchRoom(GameScreen::SCREEN_SHOP, false);
                SoundManager::Play(SoundManager::MOVE);
            }
        }



        // Scroll Inventory

        scrollInventory.render(150,178,569,232);




        // Casting

        if (IsMouseButtonDown(0)) {
            if (castingGrid == nullptr) {
                castingGrid = std::make_shared<CastingGrid>(mousePos,150,300,570,570);
                if (!castingGrid->isInsideConstraint(mousePos)) {
                    castingGrid = nullptr;
                }
            }
            std::vector<std::vector<Vector2>> previousSpells{};

            if (castingGrid != nullptr) castingGrid->update(GetMousePosition(),castSpellsPoints);

            if (castingGrid != nullptr && castingGrid->isFinished()) {
                const Spells::Spell *spell = castingGrid->evaluate();
                emscripten_log(0, spell->getName().c_str());
                castingGrid = nullptr;
            }
        } else {
            if (castingGrid != nullptr) {
                if (castingGrid->isOverlapPreview()) {
                    castingGrid->commitOverlap();
                }

                if (castingGrid->getPointCount() >= 2 || !castingGrid->hasValidMoves()) {
                    const Spells::Spell *spell = castingGrid->evaluate();
                    emscripten_log(0, spell->getName().c_str());
                }

                if (castingGrid->getPointCount() > 1) {
                    castSpells.push_back(castingGrid);
                    castSpellsPoints.push_back(castingGrid->getPoints());
                }
                castingGrid = nullptr;
            }
        }

        BeginDrawing();

        if (castingGrid != nullptr) {
            castingGrid->render();
        }
        for (auto& spell : castSpells) {
            spell->cleanRender();
        }

        if (mousePos.x > 570 && mousePos.x <= 590 &&
            mousePos.y > 300 && mousePos.y <= 570) {
            DrawRectangle(570, 300, 20, 270, SKYBLUE);

            if (inputHelper.isButtonClicked(0) && !RoomSwitcher::isActive() && castingGrid == nullptr && castSpells.size() > 0) {
                if (scrollInventory.addScroll(castSpells)) {
                    castSpells.clear();
                    SoundManager::Play(SoundManager::MOVE);
                }
            }
        }

        EndDrawing();


    }
};