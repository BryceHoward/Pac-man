#ifndef MOVEABLEOBJECT_H
#define MOVEABLEOBJECT_H

#include "Object.h"
#include <vector>


class MoveableObject : public Object
{
    public:
        virtual ~MoveableObject();

        virtual void move();
        virtual void update();

        bool check_moving() const {return moving;}

    protected:
        MoveableObject();

        int xVel;
        int yVel;

        void decelerateX();
        void decelerateY();

        bool moving;

    private:

};

#endif // MOVEABLEOBJECT_H
