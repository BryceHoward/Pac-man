#ifndef GHOST_H
#define GHOST_H

#include "MoveableObject.h"
#include "Player.h"

class Ghost : public MoveableObject
{
    public:
        Ghost(int ghost_color, bool is_smart);
        virtual ~Ghost();

        virtual void move(const std::vector<SDL_Rect*> &map, Player &player);
        virtual void update();

        void start_weakTimer() {weak_timer.start(); weak = true; move_timer.start();}
        void set_dead(bool change) const {dead = change;}

        bool is_dead() const {return dead;}
        bool is_weak() const {return weak;}
        bool is_eaten() const {return eaten;}

    protected:

    private:
        void set_sprite();
        void set_clips();
        void set_anim();
        void set_weakAnim();

        void wander(const std::vector<SDL_Rect*> &map);
        void change_direction();

        void phone_home();
        void set_deadStage();

        void attack(const std::vector<SDL_Rect*> &map, Player &player);
        void set_attVel(Player &player);
        void att_move(const std::vector<SDL_Rect*> &map);

        void check_weakTimer();

        friend void check_collision(const SDL_Rect& A, const Ghost &B);

        SDL_Rect clips[45];
        SDL_Rect* clip_ptr;
        SDL_Rect* get_clip();

        static const int width = 32;
        static const int height = 32;
        static const int homeX = 262;
        static const int homeY = 292;

        bool smart;
        bool weak;

        mutable bool dead;
        mutable bool eaten;

        int curr_clip;
        int last_clip;
        int curr_anim;
        int color;
        int dead_offset;
        int anim_counter;
        int weak_anim;
        int weak_animCntr;
        int dead_stage;
        int quadrant;

        Timer att_timer;
        Timer weak_timer;
        Timer dead_timer;
        Timer move_timer;
};

void check_collision(const SDL_Rect &A, const Ghost &B);

#endif // GHOST_H
