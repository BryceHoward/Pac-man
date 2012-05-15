#include "Game.h"
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "SDL/SDL_mixer.h"
#include "Utility.h"
#include <vector>
#include <iostream>
#include <sstream>
#include <stdlib.h>
#include <time.h>

using namespace std;

Game::Game()
{
    quit = false;
    fps = 60;
}

Game::~Game()
{
    //dtor
}

bool Game::init()
{
<<<<<<< HEAD
    icon = SDL_LoadBMP("resources/images/Pacman Icon.bmp");
=======
    icon = SDL_LoadBMP("Pacman Icon.bmp");
>>>>>>> 9ee030802e80d466304013ed104b0372c5e1b78d

    if (icon == NULL)
    {
        return false;
    }
<<<<<<< HEAD
    else

    SDL_SetColorKey( icon, SDL_SRCCOLORKEY, SDL_MapRGB( icon->format, 0, 0xFF, 0xFF ) );
=======
    else SDL_SetColorKey( icon, SDL_SRCCOLORKEY, SDL_MapRGB( icon->format, 0, 0xFF, 0xFF ) );

>>>>>>> 9ee030802e80d466304013ed104b0372c5e1b78d
    SDL_WM_SetIcon(icon, NULL);
    SDL_WM_SetCaption( "Pacaman", NULL );

    if( SDL_Init( SDL_INIT_EVERYTHING ) == -1 )
    {
        return false;
    }

    if( screen == NULL )
    {
        return false;
    }

    if (TTF_Init() == -1)
    {
        return false;
    }

    if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096) == -1)
    {
        return false;
    }

    srand(time(NULL));

    return true;
}

void Game::updateScreen()
{
    SDL_Flip(screen);
}


void Game::capFPS()
{
    if (fpsCapTimer.get_ticks() < 1000/fps)
    {
        SDL_Delay(1000/fps - fpsCapTimer.get_ticks());
    }
}

void Game::displayFPS()
{
    fpsFrame++;

    if (fpsCalcTimer.get_ticks() > 1000)
        {
            stringstream caption;

            caption.str();
            caption << "Pacman                                                              FPS: " <<  fpsFrame;

            SDL_WM_SetCaption(caption.str().c_str(), NULL);

            fpsFrame = 0;
            fpsCalcTimer.start();
        }
}
