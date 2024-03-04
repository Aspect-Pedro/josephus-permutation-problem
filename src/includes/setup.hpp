#pragma once
#include "../../raylib/includes/raylib.h"

typedef struct screenResolution {
    int screenWidth;
    int screenHeight;
} Screen;

Screen setupWindow(int width, int height);