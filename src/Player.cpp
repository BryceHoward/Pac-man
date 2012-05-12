#include "Player.h"

Player::Player()
    :
    curr_clip(0),
    curr_anim(0),
    last_clip(0),
    anim_timer(0),
    clip_ptr(NULL),
    w_pressed(false),
    a_pressed(false),
    s_pressed(false),
    d_pressed(false)
{
    load_sprite("Pacman Sprite Sheet1.png");
    set_clips();

    box.x = startX;
    box.y = startY;
    box.w = width;
    box.h = height;
}

Player::~Player()
{
    //dtor
}

void Player::input(SDL_Event &event)
{
    if (event.type == SDL_KEYDOWN)
    {
        switch(event.key.keysym.sym)
        {
            case SDLK_a: a_pressed = true; break;
            case SDLK_d: d_pressed = true;  break;
            case SDLK_w: w_pressed = true; break;
            case SDLK_s: s_pressed = true; break;

            case SDLK_LEFT: a_pressed = true; break;
            case SDLK_RIGHT: d_pressed = true; break;
            case SDLK_UP: w_pressed = true; break;
            case SDLK_DOWN: s_pressed = true; break;
            default: ;
        }
    }

    if (event.type == SDL_KEYUP)
    {
        switch(event.key.keysym.sym)
        {
            case SDLK_a: a_pressed = false; break;
            case SDLK_d: d_pressed = false; break;
            case SDLK_w: w_pressed = false; break;
            case SDLK_s: s_pressed = false; break;

            case SDLK_LEFT: a_pressed = false; break;
            case SDLK_RIGHT: d_pressed = false; break;
            case SDLK_UP: w_pressed = false; break;
            case SDLK_DOWN: s_pressed = false; break;

            default: ;
        }
    }
}

void Player::move(const std::vector<SDL_Rect*> &map, std::vector<Dot*> &dots)
{
    handle_input();

    box.x += xVel;

    if (box.x > SCREEN_WIDTH - width - 12 || box.x < 0 + 12 || check_collision(box, map) )
    {
        box.x -= xVel;
        xVel = 0;
    }

    box.y += yVel;

    if (box.y > SCREEN_HEIGHT - height - 52|| box.y < 0 + 68 || check_collision(box, map))
    {
        box.y -= yVel;
        yVel = 0;
    }

    if (xVel != 0 || yVel != 0)
    {
        moving = true;
        check_collision(box, dots);
    }
    else moving = false;

    teleport();
}

void Player::update()
{
    apply_surface(box.x, box.y, image, screen, get_clip());
}

void Player::set_clips()
{
    clips[0].x = width * 2;
    clips[0].y = 0;
    clips[0].w = width;
    clips[0].h = height;

    clips[1].x = 0;
    clips[1].y = 0;
    clips[1].w = width;
    clips[1].h = height;

    clips[2].x = width;
    clips[2].y = 0;
    clips[2].w = width;
    clips[2].h = height;

    clips[3].x = 0;
    clips[3].y = height;
    clips[3].w = width;
    clips[3].h = height;

    clips[4].x = width;
    clips[4].y = height;
    clips[4].w = width;
    clips[4].h = height;

    clips[5].x = 0;
    clips[5].y = height * 2;
    clips[5].w = width;
    clips[5].h = height;

    clips[6].x = width;
    clips[6].y = height * 2;
    clips[6].w = width;
    clips[6].h = height;

    clips[7].x = 0;
    clips[7].y = height * 3;
    clips[7].w = width;
    clips[7].h = height;

    clips[8].x = width;
    clips[8].y = height * 3;
    clips[8].w = width;
    clips[8].h = height;
}

void Player::set_anim()
{
    anim_timer++;

    if (anim_timer < 5)
    {
        curr_anim = 0;
    }
    else if (anim_timer < 10)
    {
        curr_anim = 1;
    }
    else if (anim_timer < 15)
    {
        curr_anim = 2;
    }
    else anim_timer = 0;
}

SDL_Rect* Player::get_clip()
{
    set_anim();

    if (xVel > 0)
    {
        curr_clip = 0 + curr_anim;
        last_clip = 0;
    }
    else if (xVel < 0)
    {
        curr_clip = 2 + curr_anim;
        last_clip = 2;
    }
    else if (yVel < 0)
    {
        curr_clip = 4 + curr_anim;
        last_clip = 4;
    }
    else if (yVel > 0)
    {
        curr_clip = 6 + curr_anim;
        last_clip = 6;
    }


    if (xVel == 0 && yVel == 0)
    {
        curr_clip = last_clip + curr_anim;
    }

    if (curr_anim == 0)
    {
        curr_clip = 0;
    }

    clip_ptr = &clips[curr_clip];

    return clip_ptr;
}

void Player::handle_input()
{
    if (a_pressed) xVel = -2;
    if (d_pressed) xVel = 2;
    if (w_pressed) yVel = -2;
    if (s_pressed) yVel = 2;
}

void Player::reset()
{
    box.x = startX;
    box.y = startY;

    xVel = 0;
    yVel = 0;

    a_pressed = false;
    w_pressed = false;
    s_pressed = false;
    d_pressed = false;
}

void Player::teleport()
{
    if (box.x == 12  && box.y == 356)
    {
        box.x = 518;
    }
    else if (box.x == 520 && box.y == 356)
    {
        box.x = 14;
    }
}
