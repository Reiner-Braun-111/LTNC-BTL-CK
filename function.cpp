#include "function.h"

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
        SDL_Color textColor = { 140, 140, 140, 255 };

        //Erase the buffer
        mineLeft.str ( "" );
        mineLeft << "Mine left: " << countMineLeft;
        if( !gMineLeftTexture.loadFromRenderedText( mineLeft.str().c_str(), textColor ) )
        {
            cout << "Unable to render mine left texture!\n";
        }

        //Render text
        gMineLeftTexture.render( ( SCREEN_WIDTH - gMineLeftTexture.getWidth() ) / 2, 0 );
    }
}

void flagManager()
{
    //Check if win
    if ( isWinning && !gameOver )
    {
        //Update screen
        SDL_RenderPresent( gRenderer );

        //Delay loading screen
        SDL_Delay(500);

        //Play victory music
        Mix_PlayMusic(winner, 0);

        //Render winning scene
        gWinningTexture.render( 0, 0 );

        //Render playAgain
        gPlayAgainTexture.render( ( SCREEN_WIDTH - gPlayAgainTexture.getWidth() ) / 2, SCREEN_HEIGHT - gPlayAgainTexture.getHeight() );
    }

    //Check if lose
    if ( gameOver )
    {
        //Render game over text
        gTextTexture.render( ( SCREEN_WIDTH - gTextTexture.getWidth() ) / 2, 0 );

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
        gPlayAgainTexture.render( ( SCREEN_WIDTH - gPlayAgainTexture.getWidth() ) / 2, SCREEN_HEIGHT - gPlayAgainTexture.getHeight() );
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
        if( e.key.keysym.sym == SDLK_s )
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


