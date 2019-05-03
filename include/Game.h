#ifndef C_GAME
#define C_GAME

#include "inclusao.h"
#include <iostream>
#include "State.h"
#include "Resources.h"

class State;
class Game{

public:
	~Game();
	void Run();
	SDL_Renderer* GetRenderer();
	State& GetState();
	static Game& GetInstance();
	float GetDeltaTime();
private:
	Game(std::string, int, int);
	static Game* instance;
	SDL_Window* window;
	SDL_Renderer* renderer;
	State* state;
	int frameStart;
	float dt;

	void CalculateDeltaTime();

};

#endif //C_GAME