
#ifndef _VARIABLES
#define _VARIABLES

#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL.h>
#include <stdio.h>


#include <sstream>

#include "texture.h"
#include "constances.h"
#include "button.h"
#include "time.h"

extern SDL_Renderer *gRenderer;

extern int countMineLeft;
extern int countTileLeft;
extern bool gameOver;
extern bool isWinning;

extern stringstream mineLeft;//

extern stringstream timer;

extern int board[ROW_SIZE][COLUMN_SIZE];
extern int sBoard[ROW_SIZE][COLUMN_SIZE];


extern Mix_Music *winner;
extern Mix_Music *loser;

extern TTF_Font *gGameOver;   //
extern TTF_Font *gPlayAgain;//


extern TTF_Font *gName;

extern SDL_Rect gSpriteClips[ BUTTON_SPRITE_TOTAL ];//
extern Texture gButtonSpriteSheetTexture;//

extern Texture gWinningTexture;//
extern Texture gBackgroundTexture;//
extern Texture gTextTexture;//
extern Texture gMineLeftTexture;//
extern Texture gPlayAgainTexture;//
extern Texture gTimeTexture;//




extern Texture gNameTexture;//


extern	LButton gButtons[ROW_SIZE][COLUMN_SIZE];

extern Timer timeCount;


extern Texture gMenuItemTexture;
extern SDL_Rect gMenuItem[ menuItemTotal ];
extern int menuItemW ;
extern int menuItemH;
extern LButton gMenuButtons[2];









#endif
