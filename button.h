
#ifndef _BUTTON
#define _BUTTON

#include <SDL2/SDL.h>
#include <stdio.h>


#include <sstream>

#include "texture.h"

//#include "variables.h"
#include "constances.h"

extern int countMineLeft;   
extern int countTileLeft; 

extern int board[ROW_SIZE][COLUMN_SIZE];   
extern int sBoard[ROW_SIZE][COLUMN_SIZE]; 

extern SDL_Rect gSpriteClips[ BUTTON_SPRITE_TOTAL ];//
extern Texture gButtonSpriteSheetTexture;//

extern bool gameOver;  



void reveal(int i, int j);

class LButton{
	public:
		LButton();

		void setPosition( int x, int y );
		void handleEvent( SDL_Event* e );
		void render(int i, int j);

	//private:
		SDL_Point mPosition;
};
#endif


