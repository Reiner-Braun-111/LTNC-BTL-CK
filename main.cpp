

#include <stdlib.h>



#define SDL_MAIN_HANDLED
// Standard C++ libraries
#include <iostream>
#include <sstream>
#include <ctime>
#include <string>

// SDL
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>

// Custom headers
#include "texture.h"
#include "constances.h"
#include "variables.h"
#include "function.h"
#include "button.h"
#include "time.h"
//#include "menu.h"


using namespace std;


 SDL_Window* gWindow = NULL;
 SDL_Renderer* gRenderer = NULL;




/*int main( int argc, char** argv )  // sdl yeu cau main loai nay
{

	//Start up SDL and create window
	if( !init() )
	{
		cout << "Failed to initialize!\n";
	}
	else
	{
		//Load media
		if( !loadMedia() )
		{
			cout << "Failed to load media!\n";
		}
		else
		{
		
			bool quit = false;

			//Event handler
			SDL_Event e;

			//While application is running
		
				
				
				while( !quit )
			{
				//MENU_render(gRenderer);
				
			    createPlayGround();

			    timeCount.start();


			    //While game is not over yet
			    while ( !gameOver && !quit && !isWinning)
                {
                    //Handle events on queue
                    while( SDL_PollEvent( &e ) != 0 )
                    {
                        //User requests quit
                        if( e.type == SDL_QUIT || e.key.keysym.sym == SDLK_ESCAPE) //
                        {
                            quit = true;
                        }


                       for (int i = 0; i < ROW_SIZE; i++)
                        {
                            for (int j = 0; j < COLUMN_SIZE; j++)
                            {
                                gButtons[i][j].handleEvent( &e );
                            }
                        }
                        isWinning = checkWinning();

                    }

                    //Clear screen
                    SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
                    SDL_RenderClear( gRenderer );

                    //Render background
                    gBackgroundTexture.render(0, 0);

                    for( int i = 0; i < ROW_SIZE; i++ )
                    {
                        for ( int j = 0; j < COLUMN_SIZE; j++ )
                        {
                            gButtons[i][j].render(i, j);
                        }
                    }

                    mineManager();
                       
    
                    timeManager();
                    

                    flagManager();	
					
                    //Update screen
                    SDL_RenderPresent( gRenderer );
                }
                playAgainManager( quit );
			}
			
		}
	}

	//Free resources and close SDL
	close();

	return 0;
}*/

int main( int argc, char* args[] )
{
	//Start up SDL and create window
	if( !init() )
	{
		cout << "Failed to initialize!\n";
	}
	else
	{
		//Load media
		if( !loadMedia() )
		{
			cout << "Failed to load media!\n";
		}
		else
		{
			//Main loop flag
			bool quit = false;

			//Event handler
			SDL_Event e;

			//While application is running
			while( !quit )
			{
			    createPlayGround();
			    timeCount.start();

			    //While game is not over yet
			    while ( !gameOver && !quit && !isWinning)
                {
                    //Handle events on queue
                    while( SDL_PollEvent( &e ) != 0 )
                    {
                        //User requests quit
                        if( e.type == SDL_QUIT || e.key.keysym.sym == SDLK_ESCAPE)
                        {
                            quit = true;
                        }

                        //Handle button events
                        for (int i = 0; i < ROW_SIZE; i++)
                        {
                            for (int j = 0; j < COLUMN_SIZE; j++)
                            {
                                gButtons[i][j].handleEvent( &e );
                            }
                        }
                        isWinning = checkWinning();
                    }

                    //Clear screen
                    SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
                    SDL_RenderClear( gRenderer );

                    //Render background
                    gBackgroundTexture.render(0, 0);

                    //Render buttons
                    for( int i = 0; i < ROW_SIZE; i++ )
                    {
                        for ( int j = 0; j < COLUMN_SIZE; j++ )
                        {
                            gButtons[i][j].render(i, j);
                        }
                    }
                    //Render mine/flag left
                    mineManager();
					
					//Render timer 
					timeManager();

                    //Perform win/lose flag
                    flagManager();

                    //Update screen
                    SDL_RenderPresent( gRenderer );
                }
                //Check play again flag
                playAgainManager( quit );
			}
		}
	}

	//Free resources and close SDL
	close();

	return 0;
}




