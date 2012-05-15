#ifndef BONUS_H
#define BONUS_H

#include "Object.h"

class Bonus : public Object
{
    public:
        Bonus(std::string filename);
        virtual ~Bonus();

        virtual void update();
        virtual void update(const SDL_Rect& player);

        friend void check_collision(const SDL_Rect &A, Bonus &B);

        void set_neutral(bool change) {neutral = change;}
        void set_eaten(bool change) {eaten = change;}

        bool is_eaten() const {return eaten;}
        bool is_neutral() const {return neutral;}

    protected:

    private:
        bool eaten;
        bool neutral;

        const static int width = 32;
        const static int height = 32;
};

void check_collision(const SDL_Rect &A, Bonus &B);

#endif // Bonus_H
