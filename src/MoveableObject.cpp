#include "MoveableObject.h"

MoveableObject::MoveableObject()
    :
    yVel(0),
    xVel(0),
    moving(false)
{
    //ctor
}

MoveableObject::~MoveableObject()
{
    //dtor
}

void MoveableObject::move()
{

}

void MoveableObject::update()
{

}

void MoveableObject::decelerateX()
{
    xVel = 0;
    moving = false;
}

void MoveableObject::decelerateY()
{
    yVel = 0;
    moving = false;
}
