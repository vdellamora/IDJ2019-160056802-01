#include "../include/Game.h"

Game* Game::instance = nullptr;

	Game& Game::GetInstance(){
		if(instance != nullptr) return *instance;
		instance = new Game("Vitor Moraes Dellamora 16/0056802", 1024, 600);
		return *instance;
	}

	Game::Game(std::string title, int width, int height){
		if(instance == nullptr){
			instance = this;
		} else {
			// Tratar erro
		}

		if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER)){
			// Tratar erro
			//SDL_GetError
		}

		if(IMG_Init(IMG_INIT_JPG)==0){
			// Tratar erro
		}

		if(Mix_Init(MIX_INIT_OGG)==0){
			// Tratar erro
		}
		if(Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, 
			MIX_DEFAULT_FORMAT, 
			MIX_DEFAULT_CHANNELS, 
			1024)){
			// Tratar erro
		}
		//if(Mix_AllocateChannels(2)){}
		////////////////////////////////////////////////////////////

		window = SDL_CreateWindow(title.c_str(), 
			SDL_WINDOWPOS_CENTERED, 
			SDL_WINDOWPOS_CENTERED, 
			width, height, 0);
		renderer = SDL_CreateRenderer(window,
			-1,
			SDL_RENDERER_ACCELERATED);
		state = new State();
	}

	Game::~Game(){
		Mix_CloseAudio();
		Mix_Quit();
		IMG_Quit();
		SDL_DestroyRenderer(renderer);
		SDL_DestroyWindow(window);
		SDL_Quit();
	}

	State& Game::GetState(){
		return *state;
	}

	SDL_Renderer* Game::GetRenderer(){
		return renderer;
	}

	void Game::Run(){
		state->LoadAssets();
		while(!state->QuitRequested()){
			state->Update(0.33);
			state->Render();

			SDL_RenderPresent(renderer);
			SDL_Delay(33);
		}
		Resources::ClearImages();
		Resources::ClearMusics();
		Resources::ClearSounds();
	}