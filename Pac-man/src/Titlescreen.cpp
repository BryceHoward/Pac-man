#include "Titlescreen.h"

Titlescreen::Titlescreen()
    :
<<<<<<< HEAD
    image(load_image("resources/images/Title.png")),
    player(load_image("resources/images/Single Pacman.png")),
    dot(load_image("resources/images/Ball thingy.png")),
    ghosts(load_image("resources/images/Ghost Sprite Sheet.png")),
=======
    image(load_image("Title.png")),
    player(load_image("Single Pacman.png")),
    dot(load_image("Ball thingy.png")),
    ghosts(load_image("Ghost Sprite Sheet.png")),
>>>>>>> a08e0b82c77ec6c3b4a4d2e9ec38054a74399abd
    play(120, 500),
    quit(350, 500),
    _chosen(false),
    anim(0)
{

}

Titlescreen::~Titlescreen()
{

}

void Titlescreen::update()
{
    apply_surface(100, 150, image, screen);

    apply_surface(180, 350, player, screen);

    if (anim > 15)
    {
        apply_surface(240, 350, ghosts, screen, &ghost_clips[0]);
        apply_surface(300, 350, ghosts, screen, &ghost_clips[2]);
        apply_surface(360, 350, ghosts, screen, &ghost_clips[4]);
        apply_surface(420, 350, ghosts, screen, &ghost_clips[6]);

        anim++;

        if (anim > 30) anim = 0;
    }
    else
    {
        apply_surface(240, 350, ghosts, screen, &ghost_clips[1]);
        apply_surface(300, 350, ghosts, screen, &ghost_clips[3]);
        apply_surface(360, 350, ghosts, screen, &ghost_clips[5]);
        apply_surface(420, 350, ghosts, screen, &ghost_clips[7]);

        anim++;
    }

    apply_surface(175, 362, dot, screen);
    apply_surface(160, 362, dot, screen);
    apply_surface(145, 362, dot, screen);
    apply_surface(130, 362, dot, screen);
    apply_surface(115, 362, dot, screen);
    apply_surface(100, 362, dot, screen);
    apply_surface(85, 362, dot, screen);
    apply_surface(70, 362, dot, screen);
    apply_surface(55, 362, dot, screen);
    apply_surface(40, 362, dot, screen);
    apply_surface(25, 362, dot, screen);
    apply_surface(10, 362, dot, screen);

    play.update();
    quit.update();
}

void Titlescreen::start(SDL_Event &event, Game &game)
{
    set_up();
    game.fpsCalcTimer.start();

    while (!_chosen)
    {
        game.fpsCapTimer.start();

        if (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                _chosen = true;
                game.quit = true;
            }

            if (play.clicked(event))
            {
                _chosen = true;
            }
            else if (quit.clicked(event))
            {
                _chosen = true;
                game.quit = true;
            }
        }

        SDL_FillRect(screen, &screen->clip_rect, SDL_MapRGB( screen->format, 0, 0, 0));
        update();

        game.updateScreen();
        game.capFPS();
        game.displayFPS();
    }

    reset();
}

void Titlescreen::set_up()
{
    play.load_messege("Play");
    quit.load_messege("Quit");

    ghost_clips[0].x = width;
    ghost_clips[0].y = 0;
    ghost_clips[0].w = width;
    ghost_clips[0].h = height;

    ghost_clips[1].x = width;
    ghost_clips[1].y = height;
    ghost_clips[1].w = width;
    ghost_clips[1].h = height;

    ghost_clips[2].x = width;
    ghost_clips[2].y = height * 2;;
    ghost_clips[2].w = width;
    ghost_clips[2].h = height;

    ghost_clips[3].x = width;
    ghost_clips[3].y = height * 3;;
    ghost_clips[3].w = width;
    ghost_clips[3].h = height;

    ghost_clips[4].x = width;
    ghost_clips[4].y = height * 4;;
    ghost_clips[4].w = width;
    ghost_clips[4].h = height;

    ghost_clips[5].x = width;
    ghost_clips[5].y = height * 5;
    ghost_clips[5].w = width;
    ghost_clips[5].h = height;

    ghost_clips[6].x = width;
    ghost_clips[6].y = height * 6;
    ghost_clips[6].w = width;
    ghost_clips[6].h = height;

    ghost_clips[7].x = width;
    ghost_clips[7].y = height * 7;
    ghost_clips[7].w = width;
    ghost_clips[7].h = height;
}
