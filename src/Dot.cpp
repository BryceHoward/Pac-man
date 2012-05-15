#include "Dot.h"

Dot::Dot(int x, int y)
    :
    eaten(false)
{
<<<<<<< HEAD
    load_sprite("resources/images/Ball thingy.png");
=======
    load_sprite("Ball thingy.png");
>>>>>>> 9ee030802e80d466304013ed104b0372c5e1b78d

    box.x = x;
    box.y = y;
    box.w = width;
    box.h = height;
}

Dot::~Dot()
{
    //dtor
}

void Dot::update()
{
    if (!eaten)
    {
        apply_surface(box.x, box.y, image, screen);
    }
}

void check_collision(const SDL_Rect &A, std::vector<Dot*> &B)
{
    int leftA, leftB;
    int rightA, rightB;
    int topA, topB;
    int bottomA, bottomB;

    leftA = A.x + 10;
    rightA = A.x + A.w - 10;
    topA = A.y + 10;
    bottomA = A.y + A.h - 10;

    for (int row = 0; row < B.size(); row++)
    {
        if (!B[row]->eaten)
        {
            leftB = B[row]->box.x;
            rightB = B[row]->box.x + B[row]->box.w;
            topB = B[row]->box.y;
            bottomB = B[row]->box.y + B[row]->box.h;

            if (!((bottomA <= topB) || (topA >= bottomB) || (rightA <= leftB) || (leftA >= rightB)))
            {
                B[row]->eaten = true;
            }
        }
    }
}
