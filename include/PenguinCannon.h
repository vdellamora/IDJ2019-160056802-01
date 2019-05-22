#ifndef C_PENGUINCANNON
#define C_PENGUINCANNON

#include "inclusao.h"
#include "GameObject.h"
#include "Vec2.h"
#include "Timer.h"
#include <iostream>
#include <memory>

class GameObject;
class PenguinCannon : public Component{

public:
	PenguinCannon(GameObject&, std::weak_ptr<GameObject>);
	~PenguinCannon();
	void Update(float);
	void Render();
	bool Is(std::string);

	void NotifyCollision(GameObject&);
	void Shoot();
private:
	std::weak_ptr<GameObject> pbody;
	Timer timer;
	float angle;
};

#endif //C_PENGUINCANNON