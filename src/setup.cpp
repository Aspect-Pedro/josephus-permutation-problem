#include "includes/setup.hpp"

Screen setupWindow(int width, int height) {
    Screen screen = { width, height };
    InitWindow(screen.screenWidth, screen.screenHeight, "Procedural Generation");
    ToggleFullscreen();
    return screen;
}