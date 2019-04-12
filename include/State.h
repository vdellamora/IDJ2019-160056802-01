#ifndef C_STATE
#define C_STATE

#include "inclusao.h"
#include <iostream>
#include "Face.h"
#include "Sound.h"
#include "Sprite.h"
#include "Music.h"
#include "GameObject.h"
#include "TileSet.h"
#include "TileMap.h"
#include <memory>

// class Music;

class State{

public:
	State();
	~State();
	bool QuitRequested();
	void LoadAssets();
	void Update(float);
	void Render();

private:
	GameObject* bg;
	GameObject* tm;
	Music music;
	bool quitRequested;

	void Input();
	void AddObject(int, int);
	std::vector<std::shared_ptr<GameObject>> objectArray;

};

#endif //C_STATE