#ifndef C_ENDSTATE
#define C_ENDSTATE

#include "inclusao.h"
#include "Music.h"
#include "State.h"
#include <iostream>

class EndState : public State{

public:
	EndState();
	~EndState();
	void LoadAssets();
	void Update(float);
	void Render();
	void Start();
	void Pause();
	void Resume();
private:
	Music backgroundMusic;
};

#endif //C_ENDSTATE