#ifndef DOT_H
#define DOT_H

#include "Object.h"
#include <vector>


class Dot : public Object
{
    public:
        Dot(int x, int y);
        virtual ~Dot();

        virtual void update();

        friend void check_collision(const SDL_Rect &A, std::vector<Dot*> &B);

        bool is_eaten() const {return eaten;}

    protected:

    private:
        const static int width = 6;
        const static int height = 6;

        bool eaten;
};

void check_collision(const SDL_Rect &A, const std::vector<Dot*> &B);
void add_score(int x);

#endif
