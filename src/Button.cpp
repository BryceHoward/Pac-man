#include "Button.h"
#include <sstream>

Button::Button(int x, int y)
    :
    mouseOver(false),
    color({255, 255 , 255}),
<<<<<<< HEAD
<<<<<<< HEAD
    whitePixel(load_image("resources/images/Blank Pixel.png")),
=======
    whitePixel(load_image("Blank Pixel.png")),
>>>>>>> 9ee030802e80d466304013ed104b0372c5e1b78d
=======
    whitePixel(load_image("Blank Pixel.png")),
>>>>>>> 9ee030802e80d466304013ed104b0372c5e1b78d
    box({x, y, 0, 0})
{

}

void Button::update()
{
    if(mouseOver)
    {
        apply_surface(box.x, box.y, imageOnMouseOver, screen);
    }
    else
    {
        apply_surface(box.x, box.y, image, screen);
    }
}

void Button::checkIfMouseover(SDL_Event &event)
{
    if (event.type == SDL_MOUSEMOTION)
    {
        int x = event.motion.x;
        int y = event.motion.y;

        if (x > box.x && x < box.x + box.w && y > box.y && y < box.y + box.h)
        {
            mouseOver = true;
        }
        else
        {
            mouseOver = false;
        }
    }
}

bool Button::clicked(SDL_Event &event)
{
    checkIfMouseover(event);

    if (event.type == SDL_MOUSEBUTTONDOWN && mouseOver)
    {
        return true;
    }

    return false;
}

void Button::load_messege(std::string messege)
{
<<<<<<< HEAD
<<<<<<< HEAD
    font = TTF_OpenFont("resources/images/BitNano.ttf", 65);
=======
    font = TTF_OpenFont("BitNano.ttf", 65);
>>>>>>> 9ee030802e80d466304013ed104b0372c5e1b78d
=======
    font = TTF_OpenFont("BitNano.ttf", 65);
>>>>>>> 9ee030802e80d466304013ed104b0372c5e1b78d

    std::stringstream s;

    s << messege;

    image = TTF_RenderText_Solid(font, s.str().c_str(), color);

    imageOnMouseOver = TTF_RenderText_Solid(font, s.str().c_str(), color);

<<<<<<< HEAD
<<<<<<< HEAD
    // creates a white border around imageOnMouseOver
=======
>>>>>>> 9ee030802e80d466304013ed104b0372c5e1b78d
=======
>>>>>>> 9ee030802e80d466304013ed104b0372c5e1b78d
    for (int x = 0, maxX = imageOnMouseOver->w; x < maxX; x++)
    {
        for (int y = 0, maxY = imageOnMouseOver->h; y < maxY; y++)
        {
            if (x < 1  || y < 1 || (y + 3 > maxY || (x + 3 > maxX)))
            {
                apply_surface(x, y, whitePixel, imageOnMouseOver);
            }
        }
    }

    box.w = image->w;
    box.h = image->h;

    TTF_CloseFont(font);
}

void Button::set_coords(int x, int y)
{
    box.x = x;
    box.x = y;
}

Button::~Button()
{
    //dtor
}
