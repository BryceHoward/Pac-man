#include "Button.h"
#include <sstream>

Button::Button(int x, int y)
    :
    mouseOver(false),
    color({255, 255 , 255}),
    whitePixel(load_image("Blank Pixel.png")),
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
    font = TTF_OpenFont("BitNano.ttf", 65);

    std::stringstream s;

    s << messege;

    image = TTF_RenderText_Solid(font, s.str().c_str(), color);

    imageOnMouseOver = TTF_RenderText_Solid(font, s.str().c_str(), color);

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
