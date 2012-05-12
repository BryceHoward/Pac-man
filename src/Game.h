#ifndef GAME_H
#define GAME_H

#include "SDL.h"
#include "SDL/SDL_ttf.h"
#include "Timer.h"

class Game
{
    public:
        Game();
        bool init();
        void start();
        void input(SDL_Event event);
        void updateScreen();
        void capFPS();
        void displayFPS();
        Timer fpsCapTimer;
        Timer fpsCalcTimer;
        bool quit;
        virtual ~Game();

    protected:
    private:
        int fps;
        int fpsFrame;
        SDL_Surface *icon;
};

const static int SCREEN_WIDTH = 568;
const static int SCREEN_HEIGHT = 760;
const static int SCREEN_BPP = 32;
static SDL_Surface *screen = SDL_SetVideoMode( SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE );

#endif
