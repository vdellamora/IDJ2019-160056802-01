#ifndef C_SPRITE
#define C_SPRITE

#include "inclusao.h"
#include "Component.h"
#include "Vec2.h"
#include <iostream>

class Sprite : public Component{

public:
	Sprite(GameObject&);
	Sprite(GameObject&, std::string);
	~Sprite();
	void Open(std::string);
	void SetClip(int, int, int, int);
	void SetScaleX(float, float);
	void Update(float);
	void Render();
	void Render(float, float);
	int GetWidth();
	int GetHeight();
	Vec2 GetScale();
	bool Is(std::string);
	bool IsOpen();
	float angleDeg;
private:
	SDL_Texture* texture;
	int width;
	int height;
	Vec2 scale;
	SDL_Rect clipRect;

};

#endif //C_SPRITE