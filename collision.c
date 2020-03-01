#include "collision.h"
int boundingBoxCollision(SDL_Rect a, SDL_Rect b)
{
    return (abs(a.x - b.x) * 2 < (a.w + b.w)) &&
           (abs(a.y - b.y) * 2 < (a.h + b.h));
}