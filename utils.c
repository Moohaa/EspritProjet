#include "utils.h"
#include "menu.h"

SDL_Surface *hello = NULL;
SDL_Surface *screen = NULL;
SDL_Surface *message = NULL;
SDL_Surface *background = NULL;
SDL_Surface *image = NULL;
SDL_Event event;
TTF_Font *font = NULL;
MenuElement menuElement;
SDL_Color color;
SDL_Rect clip[3];
int menuSelect = 0;
SDL_Surface *buttons = NULL;
const int FRAMES_PER_SECOND = 20;
//The frames per second
int frame = 0;
bool cap = true;
bool quit = false;
Uint32 start = 0;
bool running = true;
Uint32 next_time;

SDL_Surface *menu1 = NULL;
SDL_Surface *menu2 = NULL;
SDL_Surface *menu3 = NULL;

SDL_Surface *menu1Hover = NULL;
SDL_Surface *menu2Hover = NULL;
SDL_Surface *menu3Hover = NULL;

SDL_Surface *load_image(char filename[])
{
    //Temporary storage for the image that's loaded
    SDL_Surface *loadedImage = NULL;

    //The optimized image that will be used
    SDL_Surface *optimizedImage = NULL;
    //Load the image
    loadedImage = IMG_Load(filename);
    //If nothing went wrong in loading the image
    if (loadedImage != NULL)
    {
        //Create an optimized image
        optimizedImage = SDL_DisplayFormat(loadedImage);

        //Free the old image
        SDL_FreeSurface(loadedImage);
    }
    else
    {
        printf("Error loading images %s\n", SDL_GetError());
    }

    //Return the optimized image
    return optimizedImage;
}

//Free all surfaces and quit SDL
void clean_up()
{
    SDL_FreeSurface(image);
    SDL_FreeSurface(hello);
    SDL_FreeSurface(screen);
    SDL_FreeSurface(background);

    SDL_Quit();
}

bool load_files()
{
    //Load the image
    background = load_image("assets/bmp/background.bmp");
    hello = load_image("assets/bmp/hello.bmp");
    buttons = load_image("assets/png/restart.png");

    //If there was an error in loading the image
    if (background == NULL)
    {
        return false;
    }
    if (hello == NULL)
    {
        return false;
    }

    //If everything loaded fine
    return true;
}

//Initialize all SDL subsystems
//Set up the screen
//If there was an error in setting up the screen
//Set the window caption
//If everything initialized fine returns true
bool init()
{
    if (SDL_Init(SDL_INIT_EVERYTHING) == -1)
    {
        printf("SDL init error %s ", SDL_GetError());
        return false;
    }

    if ((screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_HWSURFACE | SDL_DOUBLEBUF)) == NULL)
    {
        printf("SDL video mode error %s", SDL_GetError());
        return false;
    }

    SDL_WM_SetCaption("Esprit Projet Jeu Video", "Esprit Projet Jeu Video");
    //Initialize SDL_ttf
    if (TTF_Init() == -1)
    {
        return false;
    }
    return true;
}

void apply_surface(int x, int y, SDL_Surface *source, SDL_Surface *destination, SDL_Rect *clip)
{
    //Make a temporary rectangle to hold the offsets
    SDL_Rect offset;
    //Give the offsets to the rectangle
    offset.x = x;
    offset.y = y;
    //Blit the surface
    SDL_BlitSurface(source, clip, destination, &offset);
}

SDL_Surface *generateFontSurface(char file[50], int size, char text[50], SDL_Color color)
{
    font = TTF_OpenFont("assets/ttf/ARCADECLASSIC.TTF", size);
    SDL_Surface *surfaceText = TTF_RenderText_Blended(font, text, color);
    TTF_CloseFont(font);
    return surfaceText;
}

void initBg(SDL_Surface *screen, SDL_Surface *background)
{
    apply_surface(0, 0, background, screen, NULL);
    apply_surface(320, 0, background, screen, NULL);
    apply_surface(0, 240, background, screen, NULL);
    apply_surface(320, 240, background, screen, NULL);
    apply_surface(180, 140, hello, screen, NULL);
}

Uint32 time_left(void)
{
    Uint32 now;

    now = SDL_GetTicks();
    if (next_time <= now)
        return 0;
    else
        return next_time - now;
}

void loadMenuFiles()
{
    menu1 = load_image("assets/png/new.png");
    menu2 = load_image("assets/png/settings.png");
    menu3 = load_image("assets/png/exit.png");
    menu1Hover = load_image("assets/png/new_hover.png");
    menu2Hover = load_image("assets/png/settings_hover.png");
    menu3Hover = load_image("assets/png/exit_hover.png");
}

void initMenu(int menuSelect)
{
    if (menuSelect == 0)
    {
        apply_surface((SCREEN_WIDTH) / 2, 100, menu1Hover, screen, NULL);
        apply_surface((SCREEN_WIDTH - menu2->w) / 2, 200, menu2, screen, NULL);
        apply_surface((SCREEN_WIDTH - menu3->w) / 2, 300, menu3, screen, NULL);
    }
    if (menuSelect == 1)
    {
        apply_surface((SCREEN_WIDTH - menu1->w) / 2, 100, menu1, screen, NULL);
        apply_surface((SCREEN_WIDTH - menu2Hover->w) / 2, 200, menu2Hover, screen, NULL);
        apply_surface((SCREEN_WIDTH - menu3->w) / 2, 300, menu3, screen, NULL);
    }
    if (menuSelect == 2)
    {
        apply_surface((SCREEN_WIDTH - menu1->w) / 2, 100, menu1, screen, NULL);
        apply_surface((SCREEN_WIDTH - menu2->w) / 2, 200, menu2, screen, NULL);
        apply_surface((SCREEN_WIDTH - menu3Hover->w) / 2, 300, menu3Hover, screen, NULL);
    }
}