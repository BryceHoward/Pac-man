#include "Utility.h"
#include "SDL/SDL_image.h"

SDL_Surface *load_image( std::string filename )
{
    SDL_Surface* loadedImage = NULL;

    SDL_Surface* optimizedImage = NULL;

    loadedImage = IMG_Load( filename.c_str() );

    if( loadedImage != NULL )
    {
        optimizedImage = SDL_DisplayFormat( loadedImage );

        SDL_FreeSurface( loadedImage );

        if( optimizedImage != NULL )
        {
            SDL_SetColorKey( optimizedImage, SDL_SRCCOLORKEY, SDL_MapRGB( optimizedImage->format, 0, 0xFF, 0xFF ) );
        }
    }

    return optimizedImage;
}

void apply_surface( int x, int y, SDL_Surface* source, SDL_Surface* destination, SDL_Rect* clip)
{
    SDL_Rect offset;

    offset.x = x;
    offset.y = y;

    SDL_BlitSurface( source, clip, destination, &offset );
}

bool check_collision(const SDL_Rect &A, const std::vector<SDL_Rect*> &B)
{
    int leftA, leftB;
    int rightA, rightB;
    int topA, topB;
    int bottomA, bottomB;

    leftA = A.x;
    rightA = A.x + A.w;
    topA = A.y;
    bottomA = A.y + A.h;

    for (int Bbox = 0; Bbox < B.size(); Bbox++)
    {
        leftB = B[Bbox]->x;
        rightB = B[Bbox]->x + B[Bbox]->w;
        topB = B[Bbox]->y;
        bottomB = B[Bbox]->y + B[Bbox]->h;

        if (!((bottomA <= topB) || (topA >= bottomB) || (rightA <= leftB) || (leftA >= rightB)))
        {
            return true;
        }
    }

    return false;
}

bool check_collision(const SDL_Rect &A, const SDL_Rect &B)
{
    int leftA, leftB;
    int rightA, rightB;
    int topA, topB;
    int bottomA, bottomB;

    leftA = A.x + 12;
    rightA = A.x + A.w - 24;
    topA = A.y + 12;
    bottomA = A.y + A.h - 24;


    leftB = B.x;
    rightB = B.x + B.w;
    topB = B.y;
    bottomB = B.y + B.h;

    if (!((bottomA <= topB) || (topA >= bottomB) || (rightA <= leftB) || (leftA >= rightB)))
    {
        return true;
    }

    return false;
}
