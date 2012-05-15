#include "PowerUp.h"

PowerUp::PowerUp(int x, int y)
    :
    eaten(false),
    neutral(false),
    anim_count(0)
{
<<<<<<< HEAD
    load_sprite("resources/images/Large Dot.png");
=======
    load_sprite("Large Dot.png");
>>>>>>> 9ee030802e80d466304013ed104b0372c5e1b78d

    box.x = x;
    box.y = y;
    box.w = width;
    box.h = height;
}

PowerUp::~PowerUp()
{
    //dtor
}

void PowerUp::update(const SDL_Rect &player, std::vector<Ghost*> &ghosts)
{
   if (!neutral)
   {
       if (eaten)
       {
           weaken_ghosts(ghosts);
           eaten = false;
           neutral = true;
       }
       else
       {
           if (anim_count < 80 || (anim_count < 95 && anim_count > 90 ))
           {
               apply_surface(box.x, box.y, image, screen);
           }

           if (anim_count > 100) anim_count = 0;

           anim_count++;
           check_collision(player, *this);
       }
   }
}

void PowerUp::update()
{
    if (!eaten && !neutral)
    {
        apply_surface(box.x, box.y, image, screen);
    }
}

void PowerUp::weaken_ghosts(std::vector<Ghost*> &ghosts)
{
    for (int x = 0; x < ghosts.size(); x++)
    {
        if(!ghosts[x]->is_dead()) ghosts[x]->start_weakTimer();
    }
}

void check_collision(const SDL_Rect &A, const PowerUp &B)
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
