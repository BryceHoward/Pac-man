#ifndef TITLESCREEN_H
#define TITLESCREEN_H

#include "Game.h"
#include "Utility.h"
#include "Ghost.h"
#include "Player.h"
#include "Button.h"

class Titlescreen
{
    public:
        Titlescreen();
        virtual ~Titlescreen();

        void start(SDL_Event& event, Game& game);

    protected:

    private:
        void update();
        void set_up();
        void reset() {_chosen = false;}

        int anim;

        bool _chosen;

        const static int width = 32;
        const static int height = 32;

        SDL_Rect ghost_clips[8];

        SDL_Surface *image;
        SDL_Surface *player;
        SDL_Surface *ghosts;
        SDL_Surface *dot;

        Button play;
        Button quit;
};

#endif // TITLESCREEN_H
