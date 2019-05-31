#ifndef C_TITLESTATE
#define C_TITLESTATE

#include "inclusao.h"
#include "State.h"
#include <iostream>
#include <memory>

class TitleState : public State{

public:
	TitleState();
	~TitleState();
	void LoadAssets();
	void Update(float);
	void Render();
	void Start();
	void Pause();
	void Resume();
};

#endif //C_TITLESTATE