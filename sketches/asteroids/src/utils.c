#include "utils.h"

void wrapAroundScreen(Vector2* position, float radius, int screenWidth, int screenHeight) {
    // Handle horizontal wrapping
    if (position->x < -radius) {
        position->x = (float)screenWidth + radius;
    } else if (position->x > (float)screenWidth + radius) {
        position->x = -radius;
    }
    
    // Handle vertical wrapping
    if (position->y < -radius) {
        position->y = (float)screenHeight + radius;
    } else if (position->y > (float)screenHeight + radius) {
        position->y = -radius;
    }
}
