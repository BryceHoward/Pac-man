#include "Level.h"
#include <sstream>

Level::Level(std::string filename)
    :
    background(load_image(filename.c_str())),
    livesImg(load_image("Single Pacman.png")),
    quit_messege("Quit Screen.png", 150, 200),
    _quit(false),
    _won(false),
    _lost(false),
    died(false),
    bonus_set(false),
    files_loaded(false),
    score(0),
    highscore(0),
    dots_eaten(0),
    lastScore(0),
    last_dots(0),
    lives(2),
    ghost_points(0),
    level(0),
    deathSeq_stage(0)
{
    dots.clear();
    ghosts.clear();
    map.clear();

    set_map();
    set_deathClips();

    dotsAudio_timer.start();
    sirenAudio_timer.start();
    bonus_timer.start();
}

Level::~Level()
{
    del_dots();
    del_Ldots();
    del_ghosts();
}

void Level::update()
{
    apply_surface(0, 0, background, screen );
    update_score();
    update_dots();
    update_Ldots();
    update_ghosts();
    update_lives();
    update_eatenBonuses();
}

void Level::update(const SDL_Rect &player, std::vector<Ghost*> &ghosts)
{
    apply_surface(0, 0, background, screen );
    update_score();
    update_dots();
    update_Ldots(player, ghosts);
    update_ghosts();
    update_lives();
    update_bonuses(player);
    update_eatenBonuses();
    activate_bonus();
    play_siren();
}

void Level::set_map()
{
    map.push_back(new SDL_Rect{46,102,62,62});
    map.push_back(new SDL_Rect{460,102,62,60});

    map.push_back(new SDL_Rect{140,102,96,62});
    map.push_back(new SDL_Rect{332,102,96,62});

    map.push_back(new SDL_Rect{268,64,32,100});

    map.push_back(new SDL_Rect{44,196,64,32});
    map.push_back(new SDL_Rect{460,196,62,32});

    map.push_back(new SDL_Rect{140,196,32,160});
    map.push_back(new SDL_Rect{172,260,64,32});

    map.push_back(new SDL_Rect{204,196,160,32});
    map.push_back(new SDL_Rect{268,228,32,64});

    map.push_back(new SDL_Rect{396,196,32,160});
    map.push_back(new SDL_Rect{332,260,64,32});

    map.push_back(new SDL_Rect{12,260,96,96});
    map.push_back(new SDL_Rect{12,388,96,96});
    map.push_back(new SDL_Rect{460,260,96,96});
    map.push_back(new SDL_Rect{460,388,96,96});

    map.push_back(new SDL_Rect{204,324,160,96});

    map.push_back(new SDL_Rect{140,388,32,96});
    map.push_back(new SDL_Rect{396,388,32,96});

    map.push_back(new SDL_Rect{204,452,160,32});
    map.push_back(new SDL_Rect{268,484,32,64});

    map.push_back(new SDL_Rect{140,516,96,32});
    map.push_back(new SDL_Rect{332,516,96,32});

    map.push_back(new SDL_Rect{46,516,62,32});
    map.push_back(new SDL_Rect{76,546,32,64});

    map.push_back(new SDL_Rect{460,516,62,32});
    map.push_back(new SDL_Rect{460,548,32,64});

    map.push_back(new SDL_Rect{12,580,30,32});
    map.push_back(new SDL_Rect{524,580,32,32});

    map.push_back(new SDL_Rect{46,644,190,30});
    map.push_back(new SDL_Rect{140,580,32,62});

    map.push_back(new SDL_Rect{204,580,160,32});
    map.push_back(new SDL_Rect{268,612,32,62});

    map.push_back(new SDL_Rect{332,644,190,30});
    map.push_back(new SDL_Rect{396,580,32,64});
}

void Level::start(SDL_Event &event, Game& game)
{
    reset();

    if (!files_loaded)
    {
        if (!load_files())
        {
            _quit = true;
            return;
        }
        else files_loaded = true;
    }

    Player player;

    update();
    player.update();

    ready_msg();
    game.updateScreen();

    Mix_PlayChannel(-1, opening, 0);
    start_delay(event, 5000);

    game.fpsCalcTimer.start();

    while (!_quit)
    {
        game.fpsCapTimer.start();

        while (SDL_PollEvent(&event))
        {
            player.input(event);

            if (event.type == SDL_QUIT)
            {
                quit_loop(event, player, game);
            }
        }

        player.move(map, dots);
        move_ghosts(map, player, event);
        check_loss(player, ghosts);

        update(player.getRect(), ghosts);
        player.update();

        game.updateScreen();
        game.capFPS();
        game.displayFPS();

        handle_death(player, event, game);
        handle_win(player, event);
    }
}

void Level::set_dots()
{
    del_dots();

    // ---------Fist Row-------
    dots.push_back(new Dot(24,80));
    dots.push_back(new Dot(40,80));
    dots.push_back(new Dot(56,80));
    dots.push_back(new Dot(72,80));
    dots.push_back(new Dot(88,80));
    dots.push_back(new Dot(104,80));
    dots.push_back(new Dot(120,80));
    dots.push_back(new Dot(136,80));
    dots.push_back(new Dot(152,80));
    dots.push_back(new Dot(168,80));
    dots.push_back(new Dot(182,80));
    dots.push_back(new Dot(198,80));
    dots.push_back(new Dot(214,80));
    dots.push_back(new Dot(230,80));
    dots.push_back(new Dot(248,80));


    dots.push_back(new Dot(312,80));
    dots.push_back(new Dot(328,80));
    dots.push_back(new Dot(344,80));
    dots.push_back(new Dot(360,80));
    dots.push_back(new Dot(376,80));
    dots.push_back(new Dot(392,80));
    dots.push_back(new Dot(408,80));
    dots.push_back(new Dot(424,80));
    dots.push_back(new Dot(440,80));
    dots.push_back(new Dot(456,80));
    dots.push_back(new Dot(472,80));
    dots.push_back(new Dot(488,80));
    dots.push_back(new Dot(504,80));
    dots.push_back(new Dot(520,80));
    dots.push_back(new Dot(536,80));


    // ---------Second Row-------
    dots.push_back(new Dot(24,96));
    dots.push_back(new Dot(248,96));
    dots.push_back(new Dot(312,96));
    dots.push_back(new Dot(536,96));

    //----------Third Row----------
    dots.push_back(new Dot(248,112));
    dots.push_back(new Dot(312,112));

    //----------Fourth Row----------
    dots.push_back(new Dot(248,128));
    dots.push_back(new Dot(312,128));

    //----------Fifth Row----------
    dots.push_back(new Dot(24,144));
    dots.push_back(new Dot(248,144));
    dots.push_back(new Dot(312,144));
    dots.push_back(new Dot(536,144));

    //----------Sixth Row----------
    dots.push_back(new Dot(24,160));
    dots.push_back(new Dot(248,160));
    dots.push_back(new Dot(312,160));
    dots.push_back(new Dot(536,160));

    //----------Seventh Row----------
    dots.push_back(new Dot(24,176));
    dots.push_back(new Dot(40,176));
    dots.push_back(new Dot(56,176));
    dots.push_back(new Dot(72,176));
    dots.push_back(new Dot(88,176));
    dots.push_back(new Dot(104,176));
    dots.push_back(new Dot(136,176));
    dots.push_back(new Dot(152,176));
    dots.push_back(new Dot(168,176));
    dots.push_back(new Dot(184,176));
    dots.push_back(new Dot(200,176));
    dots.push_back(new Dot(216,176));
    dots.push_back(new Dot(232,176));
    dots.push_back(new Dot(248,176));
    dots.push_back(new Dot(264,176));
    dots.push_back(new Dot(280,176));
    dots.push_back(new Dot(296,176));
    dots.push_back(new Dot(312,176));
    dots.push_back(new Dot(328,176));
    dots.push_back(new Dot(344,176));
    dots.push_back(new Dot(360,176));
    dots.push_back(new Dot(376,176));
    dots.push_back(new Dot(392,176));
    dots.push_back(new Dot(408,176));
    dots.push_back(new Dot(424,176));
    dots.push_back(new Dot(456,176));
    dots.push_back(new Dot(472,176));
    dots.push_back(new Dot(488,176));
    dots.push_back(new Dot(504,176));
    dots.push_back(new Dot(520,176));
    dots.push_back(new Dot(536,176));

     //----------Eigth Row----------
    dots.push_back(new Dot(24,192));
    dots.push_back(new Dot(184,192));
    dots.push_back(new Dot(376,192));
    dots.push_back(new Dot(536,192));

    //----------Nineth Row----------
    dots.push_back(new Dot(24,208));
    dots.push_back(new Dot(184,208));
    dots.push_back(new Dot(376,208));
    dots.push_back(new Dot(536,208));

    //----------Tenth Row----------
    dots.push_back(new Dot(24,224));
    dots.push_back(new Dot(184,224));
    dots.push_back(new Dot(376,224));
    dots.push_back(new Dot(536,224));

    //----------Eleventh Row----------
    dots.push_back(new Dot(24,240));
    dots.push_back(new Dot(40,240));
    dots.push_back(new Dot(56,240));
    dots.push_back(new Dot(72,240));
    dots.push_back(new Dot(88,240));
    dots.push_back(new Dot(104,240));
    dots.push_back(new Dot(184,240));
    dots.push_back(new Dot(200,240));
    dots.push_back(new Dot(216,240));
    dots.push_back(new Dot(232,240));
    dots.push_back(new Dot(248,240));
    dots.push_back(new Dot(312,240));
    dots.push_back(new Dot(328,240));
    dots.push_back(new Dot(344,240));
    dots.push_back(new Dot(360,240));
    dots.push_back(new Dot(376,240));
    dots.push_back(new Dot(456,240));
    dots.push_back(new Dot(472,240));
    dots.push_back(new Dot(488,240));
    dots.push_back(new Dot(504,240));
    dots.push_back(new Dot(520,240));
    dots.push_back(new Dot(536,240));

    // ---------Twelfth Row-------
    dots.push_back(new Dot(24,496));
    dots.push_back(new Dot(40,496));
    dots.push_back(new Dot(56,496));
    dots.push_back(new Dot(72,496));
    dots.push_back(new Dot(88,496));
    dots.push_back(new Dot(104,496));
    dots.push_back(new Dot(120,496));
    dots.push_back(new Dot(136,496));
    dots.push_back(new Dot(152,496));
    dots.push_back(new Dot(168,496));
    dots.push_back(new Dot(184,496));
    dots.push_back(new Dot(200,496));
    dots.push_back(new Dot(216,496));
    dots.push_back(new Dot(232,496));
    dots.push_back(new Dot(248,496));
    dots.push_back(new Dot(312,496));
    dots.push_back(new Dot(328,496));
    dots.push_back(new Dot(344,496));
    dots.push_back(new Dot(360,496));
    dots.push_back(new Dot(376,496));
    dots.push_back(new Dot(392,496));
    dots.push_back(new Dot(408,496));
    dots.push_back(new Dot(424,496));
    dots.push_back(new Dot(440,496));
    dots.push_back(new Dot(456,496));
    dots.push_back(new Dot(472,496));
    dots.push_back(new Dot(488,496));
    dots.push_back(new Dot(504,496));
    dots.push_back(new Dot(520,496));
    dots.push_back(new Dot(536,496));

    //--------Thirteenth Row--------
    dots.push_back(new Dot(24,512));
    dots.push_back(new Dot(248,512));
    dots.push_back(new Dot(312,512));
    dots.push_back(new Dot(536,512));

    //--------Fourteenth Row--------
    dots.push_back(new Dot(24,528));
    dots.push_back(new Dot(248,528));
    dots.push_back(new Dot(312,528));
    dots.push_back(new Dot(536,528));

    //-------=-Fifteenth Row---------
    dots.push_back(new Dot(24,544));
    dots.push_back(new Dot(248,544));
    dots.push_back(new Dot(312,544));
    dots.push_back(new Dot(536,544));

    //---------Sixteenth Row--------
    dots.push_back(new Dot(40,560));
    dots.push_back(new Dot(56,560));

    dots.push_back(new Dot(136,560));
    dots.push_back(new Dot(152,560));
    dots.push_back(new Dot(168,560));
    dots.push_back(new Dot(184,560));
    dots.push_back(new Dot(200,560));
    dots.push_back(new Dot(216,560));
    dots.push_back(new Dot(232,560));
    dots.push_back(new Dot(248,560));
    dots.push_back(new Dot(264,560));
    dots.push_back(new Dot(296,560));
    dots.push_back(new Dot(312,560));
    dots.push_back(new Dot(328,560));
    dots.push_back(new Dot(344,560));
    dots.push_back(new Dot(360,560));
    dots.push_back(new Dot(376,560));
    dots.push_back(new Dot(392,560));
    dots.push_back(new Dot(408,560));
    dots.push_back(new Dot(424,560));

    dots.push_back(new Dot(504,560));
    dots.push_back(new Dot(520,560));

    //--------Seventeenth Row--------
    dots.push_back(new Dot(56,576));
    dots.push_back(new Dot(184,576));
    dots.push_back(new Dot(376,576));
    dots.push_back(new Dot(504,576));

    //--------Eighteenth Row--------
    dots.push_back(new Dot(56,592));
    dots.push_back(new Dot(184,592));
    dots.push_back(new Dot(376,592));
    dots.push_back(new Dot(504,592));

    //--------Nineteenth Row--------
    dots.push_back(new Dot(56,608));
    dots.push_back(new Dot(184,608));
    dots.push_back(new Dot(376,608));
    dots.push_back(new Dot(504,608));

    // ---------Twentieth Row-------
    dots.push_back(new Dot(24,624));
    dots.push_back(new Dot(40,624));
    dots.push_back(new Dot(56,624));
    dots.push_back(new Dot(72,624));
    dots.push_back(new Dot(88,624));
    dots.push_back(new Dot(104,624));

    dots.push_back(new Dot(184,624));
    dots.push_back(new Dot(200,624));
    dots.push_back(new Dot(216,624));
    dots.push_back(new Dot(232,624));
    dots.push_back(new Dot(248,624));

    dots.push_back(new Dot(312,624));
    dots.push_back(new Dot(328,624));
    dots.push_back(new Dot(344,624));
    dots.push_back(new Dot(360,624));
    dots.push_back(new Dot(376,624));

    dots.push_back(new Dot(456,624));
    dots.push_back(new Dot(472,624));
    dots.push_back(new Dot(488,624));
    dots.push_back(new Dot(504,624));
    dots.push_back(new Dot(520,624));
    dots.push_back(new Dot(536,624));

    //--------Twenty-First Row--------
    dots.push_back(new Dot(24,640));
    dots.push_back(new Dot(248,640));
    dots.push_back(new Dot(312,640));
    dots.push_back(new Dot(536,640));

    //--------Twenty-Second Row--------
    dots.push_back(new Dot(24,656));
    dots.push_back(new Dot(248,656));
    dots.push_back(new Dot(312,656));
    dots.push_back(new Dot(536,656));

    //--------Twenty-Third Row--------
    dots.push_back(new Dot(24,672));
    dots.push_back(new Dot(248,672));
    dots.push_back(new Dot(312,672));
    dots.push_back(new Dot(536,672));

    // --------First Column---------
    dots.push_back(new Dot(120,96));
    dots.push_back(new Dot(120,112));
    dots.push_back(new Dot(120,128));
    dots.push_back(new Dot(120,144));
    dots.push_back(new Dot(120,160));
    dots.push_back(new Dot(120,176));
    dots.push_back(new Dot(120,192));
    dots.push_back(new Dot(120,208));
    dots.push_back(new Dot(120,224));
    dots.push_back(new Dot(120,240));
    dots.push_back(new Dot(120,256));
    dots.push_back(new Dot(120,272));
    dots.push_back(new Dot(120,288));
    dots.push_back(new Dot(120,304));
    dots.push_back(new Dot(120,320));
    dots.push_back(new Dot(120,336));
    dots.push_back(new Dot(120,352));
    dots.push_back(new Dot(120,368));
    dots.push_back(new Dot(120,384));
    dots.push_back(new Dot(120,400));
    dots.push_back(new Dot(120,416));
    dots.push_back(new Dot(120,432));
    dots.push_back(new Dot(120,448));
    dots.push_back(new Dot(120,464));
    dots.push_back(new Dot(120,480));
    dots.push_back(new Dot(120,496));
    dots.push_back(new Dot(120,512));
    dots.push_back(new Dot(120,528));
    dots.push_back(new Dot(120,544));
    dots.push_back(new Dot(120,560));
    dots.push_back(new Dot(120,576));
    dots.push_back(new Dot(120,592));
    dots.push_back(new Dot(120,608));
    dots.push_back(new Dot(120,624));

    // --------Second Column---------
    dots.push_back(new Dot(440,96));
    dots.push_back(new Dot(440,112));
    dots.push_back(new Dot(440,128));
    dots.push_back(new Dot(440,144));
    dots.push_back(new Dot(440,160));
    dots.push_back(new Dot(440,176));
    dots.push_back(new Dot(440,192));
    dots.push_back(new Dot(440,208));
    dots.push_back(new Dot(440,224));
    dots.push_back(new Dot(440,240));
    dots.push_back(new Dot(440,256));
    dots.push_back(new Dot(440,272));
    dots.push_back(new Dot(440,288));
    dots.push_back(new Dot(440,304));
    dots.push_back(new Dot(440,320));
    dots.push_back(new Dot(440,336));
    dots.push_back(new Dot(440,352));
    dots.push_back(new Dot(440,368));
    dots.push_back(new Dot(440,384));
    dots.push_back(new Dot(440,400));
    dots.push_back(new Dot(440,416));

    dots.push_back(new Dot(440,432));
    dots.push_back(new Dot(440,448));
    dots.push_back(new Dot(440,464));
    dots.push_back(new Dot(440,480));
    dots.push_back(new Dot(440,496));
    dots.push_back(new Dot(440,512));
    dots.push_back(new Dot(440,528));
    dots.push_back(new Dot(440,544));
    dots.push_back(new Dot(440,560));
    dots.push_back(new Dot(440,576));
    dots.push_back(new Dot(440,592));
    dots.push_back(new Dot(440,608));
    dots.push_back(new Dot(440,624));


    // ---------Bottom Row-------
    dots.push_back(new Dot(24,688));
    dots.push_back(new Dot(40,688));
    dots.push_back(new Dot(56,688));
    dots.push_back(new Dot(72,688));
    dots.push_back(new Dot(88,688));
    dots.push_back(new Dot(104,688));
    dots.push_back(new Dot(120,688));
    dots.push_back(new Dot(136,688));
    dots.push_back(new Dot(152,688));
    dots.push_back(new Dot(168,688));
    dots.push_back(new Dot(184,688));
    dots.push_back(new Dot(200,688));
    dots.push_back(new Dot(216,688));
    dots.push_back(new Dot(232,688));
    dots.push_back(new Dot(248,688));
    dots.push_back(new Dot(264,688));
    dots.push_back(new Dot(280,688));
    dots.push_back(new Dot(296,688));
    dots.push_back(new Dot(312,688));
    dots.push_back(new Dot(328,688));
    dots.push_back(new Dot(344,688));
    dots.push_back(new Dot(360,688));
    dots.push_back(new Dot(376,688));
    dots.push_back(new Dot(392,688));
    dots.push_back(new Dot(408,688));
    dots.push_back(new Dot(424,688));
    dots.push_back(new Dot(440,688));
    dots.push_back(new Dot(456,688));
    dots.push_back(new Dot(472,688));
    dots.push_back(new Dot(488,688));
    dots.push_back(new Dot(504,688));
    dots.push_back(new Dot(520,688));
    dots.push_back(new Dot(536,688));

}

void Level::update_dots()
{
    for ( int x = 0; x < dots.size(); x++)
    {
        dots[x]->update();
    }
}

void Level::set_score()
{
    score = 0;

    for (int x = 0; x < dots.size(); x++)
    {
        if (dots[x]->is_eaten())
        {
            score += 10;
            dots_eaten++;
        }
    }

    score += lastScore;

    if (dots_eaten > last_dots)
    {
        last_dots = dots_eaten;

        if (dotsAudio_timer.get_ticks() > 500)
        {
            Mix_PlayChannel(-1, waka, 0);
            dotsAudio_timer.start();
        }
    }

    if (dots_eaten == dots.size())
    {
        _won = true;
        dots_eaten = 0;
        lastScore = score;
    }
    else dots_eaten = 0;

    if (score > highscore) highscore = score;
}

void Level::update_score()
{
    set_score();

    msgFont = TTF_OpenFont("BitNano.ttf", 35);
    fontColor = {255,255,255};

    std::stringstream caption;

    caption << "Score:";
    scoreImg = TTF_RenderText_Solid(msgFont, caption.str().c_str(), fontColor);

    caption.str("");

    caption << score;
    scoreNum = TTF_RenderText_Solid(msgFont, caption.str().c_str(), fontColor);

    apply_surface((SCREEN_WIDTH / 4) - (scoreImg->w / 2), 0, scoreImg, screen);
    apply_surface((SCREEN_WIDTH / 4) - (scoreNum->w / 2), 25, scoreNum, screen);

    caption.str("");
    SDL_FreeSurface(scoreImg);
    SDL_FreeSurface(scoreNum);

    /////////////////---------------------------------------------------------

    caption << "HighScore:";
    scoreImg = TTF_RenderText_Solid(msgFont, caption.str().c_str(), fontColor);

    caption.str("");

    caption << highscore;
    scoreNum = TTF_RenderText_Solid(msgFont, caption.str().c_str(), fontColor);

    apply_surface((SCREEN_WIDTH / 4) * 3 - (scoreImg->w / 2), 0, scoreImg, screen);
    apply_surface((SCREEN_WIDTH / 4) * 3 - (scoreNum->w / 2), 25, scoreNum, screen);

    SDL_FreeSurface(scoreImg);
    SDL_FreeSurface(scoreNum);
    TTF_CloseFont(msgFont);
}

void Level::set_Ldots()
{
    del_Ldots();

    large_dots.push_back(new PowerUp(18, 114));
    large_dots.push_back(new PowerUp(530, 114));
    large_dots.push_back(new PowerUp(18, 554));
    large_dots.push_back(new PowerUp(530, 554));
}

void Level::update_Ldots(const SDL_Rect& player, std::vector<Ghost*> &ghosts)
{
    for (int x = 0; x < large_dots.size(); x++)
    {
        large_dots[x]->update(player, ghosts);

        if (large_dots[x]->if_eaten())
        {
            Mix_PlayChannel(-1, powerPill, 0);
            ghost_pointsTimer.start();

            lastScore += 50;
        }
    }

    if (ghost_pointsTimer.get_ticks() > 8000)
    {
        ghost_pointsTimer.reset();
        ghost_points = 0;
    }
}

void Level::update_Ldots()
{
    for (int x = 0; x < large_dots.size(); x++)
    {
        large_dots[x]->update();
    }
}

void Level::move_ghosts(const std::vector<SDL_Rect*> &map, Player &player, SDL_Event &event)
{
    for (int x = 0; x < ghosts.size(); x++)
    {
        ghosts[x]->move(map, player);

        if (ghosts[x]->is_eaten())
        {
            ghost_points == 0 ? ghost_points = 200 : ghost_points *= 2;

            lastScore += ghost_points;

            ghosts[x]->set_dead(true);

            Mix_PlayChannel(-1, eatingGhost, 0);

            apply_surface(0, 0, background, screen );
            update_score();
            update_dots();
            update_Ldots();
            update_lives();
            play_siren();

            points_msg(player.getX(), player.getY(), ghost_points);
            SDL_Flip(screen);

            start_delay(event, 500, player);
        }
    }
}

void Level::update_ghosts()
{
    for (int x = 0; x < ghosts.size(); x++)
    {
        ghosts[x]->update();
    }
}

void Level::set_ghosts()
{
    del_ghosts();

    ghosts.push_back(new Ghost(0, true));
    ghosts.push_back(new Ghost(1, true));
    ghosts.push_back(new Ghost(2, false));
    ghosts.push_back(new Ghost(3, false));
}

void Level::del_dots()
{
    for (int x = 0; x < dots.size(); x++)
    {
        delete dots[x];
    }

    dots.clear();
}

void Level::del_Ldots()
{
    for (int x = 0; x < large_dots.size(); x++)
    {
        delete large_dots[x];
    }

    large_dots.clear();
}

void Level::del_ghosts()
{
    for (int x = 0; x < ghosts.size(); x++)
    {
        delete ghosts[x];
    }

    ghosts.clear();
}

void Level::reset()
{
    set_dots();
    set_Ldots();
    set_ghosts();
    set_bonuses();
    del_eatenBonuses();
    bonus_timer.start();

    _won = false;
    _lost = false;
    _quit = false;
    died = false;

    lives = 2;
    last_dots = 0;
    score = 0;
    lastScore = 0;
    level = 0;
}

void Level::reset_forDeath(Player& player)
{
    player.reset();
    set_ghosts();
    set_bonuses();
    bonus_timer.start();


    died = false;
    last_dots = 0;
}

void Level::check_loss(Player &player, const std::vector<Ghost*> &ghosts)
{
    for (int x = 0; x < ghosts.size(); x++)
    {
        if (!ghosts[x]->is_dead() && !ghosts[x]->is_weak())
        {
            if (check_collision(player.getRect(), ghosts[x]->getRect()))
            {
                lives--;
                died = true;

                break;
            }
        }
    }
}

void Level::update_lives()
{
    for (int x = 0, i = 0; x < lives; x++, i += 15)
    {
        apply_surface(10 + (x * 20 + i), 720, livesImg, screen);
    }
}

void Level::handle_death(Player &player, SDL_Event &event, Game &game)
{
    if (died)
    {
        if (lives < 0)
        {
            Mix_PlayChannel(-1, death, 0);
            start_deathSequence(player, event);

            gameOver_msg();
            SDL_Flip(screen);
            start_delay(event, 3000);

            reset();
            player.reset();

            update();
            player.update();
            ready_msg();

            game.updateScreen();
            game.capFPS();
            game.displayFPS();

            SDL_Flip(screen);
            Mix_PlayChannel(-1, opening, 0);
            start_delay(event, 5000);
        }
        else
        {
            Mix_PlayChannel(-1, death, 0);
            start_deathSequence(player, event);

            reset_forDeath(player);

            update();
            player.update();
            ready_msg();

            game.updateScreen();
            game.capFPS();
            game.displayFPS();

            SDL_Flip(screen);
            start_delay(event, 3000);
        }
    }
}

void Level::ready_msg()
{
    msgFont = TTF_OpenFont("BitNano.ttf", 45);
    fontColor = {255,255,255};

    std::stringstream caption;

    caption << "Ready!";
    messege = TTF_RenderText_Solid(msgFont, caption.str().c_str(), fontColor);

    apply_surface((SCREEN_WIDTH / 2) - (messege->w / 2), 410, messege, screen);

    SDL_FreeSurface(messege);
    TTF_CloseFont(msgFont);
}

void Level::gameOver_msg()
{
    msgFont = TTF_OpenFont("BitNano.ttf", 50);
    fontColor = {237,28,36};

    std::stringstream caption;

    caption << "Game Over";
    messege = TTF_RenderText_Solid(msgFont, caption.str().c_str(), fontColor);

    apply_surface((SCREEN_WIDTH / 2) - (messege->w / 2), 410, messege, screen);

    SDL_FreeSurface(messege);
    TTF_CloseFont(msgFont);
}

void Level::start_delay(SDL_Event &event, int ms)
{
    delay_timer.start();

    while (delay_timer.get_ticks() < ms && !_quit)
    {
        if (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                _quit = true;
            }
        }
    }
}

void Level::start_delay(SDL_Event &event, int ms, Player &player)
{
    delay_timer.start();

    while (delay_timer.get_ticks() < ms && !_quit)
    {
        if (SDL_PollEvent(&event))
        {
            player.input(event);

            if (event.type == SDL_QUIT)
            {
                _quit = true;
            }
        }
    }
}

void Level::handle_win(Player& player, SDL_Event &event)
{
    if (_won)
    {
        player.reset();
        set_ghosts();
        set_dots();
        set_Ldots();
        set_bonuses();

        update();
        player.update();
        ready_msg();

        SDL_Flip(screen);
        start_delay(event, 3000);

        bonus_timer.start();
        _won = false;
        last_dots = 0;
        level++;
    }
}

bool Level::load_files()
{
    intermission = Mix_LoadMUS("Intermission.wav");

    opening = Mix_LoadWAV("Opening.wav");
    waka = Mix_LoadWAV("Waka.wav");
    death = Mix_LoadWAV("Dying.wav");
    eatingCherry = Mix_LoadWAV("Eat Cherry.wav");
    extraLife_Audio = Mix_LoadWAV("Extra Life.wav");
    eatingGhost = Mix_LoadWAV("Eat Ghost.wav");
    siren = Mix_LoadWAV("Siren.wav");
    powerPill = Mix_LoadWAV("Power Pill.wav");

    if (waka == NULL || opening == NULL || death == NULL || eatingCherry == NULL || powerPill == NULL ||
        extraLife_Audio == NULL || eatingGhost == NULL || siren == NULL || intermission == NULL)
    {
        return false;
    }

    msgFont = TTF_OpenFont("BitNano.ttf", 35);

    deathSequence = load_image("Pacman Death Sequence.png");

    if (msgFont == NULL || deathSequence == NULL)
    {
        return false;
    }

    quit_messege.load_buttons("Yes", "No");

    return true;
}

void Level::play_siren()
{
    if (sirenAudio_timer.get_ticks() > 1600)
    {
        Mix_PlayChannel(-1, siren, 0);
        sirenAudio_timer.start();
    }
}

void Level::points_msg(int x, int y, int amount)
{
    msgFont = TTF_OpenFont("BitNano.ttf", 30);
    fontColor = {0,236,236};

    std::stringstream caption;

    caption << amount;
    messege = TTF_RenderText_Solid(msgFont, caption.str().c_str(), fontColor);

    apply_surface(x, y, messege, screen);

    SDL_FreeSurface(messege);
    TTF_CloseFont(msgFont);
}

void Level::update_bonuses(const SDL_Rect& player)
{
    for (int x = 0; x < bonuses.size(); x++)
    {
        bonuses[x]->update(player);

        if (bonuses[x]->is_eaten())
        {
            Mix_PlayChannel(-1, eatingCherry, 0);
            bonusMsg_timer.start();
            lastScore += level * 100 + 100;

            eatenBonuses.push_back(SDL_ConvertSurface(bonuses[x]->getImg(), bonuses[x]->getImg()->format, bonuses[x]->getImg()->flags));
        }
    }

    bonusPnts_msg();
}

void Level::update_bonuses()
{
    for (int x = 0; x < bonuses.size(); x++)
    {
        bonuses[x]->update();
    }
}

void Level::set_bonuses()
{
    del_bonuses();

    bonuses.push_back(new Bonus("Cherry.png"));
    bonuses.push_back(new Bonus("Strawberry.png"));
    bonuses.push_back(new Bonus("Apple.png"));
    bonuses.push_back(new Bonus("Orange.png"));
}

void Level::del_bonuses()
{
    for (int x = 0; x < bonuses.size(); x++)
    {
        delete bonuses[x];
    }

    bonuses.clear();
}

void Level::activate_bonus()
{
    if (bonus_timer.get_ticks() > 25000)
    {
        for (int x = 0; x < bonuses.size(); x++)
        {
            bonuses[x]->set_neutral(true);
            bonuses[x]->set_eaten(false);
            bonus_set = false;
        }

        bonus_timer.start();
    }
    else if (bonus_timer.get_ticks() > 15000 && !bonus_set)
    {
        if (level < 4)
        {
            bonuses[level]->set_neutral(false);
        }
        else if (level > 3)
        {
            int x = rand() % 4;

            switch (x)
            {
                case 0: bonuses[0]->set_neutral(false); break;
                case 1: bonuses[1]->set_neutral(false); break;
                case 2: bonuses[2]->set_neutral(false); break;
                case 3: bonuses[3]->set_neutral(false); break;
                default: break;
            }
        }

        bonus_set = true;
    }
}

void Level::bonusPnts_msg()
{
    if (bonusMsg_timer.is_started())
    {
        points_msg(270, 420, level * 100 + 100);

        if (bonusMsg_timer.get_ticks() > 1500)
        {
            bonusMsg_timer.reset();
        }
    }
}

void Level::start_deathSequence(Player &player, SDL_Event &event)
{
    while (deathSeq_stage < 10 )
    {
        apply_surface(0, 0, background, screen );
        update_dots();
        update_score();
        update_Ldots();
        update_lives();
        if (deathSeq_stage < 2) update_ghosts();


        apply_surface(player.getX(), player.getY(), deathSequence, screen, &death_clips[deathSeq_stage]);

        SDL_Flip(screen);
        start_delay(event, 150);

        deathSeq_stage++;
    }

    start_delay(event, 1000);

    deathSeq_stage = 0;
}

void Level::set_deathClips()
{
    death_clips[0].x = 0;
    death_clips[0].y = 0;
    death_clips[0].w = 32;
    death_clips[0].h = 32;

    death_clips[1].x = 0;
    death_clips[1].y = 32;
    death_clips[1].w = 32;
    death_clips[1].h = 32;

    death_clips[2].x = 0;
    death_clips[2].y = 32 * 1;
    death_clips[2].w = 32;
    death_clips[2].h = 32;

    death_clips[3].x = 0;
    death_clips[3].y = 32 * 2;
    death_clips[3].w = 32;
    death_clips[3].h = 32;

    death_clips[4].x = 0;
    death_clips[4].y = 32 * 3;
    death_clips[4].w = 32;
    death_clips[4].h = 32;

    death_clips[5].x = 0;
    death_clips[5].y = 32 * 4;
    death_clips[5].w = 32;
    death_clips[5].h = 32;

    death_clips[6].x = 0;
    death_clips[6].y = 32 * 5;
    death_clips[6].w = 32;
    death_clips[6].h = 32;

    death_clips[7].x = 0;
    death_clips[7].y = 32 * 6;
    death_clips[7].w = 32;
    death_clips[7].h = 32;

    death_clips[8].x = 0;
    death_clips[8].y = 32 * 7;
    death_clips[8].w = 32;
    death_clips[8].h = 32;

    death_clips[9].x = 0;
    death_clips[9].y = 32 * 8;
    death_clips[9].w = 32;
    death_clips[9].h = 32;
}

void Level::quit_loop(SDL_Event &event, Player &player, Game &game)
{
    while (!quit_messege.chosen())
    {
        if (SDL_PollEvent(&event))
        {
            quit_messege.input(event);
        }

        update();
        player.update();
        quit_messege.update();

        SDL_Flip(screen);
    }

    if (quit_messege.quit())
    {
        _quit = true;
    }
    quit_messege.reset();
}

void Level::update_eatenBonuses()
{
    for (int x = 520, i = 0; i < eatenBonuses.size(); x-= 40, i++)
    {
        apply_surface(x, 720, eatenBonuses[i], screen);
    }
}

void Level::del_eatenBonuses()
{
    for (int x = 0; x < eatenBonuses.size(); x++)
    {
        delete eatenBonuses[x];
    }

    eatenBonuses.clear();
}
