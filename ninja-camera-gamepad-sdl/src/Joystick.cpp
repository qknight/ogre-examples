/*
  (copyleft) joachim schiele <js@lastlog.de>
    http://de.wikibooks.org/wiki/SDL:_Joystick

  based on my previous code which can be found here:
    http://lastlog.de/wiki/index.php/SDL-joystick and
    http://lastlog.de/misc/sdl_joystick_demo.html

  example2.cpp can be compiled with:
    g++ example2.cpp -o example2 `sdl-config --libs` `sdl-config --cflags`

*/
#include <iostream>
#include "Joystick.h"

Joystick::Joystick () {
    if ( SDL_InitSubSystem ( SDL_INIT_JOYSTICK ) < 0 )
    {
        std::cout << "Unable to initialize Joystick: " << SDL_GetError() << std::endl;
        exit(1);
    }
    
    std::cout << SDL_NumJoysticks () << " joystick(s) found" << std::endl;

    if (SDL_NumJoysticks() == 0 ) {
        joy1=NULL;
        return;
    }
    joy1 = SDL_JoystickOpen ( 0 );

    if ( joy1 == NULL ) {
        std::cout << "SDL backend: could not open joystick" << std::endl;
    }

    std::cout << SDL_JoystickNumAxes ( joy1 ) << " axis" << std::endl;
    std::cout << SDL_JoystickNumBalls ( joy1 ) << " balls" << std::endl;
    std::cout << SDL_JoystickNumHats ( joy1 ) << " heads" << std::endl;
    std::cout << SDL_JoystickNumButtons ( joy1 ) << " knobs" << std::endl;

    //SDL_JoystickEventState (SDL_ENABLE);
    // this will alter the behaviour of the event queue of the sdl system
    SDL_JoystickEventState ( SDL_QUERY );
}

Joystick::~Joystick() {
  //free something...?
}

// needs to be called every time before the js1 device is used
void Joystick::update() {
    SDL_JoystickUpdate ();
}
