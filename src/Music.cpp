#include <iostream>
#include "../include/Music.h"


	Music::Music(){ music = nullptr; }
	Music::Music(std::string file){
		//music = nullptr;
		Open(file);
	}
	Music::~Music(){
		Stop(0);
		Mix_FreeMusic(music);
	}
	void Music::Play(int times){
		if(music != nullptr) Mix_PlayMusic(music, times);
		else {
			// Tratar erro
			std::cout << "Erro: Não há música nesta instância. Detalhes: " << SDL_GetError() << std::endl;
			exit(1);
		}

	}
	void Music::Stop(int msToStop){ Mix_FadeOutMusic(msToStop); }
	void Music::Open(std::string file){
		music = Mix_LoadMUS(file.c_str());
		if(music == nullptr){
			// Tratar erro
			std::cout << "Erro: Não consegui carregar a música. Detalhes: " << SDL_GetError() << std::endl;
			exit(1);
		}
	}
	bool Music::IsOpen(){ return (music!=nullptr); }
