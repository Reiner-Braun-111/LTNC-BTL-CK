#include "function.h"
using namespace std;
void createPlayGround ()
{
    srand(time(NULL));
    int mine = 0;
    for (int i = 0; i < ROW_SIZE; i++)
    {
        for (int j = 0; j < COLUMN_SIZE; j++)
        {
            sBoard[i][j] = 10;
            board[i][j] = 0;
        }
    }
    while (mine < MINE_COUNT)
    {
        int i = rand() % ROW_SIZE;
        int j = rand() % COLUMN_SIZE;
        if ( board[i][j] == 9 )
        {
            continue;
        }
        else
        {
            board[i][j] = 9;
            mine++;
        }
    }
    for (int i=0;i<ROW_SIZE;i++)
    {	for (int j=0;j<COLUMN_SIZE;j++)
      	{
        	int n=0;
        	if (board[i][j]==9) continue;
        	if (board[i+1][j]==9) n++;
        	if (board[i][j+1]==9) n++;
        	if (board[i-1][j]==9) n++;
        	if (board[i][j-1]==9) n++;
        	if (board[i+1][j+1]==9) n++;
        	if (board[i-1][j-1]==9) n++;
        	if (board[i-1][j+1]==9) n++;
        	if (board[i+1][j-1]==9) n++;
        	board[i][j]=n;
      	}
    }
}

bool checkWinning ()
{
    bool win = false;
    if (countTileLeft == MINE_COUNT)
    {
        win = true;
    }
    return win;
}

void mineManager()
{
    //Render text
    if ( !gameOver && !isWinning )
    {
        //Set text color
        SDL_Color textColor = { 0, 255, 255, 255 };

        //Erase the buffer
        mineLeft.str ( "" );
        mineLeft << "Mine left: " << countMineLeft;
        if( !gMineLeftTexture.loadFromRenderedText( mineLeft.str().c_str(), textColor ) )
        {
            cout << "Unable to render mine left texture!\n";
        }

        //Render text
        gMineLeftTexture.render( 5, SCREEN_HEIGHT - gPlayAgainTexture.getHeight()-10 );
    }
}

void timeManager(){
	//Render text
    if ( !gameOver && !isWinning )
    {
        //Set text color
        SDL_Color textColor = { 0, 255, 255, 255 };

        //Erase the buffer
        timer.str ( "" );
        timer << "Time: " << timeCount.getClockCount() ;
        if( !gTimeTexture.loadFromRenderedText( timer.str().c_str(), textColor ) )
        {
            cout << "Unable to render time texture!\n";
    	}
    	//Render text
        gTimeTexture.render( ( 5+  gMineLeftTexture.getWidth() + 10) , SCREEN_HEIGHT - gPlayAgainTexture.getHeight()-10 );
        
        
    }
	
}



void flagManager()
{
    //Check if win
    if ( isWinning && !gameOver )
    {
    
    	timeCount.stop();
    	
        //Update screen
        SDL_RenderPresent( gRenderer );

        //Delay loading screen
        SDL_Delay(500);

        //Play victory music
        Mix_PlayMusic(winner, 0);

        //Render winning scene
        gWinningTexture.render( 0, 30 );

        //Render playAgain
        gPlayAgainTexture.render( ( SCREEN_WIDTH - gPlayAgainTexture.getWidth() ) / 2, SCREEN_HEIGHT - gPlayAgainTexture.getHeight() );
    }

    //Check if lose
    if ( gameOver )
    {
    	timeCount.stop();
    	
        //Render game over text
        gTextTexture.render( ( SCREEN_WIDTH - gTextTexture.getWidth() ) / 2, 30 );

        //Play lost music

        Mix_PlayMusic(loser, 0);

        for( int i = 0; i < ROW_SIZE; i++ )
        {
            for ( int j = 0; j < COLUMN_SIZE; j++ )
            {
                sBoard[i][j] = board[i][j];
                gButtons[i][j].render(i, j);
            }
        }
        //render play again
        gPlayAgainTexture.render( ( SCREEN_WIDTH - gPlayAgainTexture.getWidth() ) / 2, SCREEN_HEIGHT - gPlayAgainTexture.getHeight()-10 );
    }
}

void playAgainManager(bool &quitGame)
{
    //Event handler
    SDL_Event e;

    //Handle events on queue
    while( SDL_PollEvent( &e ) != 0 )
    {
        //play again
        if( e.key.keysym.sym == SDLK_r )
        {
            //stop music
            Mix_HaltMusic();

            //recreate
            countMineLeft = MINE_COUNT;
            countTileLeft = ROW_SIZE * COLUMN_SIZE;

            //Recreate flag
            gameOver = false;
            isWinning = false;
            quitGame = false;
        }
        else if ( e.key.keysym.sym == SDLK_ESCAPE ) quitGame = true;
    }
}

//Starts up SDL and creates window
bool init()
{


	//Initialization flag
	bool success = true;

	//Initialize SDL
	if( SDL_Init( SDL_INIT_VIDEO | SDL_INIT_AUDIO ) < 0 )   {
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
			gRenderer = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
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
/*	gName = TTF_OpenFont( "Font/whitrabt.ttf", 50 );
	if( gName == NULL )
	{
	    cout << "Failed to load whitrabt font! SDL_ttf Error: " << TTF_GetError() << endl;
		success = false;
	}
	else
	{
		//Render text
		SDL_Color textColor = { 0, 255, 255 };
		if( (!gNameTexture.loadFromRenderedText( "Minesweeper", textColor )  ) )
		{
			cout << "Failed to render text texture!\n";
			success = false;
		}
	}*/
	gGameOver = TTF_OpenFont( "Font/whitrabt.ttf", 30 );
	if( gGameOver == NULL )
	{
	    cout << "Failed to load whitrabt font! SDL_ttf Error: " << TTF_GetError() << endl;
		success = false;
	}
	else
	{
		//Render text
		SDL_Color textColor = { 0, 255, 255 };
		if( !gTextTexture.loadFromRenderedText( "YOU LOSE", textColor ) )
		{
			cout << "Failed to render text texture!\n";
			success = false;
		}
	}

	gPlayAgain = TTF_OpenFont( "Font/whitrabt.ttf", 30 );
	if( gPlayAgain == NULL )
	{
	    cout << "Failed to load whitrabt font! SDL_ttf Error: " << TTF_GetError() << endl;
		success = false;
	}
	else
    {
        //Render text
		SDL_Color playAgainWin = { 0, 255, 255 };
		if( !gPlayAgainTexture.loadFromRenderedText( "Press r to play again!", playAgainWin ) )
		{
			cout << "Failed to render text texture!\n";
			success = false;
		}
    }

    gPlayAgain = TTF_OpenFont( "Font/whitrabt.ttf", 30 );
    if( gPlayAgain == NULL )
	{
	    cout << "Failed to load whitrabt font! SDL_ttf Error: " << TTF_GetError() << endl;
		success = false;
	}
	else
    {
        //Render text
		SDL_Color playAgainLose = { 0, 255, 255 };
		if( !gPlayAgainTexture.loadFromRenderedText( "Press r to play again!", playAgainLose ) )
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
		for( int i =0; i < BUTTON_SPRITE_TOTAL; i++)
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

	return success;
}

///Shuts down
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
   // TTF_CloseFont( gName );

	gGameOver = NULL;
	gPlayAgain = NULL;
//	gName = NULL;

	//Free the sound effects
	Mix_FreeMusic( winner );
	Mix_FreeMusic( loser );

	winner = NULL;
	loser = NULL;


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


