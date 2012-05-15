#ifndef UTILITY_H_INCLUDED
#define UTILITY_H_INCLUDED

#include "SDL.h"
#include <string>
#include <vector>

bool check_collision(const SDL_Rect &A, const SDL_Rect &B);
bool check_collision(const SDL_Rect &A, const std::vector<SDL_Rect*> &B);

SDL_Surface *load_image(std::string filename);
void apply_surface(int x, int y, SDL_Surface* source, SDL_Surface* destination, SDL_Rect* clip = NULL);

#endif // UTILITY_H_INCLUDED
