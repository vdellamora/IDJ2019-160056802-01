#ifndef C_PENGUINBODY
#define C_PENGUINBODY

#include "inclusao.h"
#include "GameObject.h"
#include "Vec2.h"
#include "PenguinCannon.h"
#include <iostream>
#include <memory>

class GameObject;
class PenguinBody : public Component{

public:
	PenguinBody(GameObject&);
	~PenguinBody();
	void Start();
	void Update(float);
	void Render();
	bool Is(std::string);

	static PenguinBody* player;
	void NotifyCollision(GameObject&);
	Vec2 GetCentro();
private:
	std::weak_ptr<GameObject> pcannon;
	Vec2 speed;
	float linearSpeed;
	float angle;
	int hp;
};

#endif //C_PENGUINBODY