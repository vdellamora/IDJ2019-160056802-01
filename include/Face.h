#ifndef C_FACE
#define C_FACE

#include "inclusao.h"
#include "Component.h"
#include "GameObject.h"
#include "Sound.h"
#include <iostream>

// class Component;
class Face : public Component{

public:
	Face(GameObject&);
	//~Face();
	void Damage(int);
	void Update(float);
	void Render();
	bool Is(std::string);
private:
	int hitpoints;
};

#endif //C_FACE