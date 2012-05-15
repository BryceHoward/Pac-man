#ifndef POWERUP_H
#define POWERUP_H

#include "Object.h"
#include "Timer.h"
#include "Ghost.h"
#include <vector>


class PowerUp : public Object
{
    public:
        PowerUp(int x, int y);
        virtual ~PowerUp();

        virtual void update(const SDL_Rect &player, std::vector<Ghost*> &ghosts);
        virtual void update();

        friend void check_collision(const SDL_Rect &A, const PowerUp &B);

        bool if_eaten() const {return eaten;}
        bool if_neutral() const {return neutral;}

    protected:

    private:
        void weaken_ghosts(std::vector<Ghost*> &ghosts);

        int anim_count;

        const static int width = 20;
        const static int height = 20;

        bool neutral;
        mutable bool eaten;

        Timer eaten_timer;
};

void check_collision(const SDL_Rect &A,const PowerUp &B);

#endif
