#include "../include/Resources.h"
#include "../include/Game.h"

std::unordered_map<std::string, SDL_Texture*> Resources::imageTable;
std::unordered_map<std::string, Mix_Music*> Resources::musicTable;
std::unordered_map<std::string, Mix_Chunk*> Resources::soundTable;

SDL_Texture* Resources::GetImage(std::string file){
	if(imageTable.find(file) != imageTable.end()) return (*imageTable.find(file)).second;

	SDL_Texture* textura = IMG_LoadTexture(Game::GetInstance().GetRenderer(), file.c_str());
	if(textura == nullptr){
		// Tratar erro
		std::cout << "Não consegui abrir a textura. Detalhes: " << SDL_GetError() << std::endl;
		exit(1);
	}
	imageTable.insert(make_pair(file, textura));
	return textura;
}
Mix_Music* Resources::GetMusic(std::string file){
	if(musicTable.find(file) != musicTable.end()) return (*musicTable.find(file)).second;

	Mix_Music* musica = Mix_LoadMUS(file.c_str());
	if(musica == nullptr){
		// Tratar erro
		std::cout << "Erro: Não consegui carregar a música. Detalhes: " << SDL_GetError() << std::endl;
		exit(1);
	}

	musicTable.insert(make_pair(file, musica));
	return musica;
}
Mix_Chunk* Resources::GetSound(std::string file){
	if(soundTable.find(file) != soundTable.end()) return (*soundTable.find(file)).second;
	
	Mix_Chunk* som = Mix_LoadWAV(file.c_str());
	if(som == nullptr){
		// Tratar erro
		std::cout << "Erro: Não consegui carregar o som. Detalhes: " << SDL_GetError() << std::endl;
		exit(1);
	}

	soundTable.insert(make_pair(file, som));
	return som;
}

//////////////////////////////////////////////////////////////////////////

void Resources::ClearImages(){
	for(auto iter = imageTable.begin(); iter != imageTable.end(); iter++){
		SDL_DestroyTexture((*iter).second);
		//delete iter;
	}
	imageTable.clear();
}
void Resources::ClearMusics(){
	for(auto iter = musicTable.begin(); iter != musicTable.end(); iter++){
		Mix_FreeMusic((*iter).second);
		//delete iter;
	}
	musicTable.clear();
}
void Resources::ClearSounds(){
	for(auto iter = soundTable.begin(); iter != soundTable.end(); iter++){
		Mix_FreeChunk((*iter).second);
		//delete iter;
	}
	soundTable.clear();
}
