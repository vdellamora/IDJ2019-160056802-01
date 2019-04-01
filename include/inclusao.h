//INCLUDE EVERYTHING
//#define VITOR

#ifdef VITOR
    #include "SDL.h"
    #include "SDL_mixer.h"
    #include "SDL_ttf.h"
    #include "SDL_image.h"
#elif __APPLE__
    #include <SDL2/SDL.h>
    #include <SDL2/SDL_mixer.h>
    #include <SDL2/SDL_image.h>
    #include <SDL2/SDL_ttf.h>
#elif _WIN32
    #include <SDL2/SDL.h>
    #include <SDL2/SDL_mixer.h>
    #include <SDL2/SDL_image.h>
    #include <SDL2/SDL_ttf.h>
#elif __linux__
    #include <SDL2/SDL.h>
    #include <SDL2/SDL_mixer.h>
    #include <SDL2/SDL_image.h>
    #include <SDL2/SDL_ttf.h>
#else
    #error "Unknown compiler"
#endif