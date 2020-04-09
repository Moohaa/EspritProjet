#include "enigme.h"

void afficherEnigme(Enigme enigme, SDL_Surface *screen)
{
    if (enigme.type == 1)
    {
        apply_surface(0, 0, enigme.enigme, screen, NULL);
        SDL_Flip(screen);
        return;
    }

    int a = rand() % 10 + rand() % 10 + 1;
    int b = rand() % 10 + rand() % 10 + 1;
    int c = rand() % 10 + rand() % 10 + 1;

    SDL_Surface *enigmeBackground = load_image("assets/enigmes/enigme1F.png", 0);
    SDL_Surface *question;
    SDL_Surface *question2;
    SDL_Surface *question3;

    char enigmeQuestion[30];
    char enigmeQuestion1[30];
    char enigmeQuestion2[30];
    char enigmeReponses[10] = "1  2  3  4";

    sprintf(enigmeQuestion, "Combien font %d + %d ?", enigme.a, enigme.b);
    sprintf(enigmeQuestion1, "1 : %d  | 2 : %d", a, b);
    sprintf(enigmeQuestion2, "3 : %d  | 4 : %d", c, enigme.a + enigme.b);

    question = generateFontSurface(32, enigmeQuestion, n_selected);
    question2 = generateFontSurface(32, enigmeQuestion1, n_selected);
    question3 = generateFontSurface(32, enigmeQuestion2, n_selected);
    apply_surface(350, 200, question, enigmeBackground, NULL);
    apply_surface(400, 300, question2, enigmeBackground, NULL);
    apply_surface(400, 400, question3, enigmeBackground, NULL);
    apply_surface(0, 0, enigmeBackground, screen, NULL);
    SDL_Flip(screen);
}

Enigme generateEnigme(int type)
{
    Enigme enigme;
    if (type == 0)
    {
        int a = rand() % 10 + 1;
        int b = rand() % 10 + 1;
        enigme.a = a;
        enigme.b = b;
        enigme.reponseInt = a + b;
        return enigme;
    }
    else
    {
        return loadRandomEnigmeFile();
    }
}

Enigme loadRandomEnigmeFile()
{
    Enigme enigme;
    enigme.type = 1;
    int a = rand() % 4 + 1;
    char filePath[50];
    sprintf(filePath, "assets/enigmes/%d.png", a);
    enigme.enigme = load_image(filePath, 0);
    return enigme;
}

int enigmeEventHandler(Enigme enigme, int type)
{
    int reponse = -1;
    int continueEnigme = 1;
    while (continueEnigme)
    {
        SDL_WaitEvent(&event);
        switch (event.type)
        {
        case SDL_KEYDOWN:
            switch (event.key.keysym.sym)
            {
            case (SDLK_a):
                printf("AAAAAAAAAAAAAAAAA");
                reponse = 1;
                break;
            case (SDLK_z):
                printf("ZZZZZZZZZZZZZZZZZZZZZ");
                reponse = 2;
                break;
            case (SDLK_e):
                reponse = 3;
                break;
            case (SDLK_r):
                reponse = 4;
                break;
            case (SDLK_RETURN):
                printf(" //reponse : %d / continueEnigme %d ", reponse, continueEnigme);
                continueEnigme = 0;
                return reponse;
                break;
            }
            break;
        default:
            break;
        }
    }
}

void EnigmePipeline()
{
    Enigme enigme;

    enigme = generateEnigme(1);
    afficherEnigme(enigme, screen);
    int reponse = enigmeEventHandler(enigme, 0);
    SDL_Surface *reponseSurface;
    if (reponse == 4)
    {
        reponseSurface = load_image("assets/enigmes/reponseOK.png", 0);
    }
    else
    {
        reponseSurface = load_image("assets/enigmes/reponseF.png", 0);
    }
    apply_surface(0, 0, reponseSurface, screen, NULL);
    SDL_Flip(screen);
    SDL_Delay(3000);
}
