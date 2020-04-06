#include "defs.h"


int main()
{
SDL_Rect camera = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
const int FRAMES_PER_SECOND = 30/60;
const int POINT_WIDTH = 10;
const int POINT_HEIGHT = 10;
int bgX = 0;
int bgY = 0;

 while( quit == false )
    {
        fps.start();
 
        while( SDL_PollEvent( &event ) )
        {
            if( event.type == SDL_QUIT )
            {
                quit = true;
            }
        }

                bgX -= 2;

        if( bgX <= -background->w )
        {
            bgX = 0;
        }

                bgY -= 2;
if( bgY <= -background->w )
        {
            bgY = 0;
        }
  apply_surface( bgX, bgY, background, screen );
        apply_surface( bgX + background->w, bgY, background, screen );
 
        
        apply_surface( 310, 230, point, screen );

         SDL_Quit();

    return EXIT_SUCCESS;
}