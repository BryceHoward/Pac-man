#include "Object.h"

Object::Object()
{
    //ctor
}

Object::~Object()
{
    SDL_FreeSurface(image);
}

void Object::load_sprite(std::string filename)
{
    image = load_image(filename.c_str());
}

void Object::update()
{
    apply_surface(box.x, box.y, image, screen);
}

