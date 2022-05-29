
#ifndef _FUNCTION
#define _FUNCTION

#include "texture.h"
#include "constances.h"
#include "variables.h"
#include "button.h"
#include "time.h"


#include <ctime>

extern SDL_Window *gWindow; 

bool init();

bool loadMedia();

void close();

void createPlayGround ();

bool checkWinning ();

void mineManager();

void timeManager();

void flagManager();

void playAgainManager(bool &quitGame);

int menuRender(SDL_Event &e);



#endif



