#ifndef QUITMESSEGE_H
#define QUITMESSEGE_H

#include "Button.h"

class QuitMessege
{
    public:
        QuitMessege(std::string filename, int x, int y);
        virtual ~QuitMessege();

        void update();
        void input(SDL_Event &event);
        void load_buttons(std::string first_button, std::string second_button);
        void reset() {_chosen = false; _quit = false;}

        bool chosen() const {return _chosen;}
        bool quit() const {return _quit;}

    protected:

    private:
        bool _chosen;
        bool _quit;

        Button yes;
        Button no;

        SDL_Rect box;

        SDL_Surface *image;
};

#endif // QUITMESSEGE_H
