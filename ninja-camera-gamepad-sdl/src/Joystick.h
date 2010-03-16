#ifndef JOYSTICK_H
#define JOYSTICK_H

#include "SDL.h"
#include <stdio.h>

class Joystick {
public:
    Joystick();
    ~Joystick();
    SDL_Joystick* joy1;
    void update();
};

#endif // JOYSTICK_H
