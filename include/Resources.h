#ifndef C_RESOURCES
#define C_RESOURCES

#include "inclusao.h"
#include <iostream>
#include <unordered_map>

class Resources{

public:
	static SDL_Texture* GetImage(std::string);
	static Mix_Music* GetMusic(std::string);
	static Mix_Chunk* GetSound(std::string);

	static void ClearImages();
	static void ClearMusics();
	static void ClearSounds();

private:
	static std::unordered_map<std::string, SDL_Texture*> imageTable;
	static std::unordered_map<std::string, Mix_Music*> musicTable;
	static std::unordered_map<std::string, Mix_Chunk*> soundTable;
};



#endif //C_RESOURCES