#include "../include/State.h"


	State::State(){
		quitRequested = false;
		bg = Sprite();
		music = Music();
		
	}
	State::~State(){}

	bool State::QuitRequested(){
		return quitRequested;
	}
	void State::LoadAssets(){
		// Carregar tudo
		bg.Open("assets/img/ocean.jpg");
		music.Open("assets/audio/stageState.ogg");
		music.Play();
	}
	void State::Update(float dt){
		if(SDL_QuitRequested()) quitRequested = true;
	}
	void State::Render(){
		// Chamar o render do fundo
		bg.Render(0,0);
	}
