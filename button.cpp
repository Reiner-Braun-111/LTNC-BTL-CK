#include <ctime>
#include "button.h"

void reveal(int i, int j){
    if (sBoard[i][j] == 10 || sBoard[i][j] == 11){
        if (sBoard[i][j] == 11)
        {
            countMineLeft++;
        }
        sBoard[i][j] = board[i][j];
        countTileLeft--;
        if (sBoard[i][j] == 0)
        {
            if (i < ROW_SIZE - 1)
                reveal(i + 1, j);
            if (i > 0)
                reveal(i - 1, j);
            if (j < COLUMN_SIZE - 1)
                reveal(i, j + 1);
            if (j >0)
                reveal(i, j - 1);
            if (i > 0 && j > 0)
                reveal(i - 1, j - 1);
            if (i < ROW_SIZE - 1 && j < COLUMN_SIZE - 1)
                reveal(i + 1, j + 1);
            if (i > 0 && j < COLUMN_SIZE - 1)
                reveal(i - 1, j + 1);
            if (i < ROW_SIZE - 1 && j > 0)
                reveal(i + 1, j - 1);
        }
    }
}

//lzf


LButton::LButton()
{
	mPosition.x = 0;
	mPosition.y = 0;
}

void LButton::setPosition(int _x, int _y ){
	mPosition.x = _x;
	mPosition.y = _y;
}

void LButton::handleEvent( SDL_Event* e ){



	//If mouse event happened
	if( e->type == SDL_MOUSEMOTION || e->type == SDL_MOUSEBUTTONDOWN || e->type == SDL_MOUSEBUTTONUP )
	{
		// getposition


		int mouseX, mouseY;
		SDL_GetMouseState( &mouseX, &mouseY );

        


		bool inside = true;


		//ngoai
		if ((mouseX <  mPosition.x) || (mouseX > mPosition.x + TILE_SIZE)){
        	inside = false;
    	}
    	if ((mouseY < mPosition.y) || (mouseY > mPosition.y + TILE_SIZE)) {
        	inside = false;
    	}

		int j = (mouseX - DISTANCE_BETWEEN)/TILE_SIZE;
        int i = (mouseY - DISTANCE_BETWEEN)/TILE_SIZE;

		//trong
		if ( inside )
		{
			if ( e->type == SDL_MOUSEBUTTONDOWN )
            {

				switch ( e->button.button )
				{
                    case SDL_BUTTON_LEFT:
                    {

                        reveal(i, j);
                        if (board[i][j] == 9)
                        {
                            gameOver = true;
                        }
                        break;
                    }
                    case SDL_BUTTON_RIGHT:
                    {
                        if (sBoard[i][j] == 10)
                        {
                            if (countMineLeft == 0) break;
                            sBoard[i][j] = 11;
                            countMineLeft--;
                        }
                        else if (sBoard[i][j] > 10)
                        {
                            sBoard[i][j] = 10;
                            countMineLeft++;
                        }
                        else{
                            break;
						}
                        break;
                    }
				}
            }
		}
	}
}

void LButton::render(int i, int j){

	gButtonSpriteSheetTexture.render( mPosition.x, mPosition.y, &gSpriteClips[ sBoard[i][j] ] );
}
