#pragma once
#include "raylib.h"
#include <functional>

class Slider {
public:
  Slider(Rectangle bounds, float initialValue,
         std::function<void(float)> onValueChanged)
      : bounds(bounds), value(initialValue), isDragging(false),
        useTextures(false), onValueChanged(onValueChanged) {}
  void draw();
  void update();
  void setTextures(Texture2D track, Texture2D knob);

private:
  Rectangle bounds;
  float value;
  bool isDragging;
  std::function<void(float)> onValueChanged;

  Texture2D trackTexture;
  Texture2D knobTexture;
  bool useTextures;
};
