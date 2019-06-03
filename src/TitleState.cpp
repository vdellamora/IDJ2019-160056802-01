#include "../include/TitleState.h"
#include "../include/Game.h"
#include "../include/Camera.h"
#include "../include/StageState.h"
#include "../include/InputManager.h"
#include "../include/GameObject.h"
#include "../include/Sprite.h"
#include "../include/Text.h"

TitleState::TitleState(){
	GameObject* titulo = new GameObject();
	titulo->AddComponent(new Sprite(*titulo, "assets/img/title.jpg"));
	AddObject(titulo);

	GameObject* fonte = new GameObject();
	fonte->AddComponent(new Text(*fonte, "assets/font/Call me maybe.ttf", 50, Text::TextStyle::SOLID, "Press space to start", {0,0,0,255}));
	fonte->box.x = 1280/2 - fonte->box.w/2;
	fonte->box.y = 720/2 - fonte->box.h/2;
	AddObject(fonte);
}
void TitleState::Update(float dt){
	InputManager im = InputManager::GetInstance();
	UpdateArray(dt);
	if(im.KeyPress(ESCAPE_KEY) || im.QuitRequested()){ quitRequested = true; }

	if(im.KeyPress(SPACE_KEY)){
		TRACE("Title novo Stage");
		Game::GetInstance().Push(new StageState());
	}
}
void TitleState::Render(){RenderArray();}
void TitleState::Start(){StartArray();}
void TitleState::Resume(){Camera::pos = Vec2(0,0);}

TitleState::~TitleState(){}
void TitleState::LoadAssets(){}
void TitleState::Pause(){}