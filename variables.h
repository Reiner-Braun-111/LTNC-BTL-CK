
#ifndef _VARIABLES
#define _VARIABLES

#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL.h>
#include <stdio.h>


#include <sstream>

#include "texture.h"
#include "constances.h"
#include "button.h"

extern SDL_Renderer *gRenderer; 

extern int countMineLeft;   
extern int countTileLeft;   
extern bool gameOver;  
extern bool isWinning;  

extern stringstream mineLeft;// 

extern int board[ROW_SIZE][COLUMN_SIZE];   
extern int sBoard[ROW_SIZE][COLUMN_SIZE]; 


extern Mix_Music *winner; 
extern Mix_Music *loser; 
extern Mix_Chunk *click; 

extern TTF_Font *gGameOver;   //
extern TTF_Font *gPlayAgain;//


extern SDL_Rect gSpriteClips[ BUTTON_SPRITE_TOTAL ];//
extern LTexture gButtonSpriteSheetTexture;//

extern LTexture gWinningTexture;//
extern LTexture gBackgroundTexture;//
extern LTexture gTextTexture;//
extern LTexture gMineLeftTexture;//
extern LTexture gPlayAgainTexture;//
  //
extern	LButton gButtons[ROW_SIZE][COLUMN_SIZE];
#endif
