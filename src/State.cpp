#include "../include/State.h"
#include "../include/InputManager.h"
#include "../include/Camera.h"
#include "../include/CameraFollower.h"
#include "../include/Alien.h"
#include <cstdlib>
#include <ctime>
#define M_PI           3.14159265358979323846  /* pi */

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
	if(im.KeyPress(SPACE_KEY)){
		// Vec2 *v1 = new Vec2(200, 0);
		// float randomico  = (rand()%1001)/500.0;
		// float pi = -M_PI+(M_PI*randomico);
		// // std::cout << randomico << " // " << pi << std::endl;	
		// v1->Rotacao(pi);
		// // std::cout << *v1 << std::endl;
		// Vec2 *v2 = new Vec2(im.GetMouseX(), im.GetMouseY());
		// Vec2 objPos = Vec2::Soma(v1, v2);

		// AddObject((int)objPos.x, (int)objPos.y);
	}


	for(int i = 0; i < objectArray.size(); i++){
		objectArray[i].get()->Update(dt);
		if(objectArray[i]->IsDead()) {
			Sound* s = (Sound *) objectArray[i]->GetComponent("Sound");
			if (((s) && (!(s->IsPlaying()))) || (!s)) objectArray.erase(objectArray.begin()+i);
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