#ifndef C_STAGESTATE
#define C_STAGESTATE

#include "inclusao.h"
#include <iostream>
#include "Sound.h"
#include "Sprite.h"
#include "Music.h"
#include "GameObject.h"
#include "TileSet.h"
#include "TileMap.h"
#include "State.h"
#include <memory>

class StageState : public State{

public:
	StageState();
	~StageState();
	void LoadAssets();
	void Update(float);
	void Render();
	void Start();
	void Pause();
	void Resume();
private:
	GameObject* bg;
	GameObject* tm;
	GameObject* alien;
	GameObject* penguin;
	Music music;

};

#endif //C_STAGESTATE