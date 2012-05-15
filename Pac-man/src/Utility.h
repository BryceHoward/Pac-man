#ifndef UTILITY_H_INCLUDED
#define UTILITY_H_INCLUDED

#include "SDL.h"
<<<<<<< HEAD
#include <string>
#include <vector>

bool check_collision(const SDL_Rect &A, const SDL_Rect &B);
bool check_collision(const SDL_Rect &A, const std::vector<SDL_Rect*> &B);

=======
#include "SDL/SDL_ttf.h"
#include "SDL/SDL_mixer.h"
#include <string>
#include <vector>

struct Circle
{
    int x;
    int y;
    int r;
};

bool check_collision(const SDL_Rect &A, const SDL_Rect &B);
bool check_collision(const SDL_Rect &A, SDL_Rect B[]);
bool check_collision(const SDL_Rect &A, const std::vector<SDL_Rect*> &B);

double distance( int x1, int y1, int x2, int y2 );

int get_rand(int a);

>>>>>>> a08e0b82c77ec6c3b4a4d2e9ec38054a74399abd
SDL_Surface *load_image(std::string filename);
void apply_surface(int x, int y, SDL_Surface* source, SDL_Surface* destination, SDL_Rect* clip = NULL);

#endif // UTILITY_H_INCLUDED