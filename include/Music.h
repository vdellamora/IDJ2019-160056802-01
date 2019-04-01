#ifndef C_MUSIC
#define C_MUSIC

#define NOGDI
#include "inclusao.h"
// #include "SDL.h"
// #include "SDL_mixer.h"
#include <iostream>

class Music{

public:
	Music();
	Music(std::string);
	~Music();
	void Play(int = -1);
	void Stop(int  = 1500);
	void Open(std::string);
	bool IsOpen();
private:
	Mix_Music* music;
};

#endif //C_MUSIC