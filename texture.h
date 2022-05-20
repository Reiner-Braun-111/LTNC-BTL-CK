

#ifndef _TEXTURE
#define _TEXTURE

#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <cstring>

using namespace std;

class LTexture
{
	public:
		LTexture();

		~LTexture();
		
		int getWidth();
		int getHeight();

		bool loadFromRenderedText( string textureText, SDL_Color textColor );

		bool loadFromFile( string path );

		void free();

		void render( int x, int y, SDL_Rect* clip = NULL );

	private:
		SDL_Texture* mTexture;

		int mWidth;
		int mHeight;
};
#endif

