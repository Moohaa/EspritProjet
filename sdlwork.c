SDL_INIT_TIMER	
SDL_INIT_AUDIO	
SDL_INIT_VIDEO	
SDL_INIT_HAPTIC	
SDL_INIT_EVERYTHING	
SDL_INIT_NOPARACHUTE
SDL_Init(SDL_INIT_VIDEO);


#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>

int main()
{
    if(SDL_Init(SDL_INIT_VIDEO) < 0)
    {
       printf("Error : %s",SDL_GetError()); 
       return EXIT_FAILURE;                     
    }
    SDL_Quit();
    return 0;
}


int main()
{
    SDL_Surface *ecran = NULL, *???? = NULL;
    SDL_Rect position????;
    SDL_Event event;
    int continuer = 1;
    int Prev = 0, Now = 0;

    SDL_Init(SDL_INIT_VIDEO);

    ecran = SDL_SetVideoMode(640, 480, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);
    ???? = SDL_LoadBMP("????.bmp");
    position????.x = ecran->w / 2 - ????->w / 2;
    position????.y = ecran->h / 2 - ????->h / 2;
    while (continuer)
    
    {
        SDL_PollEvent(&event); 
        switch(event.type)
        {
            case SDL_QUIT:
                continuer = 0;
                break;
        }

        Now = SDL_GetTicks();
        if (Now - Prev > 30)
        {
            position????.x++;
            Prev = Now;
        }

        SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 255, 255, 255));
        SDL_BlitSurface(????, NULL, ecran, &position????);
        SDL_Flip(ecran);
    }

    SDL_FreeSurface(????);
    SDL_Quit();

    return EXIT_SUCCESS;
}


