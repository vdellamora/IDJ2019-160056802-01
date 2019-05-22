#include "../include/State.h"
#include "../include/InputManager.h"
#include "../include/Collision.h"
#include "../include/Collider.h"
#include "../include/Sprite.h"
#include "../include/Camera.h"
#include "../include/CameraFollower.h"
#include "../include/Alien.h"
#include "../include/PenguinBody.h"
#include <cstdlib>
#include <ctime>


State::State(){
	started = false;
	quitRequested = false;

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
	
}
State::~State(){
	objectArray.clear();
}

void State::Start(){
	LoadAssets();
	for(int i = 0; i < objectArray.size(); i++){
		// TRACE("render: " + i);
		objectArray[i].get()->Start();
	}
	started = true;
}

bool State::QuitRequested(){
	return quitRequested;
}
void State::LoadAssets(){
	// Carregar tudo
	music.Open("assets/audio/stageState.ogg");
	music.Play();
}
void State::Update(float dt){
	// TRACE("StateUpdate");
	InputManager im = InputManager::GetInstance();
	Camera::Update(dt);

	if(im.KeyPress(ESCAPE_KEY) || im.QuitRequested()){ quitRequested = true; }

	for(int i = 0; i < objectArray.size(); i++){
		objectArray[i].get()->Update(dt);

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
void State::Render(){
	bg->GetComponent("Sprite")->Render();
	for(int i = 0; i < objectArray.size(); i++){
		// TRACE("render: " + i);
		objectArray[i].get()->Render();
	}
	TileMap* topo = (TileMap *) tm->GetComponent("TileMap");
	topo->Render(1);
}
std::weak_ptr<GameObject> State::AddObject(GameObject* go){
	std::shared_ptr<GameObject> sptr(go);
	objectArray.emplace_back(sptr);
	if (started) go->Start();
	std::weak_ptr<GameObject> wptr = sptr;
	return wptr;
}
std::weak_ptr<GameObject> State::GetObjectPtr(GameObject* go){
	for(int i = 0; i < objectArray.size(); i++){
		if(objectArray[i].get() == go) 
			return std::weak_ptr<GameObject> (objectArray[i]);
	}
	return std::weak_ptr<GameObject>();
}