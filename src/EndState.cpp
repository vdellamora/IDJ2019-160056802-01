#include "../include/EndState.h"
#include "../include/Game.h"
#include "../include/GameData.h"
#include "../include/GameObject.h"
#include "../include/Camera.h"
#include "../include/InputManager.h"
#include "../include/TitleState.h"
#include "../include/Text.h"
#include "../include/Sprite.h"
#include "../include/Music.h"

bool GameData::playerVictory;

EndState::EndState(){
	GameObject* textSair = new GameObject();
	Text *textSaida = new Text(*textSair, "assets/font/Call me maybe.ttf", 30, Text::TextStyle::SOLID, "Push ESC to quit game", {0,0,0,255});
	textSair->AddComponent(textSaida);
	textSair->box.x = 1280/2 - textSair->box.w/2;
	
	GameObject* textRestart = new GameObject();
	Text *textRestarta = new Text(*textRestart, "assets/font/Call me maybe.ttf", 30, Text::TextStyle::SOLID, "Push space to start again", {0,0,0,255});
	textRestart->AddComponent(textRestarta);
	textRestart->box.x = 1280/2 - textRestart->box.w/2;


	float offset = 0;
	GameObject* background = new GameObject();
	if(GameData::playerVictory){
		background->AddComponent(new Sprite(*background, "assets/img/win.jpg"));
		backgroundMusic.Open("assets/audio/endStateWin.ogg");
		offset = 720;
	} else {
		background->AddComponent(new Sprite(*background, "assets/img/lose.jpg"));
		backgroundMusic.Open("assets/audio/endStateLose.ogg");
		offset = textSair->box.h + textSair->box.h;
	}
	AddObject(background);
	
	textSair->box.y = offset - textSair->box.h/2;
	AddObject(textSair);

	textRestart->box.y = offset - textRestart->box.h/2 - textSair->box.h/2;
	AddObject(textRestart);
}
void EndState::Update(float dt){
	InputManager im = InputManager::GetInstance();
	UpdateArray(dt);

	if(im.QuitRequested() || im.KeyPress(ESCAPE_KEY)) quitRequested = true;
	if(im.KeyPress(SPACE_KEY)){
		popRequested = true;
		Game::GetInstance().Push(new TitleState());
	}
}
void EndState::Start(){
	Camera::pos = Vec2(0,0);
	StartArray();
	LoadAssets();
	backgroundMusic.Play();
}


EndState::~EndState(){}
void EndState::LoadAssets(){}
void EndState::Render(){}
void EndState::Pause(){}
void EndState::Resume(){}
