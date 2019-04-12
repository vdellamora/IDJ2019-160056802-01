#ifndef C_SPRITE
#define C_SPRITE

#include "inclusao.h"
#include "Component.h"
#include <iostream>

class Sprite : public Component{

public:
	Sprite(GameObject&);
	Sprite(GameObject&, std::string);
	~Sprite();
	void Open(std::string);
	void SetClip(int, int, int, int);
	void Update(float);
	void Render();
	void Render(float, float);
	int GetWidth();
	int GetHeight();
	bool Is(std::string);
	bool IsOpen();
private:
	SDL_Texture* texture;
	int width;
	int height;
	SDL_Rect clipRect;

};

#endif //C_SPRITE