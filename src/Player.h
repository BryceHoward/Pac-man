#ifndef PLAYER_H
#define PLAYER_H

#include "MoveableObject.h"
#include "Dot.h"

class Player : public MoveableObject
{
    public:
        Player();
        virtual ~Player();

        virtual void move(const std::vector<SDL_Rect*> &map, std::vector<Dot*> &dots);
        virtual void update();

        void input(SDL_Event& even);
        void reset();
        void stop() {xVel = 0; yVel = 0;}

    protected:

    private:
        void set_sprite();
        void set_clips();
        void set_anim();
        void handle_input();
        void teleport();

        SDL_Rect clips[9];
        SDL_Rect* clip_ptr;
        SDL_Rect* get_clip();

        static const int width = 32;
        static const int height = 32;
        static const int startX = 268;
        static const int startY = 548;

        int curr_clip;
        int curr_anim;
        int last_clip;
        int anim_timer;

        bool w_pressed;
        bool a_pressed;
        bool s_pressed;
        bool d_pressed;
};

#endif // PLAYER_H
