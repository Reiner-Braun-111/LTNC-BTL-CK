#include "variables.h"



Mix_Music *winner = NULL;
Mix_Music *loser = NULL;


TTF_Font *gGameOver = NULL;
TTF_Font *gPlayAgain = NULL;
TTF_Font *gName = NULL;

SDL_Rect gSpriteClips[ BUTTON_SPRITE_TOTAL ];
SDL_Rect gMenuItem[ menuItemTotal ];

Texture gButtonSpriteSheetTexture;
Texture gWinningTexture;
Texture gBackgroundTexture;
Texture gTextTexture;
Texture gMineLeftTexture;
Texture gTimeTexture;
Texture gNameTexture;
Texture gPlayAgainTexture;
Texture gMenuItemTexture;

int countMineLeft = MINE_COUNT;
int countTileLeft = ROW_SIZE * COLUMN_SIZE;
bool gameOver = false;
bool isWinning = false;

stringstream mineLeft;

int board[ROW_SIZE][COLUMN_SIZE];

int sBoard[ROW_SIZE][COLUMN_SIZE];

LButton gButtons[ROW_SIZE][COLUMN_SIZE];
LButton gMenuButtons[2];
stringstream timer;

Timer timeCount;


int menuItemW = 300;
int menuItemH = 40;














