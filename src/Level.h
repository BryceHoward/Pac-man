#ifndef LEVEL_H
#define LEVEL_H

#include <string>
#include <vector>

#include "SDL.h"
#include "SDL/SDL_ttf.h"
#include "Utility.h"
#include "Game.h"
#include "Object.h"
#include "Player.h"
#include "Ghost.h"
#include "Dot.h"
#include "PowerUp.h"
#include "Timer.h"
#include "Bonus.h"
#include "QuitMessege.h"


class Level
{
    public:
        Level(std::string filename);
        virtual ~Level();

        void update();
        void update(const SDL_Rect &player, std::vector<Ghost*> &ghosts);
        void start(SDL_Event &event, Game &game);
        bool quit() const {return _quit;}

    protected:

    private:
        bool load_files();

        void play_siren();

        void set_map();
        void set_dots();
        void set_Ldots();
        void set_ghosts();
        void set_bonuses();
        void set_deathClips();

        void update_dots();
        void update_Ldots(const SDL_Rect &player, std::vector<Ghost*> &ghosts);
        void update_Ldots();
        void update_ghosts();
        void update_lives();
        void update_bonuses(const SDL_Rect& player);
        void update_bonuses();
        void update_eatenBonuses();

        void del_dots();
        void del_Ldots();
        void del_ghosts();
        void del_bonuses();
        void del_eatenBonuses();

        void move_ghosts(const std::vector<SDL_Rect*> &map, Player &player, SDL_Event &event);

        void set_score();
        void check_score();
        void update_score();

        void reset();
        void reset_forDeath(Player& player);
        void check_loss(Player &player, const std::vector<Ghost*> &ghosts);
        void handle_win(Player &player, SDL_Event &event);
        void handle_death(Player &player, SDL_Event &event, Game &game);
        void start_deathSequence(Player &player, SDL_Event &event);

        void ready_msg();
        void gameOver_msg();
        void points_msg(int x, int y, int amount);
        void bonusPnts_msg();
        void start_delay(SDL_Event &event, int ms);
        void start_delay(SDL_Event &event, int ms, Player &player);

        void quit_loop(SDL_Event& event, Player &player, Game &game);

        void activate_bonus();

        int score;
        int highscore;
        int lastScore;
        int dots_eaten;
        int last_dots;
        int lives;
        int ghost_points;
        int level;
        int deathSeq_stage;

        bool _quit;
        bool _lost;
        bool _won;
        bool died;
        bool files_loaded;
        bool bonus_set;

        std::vector<Dot*> dots;
        std::vector<SDL_Rect*> map;
        std::vector<PowerUp*> large_dots;
        std::vector<Ghost*> ghosts;
        std::vector<Bonus*> bonuses;
        std::vector<SDL_Surface*> eatenBonuses;

        Timer delay_timer;
        Timer dotsAudio_timer;
        Timer sirenAudio_timer;
        Timer ghost_pointsTimer;
        Timer bonus_timer;
        Timer bonusMsg_timer;

        Mix_Music *intermission;

        Mix_Chunk *opening;
        Mix_Chunk *waka;
        Mix_Chunk *death;
        Mix_Chunk *eatingCherry;
        Mix_Chunk *extraLife_Audio;
        Mix_Chunk *eatingGhost;
        Mix_Chunk *siren;
        Mix_Chunk *powerPill;

        SDL_Surface *background;
        SDL_Surface *scoreImg;
        SDL_Surface *scoreNum;
        SDL_Surface *livesImg;
        SDL_Surface *messege;
        SDL_Surface *deathSequence;

        SDL_Rect death_clips[10];

        TTF_Font *msgFont;

        SDL_Color fontColor;

        QuitMessege quit_messege;
};

#endif // LEVEL_H
