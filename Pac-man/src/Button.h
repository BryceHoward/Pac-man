#ifndef BUTTON_H
#define BUTTON_H

#include <string>

#include "SDL.h"
#include "Utility.h"
#include "Game.h"


class Button
{
    public:
        Button(int x, int y);
        virtual ~Button();

        void update();
        void load_messege(std::string messege);
        void set_coords(int x, int y);

        bool clicked(SDL_Event &event);


    protected:

    private:
        SDL_Rect box;

        SDL_Color color;

        TTF_Font *font;

        SDL_Surface *image;
        SDL_Surface *imageOnMouseOver;
        SDL_Surface *whitePixel;

        void checkIfMouseover(SDL_Event &event);

        bool mouseOver;
};

#endif // BUTTON_H
