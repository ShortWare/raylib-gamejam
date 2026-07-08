//
// Created by Pd on 7/8/26.
//

#ifndef RAYLIB_GAME_TEMPLATE_SCROLLINVENTORY_H
#define RAYLIB_GAME_TEMPLATE_SCROLLINVENTORY_H

#include "spells.h"
#include "castingGrid.h"
#include "../../cmake-build-debug/_deps/raylib-src/src/raymath.h"

class ScrollInventory {
    std::vector<std::vector<std::shared_ptr<CastingGrid>>> scrolls{};
    int capacity = 1;
    Vector2 spacing {5, 5};
    Vector2 scrollSizeVertical {15,40};
    Vector2 scrollSizeHorizontal {15,15};
    Vector2 padding {1,2};

public:
    ScrollInventory(int _capacity) {
        capacity = _capacity;
    }
    std::vector<std::vector<std::shared_ptr<CastingGrid>>> getScrolls() { return scrolls; }


    bool addScroll(const std::vector<std::shared_ptr<CastingGrid>>& scroll) {
        if (scrolls.size() >= capacity) return false;
        scrolls.push_back(scroll);
        return true;
    }


    void render(float x1, float y1, float x2, float y2) {
        Vector2 nextPos;

        BeginDrawing();

        if ((scrollSizeVertical.x+spacing.x)*scrolls.size() + padding.x*2 < x2-x1) {
            nextPos = Vector2Add({x1, y2-scrollSizeVertical.y}, padding);

            for (std::vector scroll : scrolls) {
                DrawRectangle(nextPos.x, nextPos.y, scrollSizeVertical.x, scrollSizeVertical.y, WHITE);
                nextPos.x += scrollSizeVertical.x+spacing.x;
            }
        } else {
            nextPos = Vector2Add({x1, y2-scrollSizeHorizontal.y}, padding);

            for (std::vector scroll : scrolls) {
                DrawRectangle(nextPos.x, nextPos.y, scrollSizeHorizontal.x, scrollSizeHorizontal.y, WHITE);
                nextPos.x += scrollSizeHorizontal.x+spacing.x;

                if (nextPos.x + scrollSizeHorizontal.x + padding.x < x2-x1) continue;

                nextPos.x = x1 + padding.x + scrollSizeHorizontal.x/2;
                nextPos.y -= scrollSizeHorizontal.y+spacing.y;
            }
        }

        EndDrawing();
    }
};

#endif //RAYLIB_GAME_TEMPLATE_SCROLLINVENTORY_H
