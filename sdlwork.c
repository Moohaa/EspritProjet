//AHMED

//#include "defs.h"
/*
int main()
{
    SDL_Surface *ecran = NULL;
    SDL_Surface *image = NULL;
    SDL_Rect position;
    SDL_Event event;
    int continuer = 1;
    int Prev = 0, Now = 0;

    SDL_Init(SDL_INIT_VIDEO);

    ecran = SDL_SetVideoMode(640, 480, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);
    image = IMG_Load("a.png");
    position.x = ecran->w / 2 - image->w / 2;
    position.y = ecran->h / 2 - image->h / 2;
    while (continuer)
    {
        SDL_PollEvent(&event);
        switch (event.type)
        {
        case SDL_QUIT:
            continuer = 0;
            break;
        }
        Now = SDL_GetTicks();
        if (Now - Prev > 30)
        {
            position.x++;
            Prev = Now;
        }
        SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 255, 255, 255));
        SDL_BlitSurface(image, NULL, ecran, &position);
        SDL_Flip(ecran);
    }
    SDL_Quit();
    return EXIT_SUCCESS;
}
*/