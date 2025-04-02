//
// Created by Baka-tannn on 23/2/2025.
//

#ifndef PHYSICS_H
#define PHYSICS_H

#include <SDL.h>
#include "vector.h"

class Physics {
public:
    static bool isCollision(const SDL_Rect& rect1, const SDL_Rect& rect2);
    static void reflect(SDL_Rect& rect, Vector& velocity, const SDL_Rect& boundary);
    static void reflectObject(SDL_Rect& rect, Vector& velocity, const SDL_Rect& object);
    static bool isHole(const SDL_Rect& ballRect, const Vector& prevPos, const Vector& currPos);

};

#endif // PHYSICS_H

