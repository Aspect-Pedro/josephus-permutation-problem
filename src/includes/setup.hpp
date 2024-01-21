#include "../../raylib/includes/raylib.h"

#ifndef __SETUP_HPP__
#define __SETUP_HPP__

typedef struct screenResolution {
    int screenWidth;
    int screenHeight;
} Screen;

Screen setupWindow(int width, int height);



#endif