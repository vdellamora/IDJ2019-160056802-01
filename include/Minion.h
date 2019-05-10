#ifndef C_MINION
#define C_MINION

#include "inclusao.h"
#include "GameObject.h"
#include "Vec2.h"
#include <iostream>

class GameObject;
class Minion : public Component{

public:
	Minion(GameObject&, std::weak_ptr<GameObject>, float);
	~Minion();
	void Update(float);
	void Render();
	bool Is(std::string);
	void Shoot(Vec2);
private:
	GameObject* alienCenter;
	float arc;
};

#endif //C_MINION