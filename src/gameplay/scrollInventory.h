//
// Created by Pd on 7/8/26.
//

#ifndef RAYLIB_GAME_TEMPLATE_SCROLLINVENTORY_H
#define RAYLIB_GAME_TEMPLATE_SCROLLINVENTORY_H

#include <memory>

#include "spells.h"
#include "castingGrid.h"
#include "../../cmake-build-debug/_deps/raylib-src/src/raymath.h"
#include "../tools/inputHelper.h"

class Workshop;

class ScrollInventory {
    std::vector<std::vector<std::shared_ptr<CastingGrid>>> scrolls{};
    int capacity = 1;
    Vector2 spacing {5, 5};
    Vector2 scrollSizeVertical {15,40};
    Vector2 scrollSizeHorizontal {15,15};
    Vector2 padding {1,2};
    bool isHorizontal = false;
    int selectedScroll = -1;
    Workshop *workshop;


    struct ScrollPos {
        float x, y;

        ScrollPos(float _x, float _y) : x(_x), y(_y) {}
    };

    std::vector<ScrollPos> scrollPositions {};

public:
    ScrollInventory(int _capacity, Workshop *_workshop);

    std::vector<std::vector<std::shared_ptr<CastingGrid>>> getScrolls() { return scrolls; }


    bool addScroll(const std::vector<std::shared_ptr<CastingGrid>>& scroll) {
        if (scrolls.size() >= capacity) return false;
        scrolls.push_back(scroll);
        return true;
    }

    void updateScrolls(float x1, float y1, float x2, float y2) {
        Vector2 nextPos;
        scrollPositions.clear();
        isHorizontal = false;

        if ((scrollSizeVertical.x+spacing.x)*scrolls.size() + padding.x*2 < x2-x1) {
            nextPos = Vector2Add({x1, y2-scrollSizeVertical.y}, padding);

            for (std::vector scroll : scrolls) {
                scrollPositions.emplace_back(nextPos.x, nextPos.y);
                nextPos.x += scrollSizeVertical.x+spacing.x;
            }
        } else {
            isHorizontal = true;
            nextPos = Vector2Add({x1, y2-scrollSizeHorizontal.y}, padding);

            for (std::vector scroll : scrolls) {
                scrollPositions.emplace_back(nextPos.x, nextPos.y);
                nextPos.x += scrollSizeHorizontal.x+spacing.x;

                if (nextPos.x + scrollSizeHorizontal.x + padding.x < x2-x1) continue;

                nextPos.x = x1 + padding.x + scrollSizeHorizontal.x/2;
                nextPos.y -= scrollSizeHorizontal.y+spacing.y;
            }
        }
    }

    void updateMouse(Vector2 mousePos, float x1, float y1, float x2, float y2, InputHelper inputHelper) {
        selectedScroll = -1;
        if (mousePos.x < x1 || mousePos.y < y1 || mousePos.x > x2 || mousePos.y > y2) return;

        for (int i = 0; i < scrollPositions.size(); i++) {
            const ScrollPos& scrollPos = scrollPositions[i];

            if (isHorizontal) {
                if (mousePos.x > scrollPos.x && mousePos.x < scrollPos.x + scrollSizeHorizontal.x &&
                    mousePos.y > scrollPos.y && mousePos.y < scrollPos.y + scrollSizeHorizontal.y) {
                    selectedScroll = i;
                    if (inputHelper.isButtonClicked(0))
                        selectScroll(i, x1, y1, x2, y2);
                }
            } else {
                if (mousePos.x > scrollPos.x && mousePos.x < scrollPos.x + scrollSizeVertical.x &&
                    mousePos.y > scrollPos.y && mousePos.y < scrollPos.y + scrollSizeVertical.y) {
                    selectedScroll = i;
                    if (inputHelper.isButtonClicked(0))
                        selectScroll(i, x1, y1, x2, y2);
                }
            }
        }
    }


    void selectScroll(int id, float x1, float y1, float x2, float y2);


    void render() {

        BeginDrawing();

        for (int i = 0; i < scrollPositions.size(); i++) {
            const ScrollPos& scrollPos = scrollPositions[i];

            if (isHorizontal) {
                DrawRectangle(scrollPos.x, scrollPos.y, scrollSizeHorizontal.x, scrollSizeHorizontal.y, i == selectedScroll ? SKYBLUE : WHITE);
            } else {
                DrawRectangle(scrollPos.x, scrollPos.y, scrollSizeVertical.x, scrollSizeVertical.y, i == selectedScroll ? SKYBLUE : WHITE);
            }
        }


        EndDrawing();
    }
};

#endif //RAYLIB_GAME_TEMPLATE_SCROLLINVENTORY_H
