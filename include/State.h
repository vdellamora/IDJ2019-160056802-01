#ifndef C_STATE
#define C_STATE

#include "inclusao.h"
#include <iostream>
#include "Sprite.h"
#include "Music.h"

class State{

public:
	State();
	~State();
	bool QuitRequested();
	void LoadAssets();
	void Update(float);
	void Render();
private:
	Sprite bg;
	Music music;
	bool quitRequested;

};

#endif //C_STATE