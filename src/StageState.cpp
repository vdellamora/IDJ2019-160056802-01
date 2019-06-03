#include "../include/StageState.h"
#include "../include/Game.h"
#include "../include/InputManager.h"
#include "../include/GameData.h"
#include "../include/EndState.h"
#include "../include/Collision.h"
#include "../include/Collider.h"
#include "../include/Sprite.h"
#include "../include/Camera.h"
#include "../include/CameraFollower.h"
#include "../include/Alien.h"
#include "../include/PenguinBody.h"
#include <cstdlib>
#include <ctime>


StageState::StageState() : State(){
	started = false;

	bg = new GameObject();
	bg->AddComponent(new Sprite(*bg, "assets/img/ocean.jpg"));
	bg->AddComponent(new CameraFollower(*bg));
	objectArray.emplace_back(bg);

	tm = new GameObject();
	tm->box.x = 0;
	tm->box.y = 0;
	tm->AddComponent(new TileMap(*tm, 
		"assets/map/tileMap.txt", 
		new TileSet(64, 64, "assets/img/tileset.png")));
	objectArray.emplace_back(tm);

	alien = new GameObject();
	alien->AddComponent(new Alien(*alien, 3));
	alien->box.x = 512;
	alien->box.y = 300;
	objectArray.emplace_back(alien);

	penguin = new GameObject();
	penguin->AddComponent(new PenguinBody(*penguin));
	penguin->box.x = 704;
	penguin->box.y = 640;
	Camera::Follow(penguin);
	objectArray.emplace_back(penguin);

	music = Music();
	quitRequested = false;
}

void StageState::Start(){
	if(popRequested) return;
	StartArray();
	LoadAssets();
}

void StageState::LoadAssets(){
	// Carregar tudo
	music.Open("assets/audio/stageState.ogg");
	music.Play();
}
void StageState::Update(float dt){
	// TRACE("StageStateUpdate");
	InputManager im = InputManager::GetInstance();
	Camera::Update(dt);

	if(im.QuitRequested()) quitRequested = true;
	if(im.KeyPress(ESCAPE_KEY)){ TRACE("stage POP"); popRequested = true; return;}

	for(int i = 0; i < objectArray.size(); i++){
		objectArray[i].get()->Update(dt);

		if(Alien::alienCount == 0 || PenguinBody::player == nullptr){
			GameData::playerVictory = PenguinBody::player != nullptr;
			popRequested = true;
			Game::GetInstance().Push(new EndState());
		}

		Collider* col1 = (Collider *) objectArray[i]->GetComponent("Collider");
		if(col1){
			for(int j = i+1; j < objectArray.size(); j++){
				Collider* col2 = (Collider *) objectArray[j]->GetComponent("Collider");
				if(col2){
					Sprite* spr1 = (Sprite*) objectArray[i]->GetComponent("Sprite");
					Sprite* spr2 = (Sprite*) objectArray[j]->GetComponent("Sprite");
					//spr->angleDeg -= 0.3f;
					if(Collision::IsColliding(
						col1->box, col2->box, 
						spr1->angleDeg, spr2->angleDeg)){
						objectArray[i]->NotifyCollision(*objectArray[j]);
						objectArray[j]->NotifyCollision(*objectArray[i]);
					}
				}
			}
		}

		if(objectArray[i]->IsDead()) {
			/*Sound* s = (Sound *) objectArray[i]->GetComponent("Sound");
			if (((s) && (!(s->IsPlaying()))) || (!s)){ if(s)TRACE("Tem som");*/
			objectArray.erase(objectArray.begin()+i);//}
		}
	}

}
void StageState::Render(){
	bg->GetComponent("Sprite")->Render();
	for(int i = 0; i < objectArray.size(); i++){
		// TRACE("render: " + i);
		objectArray[i].get()->Render();
	}
	TileMap* topo = (TileMap *) tm->GetComponent("TileMap");
	topo->Render(1);
}

StageState::~StageState(){objectArray.clear();}
void StageState::Pause(){}
void StageState::Resume(){}