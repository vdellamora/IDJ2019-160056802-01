#ifndef C_SPRITE
#define C_SPRITE

#include "inclusao.h"
//#include "SDL.h"
//#include "SDL_image.h"
#include <iostream>

class Sprite{

public:
	Sprite();
	Sprite(std::string);
	~Sprite();
	void Open(std::string);
	void SetClip(int, int, int, int);
	void Render(int, int);
	int GetWidth();
	int GetHeight();
	bool IsOpen();
private:
	SDL_Texture* texture;
	int width;
	int height;
	SDL_Rect clipRect;

};

#endif //C_SPRITE