#include "variables.h"



SDL_Renderer* gRenderer = NULL;

Mix_Music *winner = NULL;
Mix_Music *loser = NULL;
Mix_Chunk *click = NULL;

TTF_Font *gGameOver = NULL;
TTF_Font *gPlayAgain = NULL;

SDL_Rect gSpriteClips[ BUTTON_SPRITE_TOTAL ];
LTexture gButtonSpriteSheetTexture;

LTexture gWinningTexture;
LTexture gBackgroundTexture;

LTexture gTextTexture;
LTexture gMineLeftTexture;
LTexture gPlayAgainTexture;


int countMineLeft = MINE_COUNT;
int countTileLeft = ROW_SIZE * COLUMN_SIZE;
bool gameOver = false;
bool isWinning = false;

stringstream mineLeft;

int board[ROW_SIZE][COLUMN_SIZE];

int sBoard[ROW_SIZE][COLUMN_SIZE];
