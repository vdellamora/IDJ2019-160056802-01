#include "../include/Resources.h"
#include "../include/Game.h"

std::unordered_map<std::string, std::shared_ptr<SDL_Texture> > Resources::imageTable;
std::unordered_map<std::string, std::shared_ptr<Mix_Music> > Resources::musicTable;
std::unordered_map<std::string, std::shared_ptr<Mix_Chunk> > Resources::soundTable;
std::unordered_map<std::string, std::shared_ptr<TTF_Font> > Resources::fontTable;

std::shared_ptr<SDL_Texture> Resources::GetImage(std::string file){
	if(imageTable.find(file) != imageTable.end()) return (*imageTable.find(file)).second;

	SDL_Texture* textura = IMG_LoadTexture(Game::GetInstance().GetRenderer(), file.c_str());
	if(textura == nullptr){
		// Tratar erro
		std::cout << "Não consegui abrir a textura. Detalhes: " << SDL_GetError() << std::endl;
		exit(1);
	}

	void (*deleter)(SDL_Texture *) = [] (SDL_Texture *textura) -> void {SDL_DestroyTexture(textura);};

	auto poteiro = std::shared_ptr<SDL_Texture>(textura, deleter);
	imageTable.emplace(file, poteiro);
	return poteiro;
}
std::shared_ptr<Mix_Music> Resources::GetMusic(std::string file){
	if(musicTable.find(file) != musicTable.end()) return (*musicTable.find(file)).second;

	Mix_Music* musica = Mix_LoadMUS(file.c_str());
	if(musica == nullptr){
		// Tratar erro
		std::cout << "Erro: Não consegui carregar a música. Detalhes: " << SDL_GetError() << std::endl;
		exit(1);
	}

	void (*deleter)(Mix_Music *) = [] (Mix_Music *musica) -> void {Mix_FreeMusic(musica);};
	auto poteiro = std::shared_ptr<Mix_Music>(musica, deleter);
	musicTable.emplace(file, poteiro);
	return poteiro;
}
std::shared_ptr<Mix_Chunk> Resources::GetSound(std::string file){
	if(soundTable.find(file) != soundTable.end()) return (*soundTable.find(file)).second;
	
	Mix_Chunk* som = Mix_LoadWAV(file.c_str());
	if(som == nullptr){
		// Tratar erro
		std::cout << "Erro: Não consegui carregar o som. Detalhes: " << SDL_GetError() << std::endl;
		exit(1);
	}

	void (*deleter)(Mix_Chunk *) = [] (Mix_Chunk *som) -> void {Mix_FreeChunk(som);};
	auto poteiro = std::shared_ptr<Mix_Chunk>(som, deleter);
	soundTable.emplace(file, poteiro);
	return poteiro;
}
std::shared_ptr<TTF_Font> Resources::GetFont(std::string file, int size){
	std::string k = file + std::to_string(size);
	if(fontTable.find(k) != fontTable.end()) return (*fontTable.find(k)).second;
	
	TTF_Font* fonte = TTF_OpenFont(file.c_str(), size);
	if(fonte == nullptr){
		// Tratar erro
		std::cout << "Erro: Não consegui carregar a fonte. Detalhes: " << SDL_GetError() << std::endl;
		exit(1);
	}

	void (*deleter)(TTF_Font *) = [] (TTF_Font *fonte) -> void {TTF_CloseFont(fonte);};
	auto poteiro = std::shared_ptr<TTF_Font>(fonte, deleter);
	fontTable.emplace(k, poteiro);
	return poteiro;
}

//////////////////////////////////////////////////////////////////////////

void Resources::ClearImages(){
	for(auto &iter : imageTable){
		if(iter.second.unique()) imageTable.erase(iter.first);
	}
	imageTable.clear();
}
void Resources::ClearMusics(){
	for(auto &iter : musicTable){
		if(iter.second.unique()) musicTable.erase(iter.first);
	}
	musicTable.clear();
}
void Resources::ClearSounds(){
	for(auto &iter : soundTable){
		if(iter.second.unique()) soundTable.erase(iter.first);
	}
	soundTable.clear();
}
void Resources::ClearFonts(){
	for(auto &iter : fontTable){
		if(iter.second.unique()) fontTable.erase(iter.first);
	}
	fontTable.clear();
}
