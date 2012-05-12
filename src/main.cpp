
#include "SDL/SDL.h"
#include "Game.h"
#include "Level.h"
#include "Timer.h"
#include "Object.h"
#include "MoveableObject.h"
#include "Player.h"
#include "Ghost.h"
#include "PowerUp.h"
#include "Dot.h"
#include "Titlescreen.h"


int main ( int argc, char** argv )
{

    Game game;
    SDL_Event event;
    Level level("Pacman Map.png");
    Titlescreen titlescreen;

    if (!game.init())
    {
        return 1;
    }

    while (!game.quit)
    {
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                game.quit = true;
            }
        }

        titlescreen.start(event, game);

        if (!game.quit) level.start(event, game);
    }

    return 0;
}
