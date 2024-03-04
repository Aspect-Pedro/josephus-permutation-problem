#include "includes/soldiers.hpp"

Soldier createSoldier(Vector2 circleCenter, float divisions, int i) {
    // printf("%f\n", divisions); // (1
    float angle = (float) divisions;
    float x = circleCenter.x + RADIUS * cos(angle);
    float y = circleCenter.y + RADIUS * sin(angle);

    Soldier soldier;
    soldier.position = { x, y };
    soldier.angle = angle;
    soldier.idAngle = angle;
    soldier.gunColor = RED;
    soldier.headColor = BLUE;
    soldier.bodyColor = GREEN;
    soldier.isDead = false;
    soldier.id = i;
    soldier.width = 30;
    soldier.height = 2;
    soldier.origin = { soldier.width / 2, soldier.height / 2 };
    soldier.idLastKilled = 0;
    return soldier;
}

void drawSoldier(Soldier *soldier, Vector2 circleCenter) {
    DrawRectanglePro({ soldier->position.x, soldier->position.y, soldier->width, soldier->height }, {soldier->origin.x + 5, soldier->origin.y}, soldier->angle * RAD2DEG, soldier->gunColor);

    DrawCircle(soldier->position.x, soldier->position.y, 10, soldier->headColor);
    DrawCircle(soldier->position.x, soldier->position.y, 5, soldier->bodyColor);

    if (!soldier->isDead) DrawText(TextFormat("%d", soldier->id + 1), circleCenter.x - 8 + (440 * cos(soldier->idAngle)), circleCenter.y - 8 + 440 * (sin(soldier->idAngle)), 15, WHITE);
}