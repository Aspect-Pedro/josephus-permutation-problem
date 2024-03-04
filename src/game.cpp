#include "../raylib/includes/raylib.h"
#include "includes/setup.hpp"
#include "includes/soldiers.hpp"
#include "../raylib/includes/raymath.h"
#include <math.h>
#include <stdio.h>
#include <vector>

#define SOLDIERS 3

int main(void) {
  Screen screen = setupWindow(1920,1080);

  float middleX = screen.screenWidth / 2;
  float middleY = screen.screenHeight / 2;

  float divisions = PI * 2 / SOLDIERS;
  int i = 0;
  Vector2 circleCenter = { middleX, middleY };
  float animation = 0.0f;
  bool circleComplete = false;
  bool killsComplete = false;
  bool isShooting = false;
  int deadSoldiersCount = 0;

  std::vector<Soldier> soldiers;
  std::vector<Soldier> deadSoldiers;

  Shot shot;
  shot.initialPosition = { 0, 0 };
  shot.finalPosition = { 0, 0 };
  shot.actualPosition = { 0, 0 };
  shot.angle = { 0, 0 };
  shot.speed = 0.0f;

  Soldier example = createSoldier({ 0, 0}, 0, 0);
  Soldier *soldier;
  Soldier *prevSoldier;
  Soldier *nextSoldier;

  soldier = &example;
  prevSoldier = &example;
  nextSoldier = &example;

  SetTargetFPS(60);
  while (!WindowShouldClose()) {
    BeginDrawing();
    ClearBackground(BLACK);

    DrawCircleLines(middleX, middleY, RADIUS, WHITE);
    DrawCircleLines(middleX, middleY, RADIUS + 40, YELLOW);

    if (IsKeyDown(KEY_SPACE) && i < SOLDIERS && !circleComplete) {
      Soldier soldier = createSoldier(circleCenter, divisions * i - PI / 2, i);
      soldiers.push_back(soldier);
      i++;

      if (i >= SOLDIERS) {
        i = 0;
        circleComplete = true;
      }

    }

    // Reset the soldiers
    if (IsKeyPressed(KEY_ENTER)) {
      i = 0;
      circleComplete = false;
      killsComplete = false;
      deadSoldiersCount = 0;
      soldiers.clear();
      deadSoldiers.clear();
    }

    if (IsKeyDown(KEY_A) && !isShooting) {

      soldier = &soldiers[i % SOLDIERS];
      prevSoldier = &soldiers[(i + 1) % SOLDIERS];
      nextSoldier = &soldiers[(i + 1) % SOLDIERS];

      while (nextSoldier->isDead) {
        i += 1;
        prevSoldier = &soldiers[i % SOLDIERS];
        nextSoldier = &soldiers[(i + 1) % SOLDIERS];
      }

      prevSoldier = &soldiers[soldier->idLastKilled];

      Vector2 toOrigin = { circleCenter.x - soldier->position.x, circleCenter.y - soldier->position.y };
      Vector2 toNext = { nextSoldier->position.x - soldier->position.x, nextSoldier->position.y - soldier->position.y  };    
      Vector2 toPrev = { prevSoldier->position.x - soldier->position.x, prevSoldier->position.y - soldier->position.y  };
      
      // printf("TO ORIGIN: (%f, %f)\n", toOrigin.x, toOrigin.y);
      // printf("TO NEXT: (%f, %f)\n", toNext.x, toNext.y);

      float newAngle = (float) Vector2Angle(toOrigin, toNext);
      float prevAngle = (float) Vector2Angle(toOrigin, toPrev);

      // printf("NEW ANGLE: %f\n", newAngle * RAD2DEG);

      // printf("%d\n", (i + 1) % SOLDIERS);

      if (soldier->isDead) {

        i += 1;

      } else if (deadSoldiersCount < SOLDIERS - 1) {
        
        printf("%d\n", killsComplete);
        // Turn the soldier to the next soldier in the left
        if (killsComplete) soldier->angle += abs(prevAngle - newAngle); 
        else soldier->angle += newAngle;
        
        Vector2 originShot = { soldier->position.x, soldier->position.y };
        Vector2 finalShot = { nextSoldier->position.x, nextSoldier->position.y };

        shot.initialPosition = originShot;
        shot.finalPosition = finalShot;
        shot.actualPosition = originShot;

        Vector2 vector = Vector2Normalize({ finalShot.x - originShot.x, finalShot.y - originShot.y });

        shot.angle = vector;
        printf("VECTOR: (%f, %f)\n", vector.x, vector.y);

        shot.speed = 3.0f;
        isShooting = true;
      }
    }

    // If there's a shot, draw it
    if (shot.initialPosition.x != 0 && shot.initialPosition.y != 0 && isShooting) {
      DrawRectangle(shot.actualPosition.x, shot.actualPosition.y, 2, 2, WHITE);
      shot.actualPosition.x += shot.angle.x * shot.speed;
      shot.actualPosition.y += shot.angle.y * shot.speed;
    }


    Rectangle shotRec = { shot.actualPosition.x, shot.actualPosition.y, 2, 2 };
    bool collision = CheckCollisionCircleRec(nextSoldier->position, 10, shotRec);

    if (circleComplete && isShooting && collision) {
      nextSoldier->isDead = true;
      nextSoldier->bodyColor = RED;
      nextSoldier->headColor = RED;
      deadSoldiers.push_back(*nextSoldier);
      soldier->idLastKilled = nextSoldier->id;
      i += 1;
      deadSoldiersCount += 1;
      printf("DEAD SOLDIERS: %d\n", deadSoldiersCount);

      isShooting = false;
    }

    // Draw the soldiers
    for (Soldier soldier : soldiers) drawSoldier(&soldier, circleCenter);

    if (i >= SOLDIERS) {
      
      killsComplete = true;

    }

    EndDrawing();
  }

  CloseWindow();

  return 0;
}
