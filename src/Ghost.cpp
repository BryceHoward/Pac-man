#include "Ghost.h"
#include <sstream>

Ghost::Ghost(int ghost_color, bool is_smart)
    :
    color(ghost_color),
    smart(is_smart),
    weak(false),
    dead(false),
    eaten(false),
    last_clip(0),
    curr_clip(0),
    dead_stage(0),
    anim_counter(0),
    curr_anim(0),
    weak_anim(0),
    weak_animCntr(0)
{
<<<<<<< HEAD
    load_sprite("resources/images/Ghost Sprite Sheet.png");
=======
    load_sprite("Ghost Sprite Sheet.png");
>>>>>>> 9ee030802e80d466304013ed104b0372c5e1b78d
    set_clips();
    change_direction();

    if (color > 3)
    {
        color = 0;
    }
    else color *= 8;

    dead_offset = 32 - color;

    box.x = 268;
    box.y = 292;
    box.w = width;
    box.h = height;

    att_timer.start();
}

Ghost::~Ghost()
{
    //dtor
}

void Ghost::move(const std::vector<SDL_Rect*> &map, Player &player)
{
    check_weakTimer();

    if (dead) phone_home();
    else if(weak)
    {
        if (move_timer.get_ticks() > 20)
        {
            wander(map);
            check_collision(player.getRect(), *this);
            move_timer.start();
        }
    }
    else if (smart) attack(map, player);
    else wander(map);
}

void Ghost::update()
{
    apply_surface(box.x, box.y, image, screen, get_clip());
}

void Ghost::set_clips()
{
    clips[0].x = 0;
    clips[0].y = 0;
    clips[0].w = width;
    clips[0].h = height;

    clips[1].x = width;
    clips[1].y = 0;
    clips[1].w = width;
    clips[1].h = height;

    clips[2].x = width * 2;
    clips[2].y = 0;
    clips[2].w = width;
    clips[2].h = height;

    clips[3].x = width * 3;
    clips[3].y = 0;
    clips[3].w = width;
    clips[3].h = height;

    clips[4].x = 0;
    clips[4].y = height;
    clips[4].w = width;
    clips[4].h = height;

    clips[5].x = width;
    clips[5].y = height;
    clips[5].w = width;
    clips[5].h = height;

    clips[6].x = width * 2;
    clips[6].y = height;
    clips[6].w = width;
    clips[6].h = height;

    clips[7].x = width * 3;
    clips[7].y = height;
    clips[7].w = width;
    clips[7].h = height;

    clips[8].x = 0;
    clips[8].y = height * 2;
    clips[8].w = width;
    clips[8].h = height;

    clips[9].x = width;
    clips[9].y = height * 2;
    clips[9].w = width;
    clips[9].h = height;

    clips[10].x = width * 2;
    clips[10].y = height * 2;
    clips[10].w = width;
    clips[10].h = height;

    clips[11].x = width * 3;
    clips[11].y = height * 2;
    clips[11].w = width;
    clips[11].h = height;

    clips[12].x = 0;
    clips[12].y = height * 3;
    clips[12].w = width;
    clips[12].h = height;

    clips[13].x = width;
    clips[13].y = height * 3;
    clips[13].w = width;
    clips[13].h = height;

    clips[14].x = width * 2;
    clips[14].y = height * 3;
    clips[14].w = width;
    clips[14].h = height;

    clips[15].x = width * 3;
    clips[15].y = height * 3;
    clips[15].w = width;
    clips[15].h = height;

    clips[16].x = 0;
    clips[16].y = height * 4;
    clips[16].w = width;
    clips[16].h = height;

    clips[17].x = width;
    clips[17].y = height * 4;
    clips[17].w = width;
    clips[17].h = height;

    clips[18].x = width * 2;
    clips[18].y = height * 4;
    clips[18].w = width;
    clips[18].h = height;

    clips[19].x = width * 3;
    clips[19].y = height * 4;
    clips[19].w = width;
    clips[19].h = height;

    clips[20].x = 0;
    clips[20].y = height * 5;
    clips[20].w = width;
    clips[20].h = height;

    clips[21].x = width;
    clips[21].y = height * 5;
    clips[21].w = width;
    clips[21].h = height;

    clips[22].x = width * 2;
    clips[22].y = height * 5;
    clips[22].w = width;
    clips[22].h = height;

    clips[23].x = width * 3;
    clips[23].y = height * 5;
    clips[23].w = width;
    clips[23].h = height;

    clips[24].x = 0;
    clips[24].y = height * 6;
    clips[24].w = width;
    clips[24].h = height;

    clips[25].x = width;
    clips[25].y = height * 6;
    clips[25].w = width;
    clips[25].h = height;

    clips[26].x = width * 2;
    clips[26].y = height * 6;
    clips[26].w = width;
    clips[26].h = height;

    clips[27].x = width * 3;
    clips[27].y = height * 6;
    clips[27].w = width;
    clips[27].h = height;

    clips[28].x = 0;
    clips[28].y = height * 7;
    clips[28].w = width;
    clips[28].h = height;

    clips[29].x = width;
    clips[29].y = height * 7;
    clips[29].w = width;
    clips[29].h = height;

    clips[30].x = width * 2;
    clips[30].y = height * 7;
    clips[30].w = width;
    clips[30].h = height;

    clips[31].x = width * 3;
    clips[31].y = height * 7;
    clips[31].w = width;
    clips[31].h = height;

    clips[32].x = 0;
    clips[32].y = height * 8;
    clips[32].w = width;
    clips[32].h = height;

    clips[33].x = width;
    clips[33].y = height * 8;
    clips[33].w = width;
    clips[33].h = height;

    clips[34].x = width;
    clips[34].y = height * 8;
    clips[34].w = width;
    clips[34].h = height;

    clips[35].x = width * 2;
    clips[35].y = height * 8;
    clips[35].w = width;
    clips[35].h = height;

    clips[36].x = width * 3;
    clips[36].y = height * 8;
    clips[36].w = width;
    clips[36].h = height;

    clips[37].x = 0;
    clips[37].y = height * 9;
    clips[37].w = width;
    clips[37].h = height;

    clips[38].x = width;
    clips[38].y = height * 9;
    clips[38].w = width;
    clips[38].h = height;

    clips[39].x = width * 2;
    clips[39].y = height * 9;
    clips[39].w = width;
    clips[39].h = height;

    clips[40].x = width * 3;
    clips[40].y = height * 9;
    clips[40].w = width;
    clips[40].h = height;

    clips[41].x = 0;
    clips[41].y = height * 10;
    clips[41].w = width;
    clips[41].h = height;

    clips[42].x = width;
    clips[42].y = height * 10;
    clips[42].w = width;
    clips[42].h = height;

    clips[43].x = width * 2;
    clips[43].y = height * 10;
    clips[43].w = width;
    clips[43].h = height;

    clips[44].x = width * 3;
    clips[44].y = height * 10;
    clips[44].w = width;
    clips[44].h = height;
}

SDL_Rect* Ghost::get_clip()
{
    set_anim();

    if (xVel > 0)
    {
        curr_clip = 0 + color + curr_anim;
        last_clip = 0 + color + curr_anim;
    }
    else if (xVel < 0)
    {
        curr_clip = 1 + color + curr_anim;
        last_clip = 1 + color + curr_anim;
    }
    else if (yVel > 0)
    {
        curr_clip = 2 + color + curr_anim;
        last_clip = 2 + color + curr_anim;
    }
    else if (yVel < 0)
    {
        curr_clip = 3 + color + curr_anim;
        last_clip = 3 + color + curr_anim;
    }
    else if (xVel == 0 && yVel == 0)
    {
        curr_clip = last_clip;
    }

<<<<<<< HEAD
    // fixes a bug where the last image of a just eaten ghosts reappears before it's sent to the 'jail'
=======
>>>>>>> 9ee030802e80d466304013ed104b0372c5e1b78d
    if (dead && weak)
    {
        curr_clip = 43;
    }
    else if (dead)
    {
        curr_clip += dead_offset - curr_anim;
    }
    else if (weak)
    {
        set_weakAnim();
        curr_clip = 37 + curr_anim + weak_anim;
    }

    clip_ptr = &clips[curr_clip];
    return clip_ptr;
}

void Ghost::change_direction()
{
    xVel = 0;
    yVel = 0;

    if (rand() % 2 > 0)
    {
        if (rand() % 2 > 0)
        {
            xVel = 2;
        }
        else xVel = -2;
    }
    else
    {
        if (rand() % 2 > 0)
        {
            yVel = 2;
        }
        else yVel = -2;
    }
}

void Ghost::phone_home()
{
    set_deadStage();

<<<<<<< HEAD
=======

>>>>>>> 9ee030802e80d466304013ed104b0372c5e1b78d
    if (dead_stage == 2) box.y -= 1;
}

void Ghost::set_deadStage()
{
    if (dead_stage == 0)
    {
        box.x = 268;
        box.y = 360;

        weak = false;
        eaten = false;
        dead_stage = 1;
        dead_timer.start();
    }
    else if (dead_timer.get_ticks() > 6000)
    {
        dead_timer.reset();
        dead_stage = 2;
    }
    else if (box.y == homeY)
    {
        dead = false;
        dead_stage = 0;
    }
}

void Ghost::attack(const std::vector<SDL_Rect*> &map, Player &player)
{
    if (att_timer.get_ticks() > 30000)
    {
        att_timer.start();
        wander(map);
    }
    else if (att_timer.get_ticks() > 10000)
    {
        set_attVel(player);
        att_move(map);
    }
    else wander(map);
}

void Ghost::set_attVel(Player &player)
{
    if (player.getX() > box.x)
    {
        if(player.getY() > box.y)
        {
            xVel = 2;
            yVel = 2;
        }
        else
        {
            xVel = 2;
            yVel = -2;
        }
    }
    else if (player.getY() > box.y)
    {
        xVel = -2;
        yVel = 2;
    }
    else
    {
        xVel = -2;
        yVel = -2;
    }
}

void Ghost::wander(const std::vector<SDL_Rect*> &map)
{
    if (xVel != 0)
    {
        box.x += xVel;

        if (box.x >= SCREEN_WIDTH - width - 12 || box.x <= 0 + 12 || check_collision(box, map) )
        {
            box.x -= xVel;
            change_direction();
        }
    }
    else if (yVel != 0)
    {
        box.y += yVel;

        if (box.y >= SCREEN_HEIGHT - height - 52|| box.y <= 0 + 68 || check_collision(box, map))
        {
            box.y -= yVel;
            change_direction();
        }
    }
    else change_direction();
}


void check_collision(const SDL_Rect &A, const Ghost &B)
{
    int leftA, leftB;
    int rightA, rightB;
    int topA, topB;
    int bottomA, bottomB;

    leftA = A.x;
    rightA = A.x + A.w;
    topA = A.y;
    bottomA = A.y + A.h;

    if (!B.dead)
    {
        leftB = B.box.x + 10;
        rightB = B.box.x + B.box.w - 10;
        topB = B.box.y + 10;
        bottomB = B.box.y + B.box.h - 10;

        if (!((bottomA <= topB) || (topA >= bottomB) || (rightA <= leftB) || (leftA >= rightB)))
        {
            if (!B.dead)
            {
                B.dead = true;
                B.eaten = true;
            }
        }
    }
}

void Ghost::check_weakTimer()
{
    if (weak_timer.get_ticks() > 8000)
    {
        weak = false;
        weak_timer.reset();
        move_timer.reset();
    }
}

void Ghost::set_anim()
{
    if (anim_counter > 20)
    {
        curr_anim = 0;
        anim_counter = 0;
    }
    else if (anim_counter > 10) curr_anim = 4;

    anim_counter += 1;
}

void Ghost::set_weakAnim()
{
    if (weak_timer.get_ticks() > 5000)
    {
        if (weak_animCntr > 20)
        {
            weak_anim = 0;
            weak_animCntr = 0;
        }
        else if (weak_animCntr > 10) weak_anim = 1;

        weak_animCntr += 1;
    }
    else
    {
        weak_animCntr = 0;
        weak_anim = 0;
    }

}

void Ghost::att_move(const std::vector<SDL_Rect*> &map)
{
    box.x += xVel;

    if (box.x >= SCREEN_WIDTH - width - 12 || box.x <= 0 + 12 || check_collision(box, map) )
    {
        box.x -= xVel;
    }

    box.y += yVel;

    if (box.y >= SCREEN_HEIGHT - height - 52|| box.y <= 0 + 68 || check_collision(box, map))
    {
        box.y -= yVel;
    }
}
