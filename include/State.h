#ifndef C_STATE
#define C_STATE

#include "inclusao.h"
#include <iostream>
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
	void Start();
	void LoadAssets();
	void Update(float);
	void Render();
	std::weak_ptr<GameObject> AddObject(GameObject*);
	std::weak_ptr<GameObject> GetObjectPtr(GameObject*);
	bool QuitRequested();
private:
	GameObject* bg;
	GameObject* tm;
	GameObject* alien;
	Music music;
	bool started;
	bool quitRequested;

	void Input();
	void AddObject(int, int);
	std::vector<std::shared_ptr<GameObject>> objectArray;

};

#endif //C_STATE