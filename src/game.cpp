#include "../raylib/includes/raylib.h"
#include "includes/setup.hpp"

int main(void) {
  Screen screen = setupWindow(1920,1080);

  SetTargetFPS(60);

  while (!WindowShouldClose()) {
    BeginDrawing();
    ClearBackground(RAYWHITE);


    EndDrawing();
  }

  CloseWindow();

  return 0;
}
