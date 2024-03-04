#pragma once
#include "../../raylib/includes/raylib.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define RADIUS 400

typedef struct soldier {
    Vector2 position;
    float angle;
    float idAngle;
    Color gunColor;
    Color headColor;
    Color bodyColor;
    int id;
    float width;
    float height;
    Vector2 origin;
    bool isDead;
    int idLastKilled;
} Soldier;

typedef struct shot {
    Vector2 angle;
    Vector2 initialPosition;
    Vector2 actualPosition;
    Vector2 finalPosition;
    float speed;
} Shot;

Soldier createSoldier(Vector2 circleCenter, float divisions, int i);

void drawSoldier(Soldier *soldier, Vector2 circleCenter);