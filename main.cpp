

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

using namespace std;


 Mix_Music *winner; 
 Mix_Music *loser; 
 Mix_Chunk *click; 

 TTF_Font *gGameOver;   
 TTF_Font *gPlayAgain;

 SDL_Rect gSpriteClips[ BUTTON_SPRITE_TOTAL ];
 

 int countMineLeft;   
 int countTileLeft;  
 bool gameOver;  
 bool isWinning;  

 stringstream mineLeft; 

 int board[ROW_SIZE][COLUMN_SIZE];   

 int sBoard[ROW_SIZE][COLUMN_SIZE]; 

 SDL_Window* gWindow = NULL;
 SDL_Renderer* gRenderer = NULL;


//Starts up SDL and creates window
bool init()
{
	//Initialization flag
	bool success = true;

	//Initialize SDL
	if( SDL_Init( SDL_INIT_VIDEO | SDL_INIT_AUDIO ) < 0 )   //khong biet la gi nhung phai lam dau tien , tai sao lai la <0 vi ham sdl init return 0 la dung
	{
	    cout << "SDL could not initialize! SDL Error: " << SDL_GetError() << endl;
		success = false;
	}
	else
	{
		//Set texture filtering to linear
		
		if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )  //??
		{

			cout << "Warning: Linear texture filtering not enabled!";
		}//Call SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear"); Just before you create bg texture

		//Create window
		gWindow = SDL_CreateWindow( "Minesweeper", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
		if( gWindow == NULL )     // ten, vi tri cua x, y,  ... make sure window show when it created
		{
			cout << "Window could not be created! SDL Error: " << SDL_GetError() << endl; 
			success = false;
		}
		else
		{
			//Create vsynced renderer for window //???
			gRenderer = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC ); //?? -1 la sao
			if( gRenderer == NULL )
			{
			    cout << "Renderer could not be created! SDL Error: " << SDL_GetError() << endl;
				success = false;
			}
			else
			{
				//Initialize PNG loading
				int imgFlags = IMG_INIT_PNG;
				if( !( IMG_Init( imgFlags ) & imgFlags ) )
				{
				    cout << "SDL_image could not initialize! SDL_image Error: " << IMG_GetError() << endl;
					success = false;
				}

                //Initialize SDL_mixer
				if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 )
				{
				    cout << "SDL_mixer could not initialize! SDL_mixer Error: " << Mix_GetError() << endl;
					success = false;
				}

                //Initialize SDL_ttf
				if( TTF_Init() == -1 )
				{
				    cout << "SDL_ttf could not initialize! SDL_ttf Error: " << TTF_GetError() << endl;
					success = false;
				}
			}
		}
	}

	return success;
}

//Loads media
bool loadMedia()
{
	//Loading success flag
	bool success = true;

	//Open the font
	gGameOver = TTF_OpenFont( "Font/whitrabt.ttf", 40 );
	if( gGameOver == NULL )
	{
	    cout << "Failed to load whitrabt font! SDL_ttf Error: " << TTF_GetError() << endl;
		success = false;
	}
	else
	{
		//Render text
		SDL_Color textColor = { 140, 140, 140 };
		if( !gTextTexture.loadFromRenderedText( "YOU LOSE", textColor ) )
		{
			cout << "Failed to render text texture!\n";
			success = false;
		}
	}

	gPlayAgain = TTF_OpenFont( "Font/whitrabt.ttf", 40 );
	if( gPlayAgain == NULL )
	{
	    cout << "Failed to load whitrabt font! SDL_ttf Error: " << TTF_GetError() << endl;
		success = false;
	}
	else
    {
        //Render text
		SDL_Color playAgainWin = { 140, 140, 140 };
		if( !gPlayAgainTexture.loadFromRenderedText( "Press s to play again!", playAgainWin ) )
		{
			cout << "Failed to render text texture!\n";
			success = false;
		}
    }

    gPlayAgain = TTF_OpenFont( "Font/whitrabt.ttf", 40 );
    if( gPlayAgain == NULL )
	{
	    cout << "Failed to load whitrabt font! SDL_ttf Error: " << TTF_GetError() << endl;
		success = false;
	}
	else
    {
        //Render text
		SDL_Color playAgainLose = { 140, 140, 140 };
		if( !gPlayAgainTexture.loadFromRenderedText( "Press s to play again!", playAgainLose ) )
		{
			cout << "Failed to render text texture!\n";
			success = false;
		}
    }

	//Load scene
	if ( !gWinningTexture.loadFromFile( "Image/Winner.png" ) )
    {
        cout << "Failed to load winning texture!\n";
        success = false;
    }
    if ( !gBackgroundTexture.loadFromFile( "Image/Background.png" ) )
    {
        cout << "Failed to load background texture!\n";
        success = false;
    }

	//Load sprites
	
	if( !gButtonSpriteSheetTexture.loadFromFile( "Image/Tiles.png" ) )
	{
		cout << "Failed to load sprites texture!\n";
		success = false;
	}
	else
    {
        //Set sprites
		for( int i = 0; i < BUTTON_SPRITE_TOTAL; i++ )
		{
			gSpriteClips[ i ].x = i * 32;   
			gSpriteClips[ i ].y = 0;
			gSpriteClips[ i ].w = TILE_SIZE;
			gSpriteClips[ i ].h = TILE_SIZE;
		}
		//Set buttons position
		for (int i = 0; i < ROW_SIZE; i++)
        {
            for (int j = 0; j < COLUMN_SIZE; j++)
            {
                gButtons[i][j].setPosition(j * TILE_SIZE + DISTANCE_BETWEEN, i * TILE_SIZE + DISTANCE_BETWEEN);
            }
        }
    }

	//Load sound effects
	
	winner = Mix_LoadMUS( "Sounds/winner.wav" );
	if( winner == NULL )
	{
		cout << "Failed to load winner sound effect! SDL_mixer Error: " << Mix_GetError() << endl;
		success = false;
	}

	loser = Mix_LoadMUS( "Sounds/loser.wav" );
	if( loser == NULL )
	{
		cout << "Failed to load loser sound effect! SDL_mixer Error: " << Mix_GetError() << endl;
		success = false;
	}

	click = Mix_LoadWAV( "Sounds/click.wav" );
	if( click == NULL )
	{
		cout << "Failed to load click sound effect! SDL_mixer Error: " << Mix_GetError() << endl;
		success = false;
	}

	return success;
}

//Shuts down 
void close()
{
	//Free loaded images
	gButtonSpriteSheetTexture.free();
	gMineLeftTexture.free();
	gBackgroundTexture.free();
	gWinningTexture.free();
	gTextTexture.free();

	//Free global font
	TTF_CloseFont( gGameOver );
	TTF_CloseFont( gPlayAgain );

	
	gGameOver = NULL;
	gPlayAgain = NULL;

	//Free the sound effects
	Mix_FreeMusic( winner );
	Mix_FreeMusic( loser );
	Mix_FreeChunk( click );
	winner = NULL;
	loser = NULL;
	click = NULL;

	//Destroy window
	SDL_DestroyRenderer( gRenderer );  //giai phong bo nho
	SDL_DestroyWindow( gWindow ); 
	gWindow = NULL;
	gRenderer = NULL;

	//Quit SDL subsystems
	Mix_Quit();
	IMG_Quit();
	SDL_Quit();
}



int main( int argc, char** argv )  // sdl yeu cau main loai nay
{
	

LTexture gButtonSpriteSheetTexture;

 LTexture gWinningTexture;
 LTexture gBackgroundTexture;

 LTexture gTextTexture;
 LTexture gMineLeftTexture;
 LTexture gPlayAgainTexture;


LButton gButtons[ROW_SIZE][COLUMN_SIZE];   



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

			    //While game is not over yet
			    while ( !gameOver && !quit && !isWinning)
                {
                    //Handle events on queue
                    while( SDL_PollEvent( &e ) != 0 )
                    {
                        //User requests quit
                        if( e.type == SDL_QUIT || e.key.keysym.sym == SDLK_ESCAPE) // loai cua e = quit hoac 
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






