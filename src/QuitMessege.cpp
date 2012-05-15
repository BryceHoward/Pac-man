#include "QuitMessege.h"

QuitMessege::QuitMessege(std::string filename, int x, int y)
    :
    image(load_image(filename.c_str())),
    box({x, y, 0, 0}),
    yes(180, 320),
    no(350, 320),
    _chosen(false),
    _quit(false)
{

}

QuitMessege::~QuitMessege()
{
    //dtor
}

void QuitMessege::update()
{
    if(!(image == NULL))
    {
        apply_surface(box.x, box.y, image, screen);
    }

    yes.update();
    no.update();
}

void QuitMessege::input(SDL_Event &event)
{
    if (yes.clicked(event))
    {
        _chosen = true;
        _quit = true;
    }
    else if (no.clicked(event))
    {
        _chosen = true;
        _quit = false;
    }
}

void QuitMessege::load_buttons(std::string first_button, std::string second_button)
{
    yes.load_messege(first_button);
    no.load_messege(second_button);
}
