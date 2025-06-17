#ifndef LASER_H
#define LASER_H

#include "raylib.h"
#include "ship.h"

#define MAX_LASERS 20

typedef struct Laser {
  Vector2 position;
  Vector2 velocity;
  Color color;
  bool active;
} Laser;

void initializeLasers(Laser* lasers);

void fireLaser(Laser* lasers, Ship* ship, int* laserCount, float* lastFireTime);

void updateLasers(Laser* lasers, int screenWidth, int screenHeight);

void drawLasers(Laser* lasers);

#endif // LASER_H