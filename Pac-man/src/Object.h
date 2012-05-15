#ifndef OBJECT_H
#define OBJECT_H

#include "SDL.h"
#include "Game.h"
#include "Utility.h"
#include <string>

class Object
{
    public:
        virtual ~Object();

        virtual void update();

        int getX() const {return box.x;}
        int getY() const {return box.y;}
        SDL_Rect getRect() const {return box;}
        SDL_Surface* getImg() const {return image;}

    protected:
        Object();

        void load_sprite(std::string filename);

        SDL_Rect box;
        SDL_Surface *image;

    private:
};

#endif // OBJECT_H
