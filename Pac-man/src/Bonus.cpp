#include "Bonus.h"

Bonus::Bonus(std::string filename)
    :
    eaten(false),
    neutral(true)
{
    load_sprite(filename);

    box.x = 270;
    box.y = 420;
    box.w = width;
    box.h = height;
}

Bonus::~Bonus()
{
    //dtor
}

void Bonus::update()
{
    if (!eaten && !neutral)
    {
        apply_surface(box.x, box.y, image, screen);
    }
}

void Bonus::update(const SDL_Rect& player)
{
    if (!neutral)
    {
        if (eaten)
        {
            eaten = false;
            neutral = true;
        }
        else
        {
            apply_surface(box.x, box.y, image, screen);
            check_collision(player, *this);
        }
    }

}

void check_collision(const SDL_Rect &A, Bonus &B)
{
    int leftA, leftB;
    int rightA, rightB;
    int topA, topB;
    int bottomA, bottomB;

    leftA = A.x;
    rightA = A.x + A.w;
    topA = A.y;
    bottomA = A.y + A.h;

    if (!B.eaten)
    {
        leftB = B.box.x;
        rightB = B.box.x + B.box.w;
        topB = B.box.y;
        bottomB = B.box.y + B.box.h;

        if (!((bottomA <= topB) || (topA >= bottomB) || (rightA <= leftB) || (leftA >= rightB)))
        {
            if (!B.eaten && !B.neutral)
            {
                B.eaten = true;
            }
        }
    }
}
