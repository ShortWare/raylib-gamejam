#include "slider.hpp"

void Slider::setTextures(Texture2D track, Texture2D knob) {
  trackTexture = track;
  knobTexture = knob;
  useTextures = true;
}

void Slider::update() {
  Vector2 mousePoint = GetMousePosition();
  Rectangle dragArea = {bounds.x, bounds.y - 10, bounds.width,
                        bounds.height + 20};

  if (CheckCollisionPointRec(mousePoint, dragArea) &&
      IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
    isDragging = true;
  }

  if (isDragging) {
    if (IsMouseButtonUp(MOUSE_BUTTON_LEFT)) {
      isDragging = false;
    }

    value = (mousePoint.x - bounds.x) / bounds.width;
    if (value < 0.0f)
      value = 0.0f;
    if (value > 1.0f)
      value = 1.0f;

    if (onValueChanged)
      onValueChanged(value);
  }
}

void Slider::draw() {
  Rectangle knob = {bounds.x + (value * bounds.width) - 10, bounds.y - 5, 20,
                    bounds.height + 10};

  if (useTextures) {
    DrawTexturePro(
        trackTexture,
        {0, 0, (float)trackTexture.width, (float)trackTexture.height}, bounds,
        {0, 0}, 0.0f, WHITE);
    DrawTexturePro(knobTexture,
                   {0, 0, (float)knobTexture.width, (float)knobTexture.height},
                   knob, {0, 0}, 0.0f, WHITE);
  } else {
    DrawRectangleRec(bounds, LIGHTGRAY);
    DrawRectangleRec({bounds.x, bounds.y, value * bounds.width, bounds.height},
                     BLUE);
    Color knobColor = isDragging ? DARKBLUE : GRAY;
    DrawRectangleRec(knob, knobColor);
  }
}
