#ifndef C_ALIEN
#define C_ALIEN

#include "inclusao.h"
#include "GameObject.h"
#include "Vec2.h"
#include "Timer.h"
#include <iostream>
#include <vector>
#include <queue>

class GameObject;
class Alien : public Component{

public:
	Alien(GameObject&, int);
	~Alien();
	void Start();
	void Update(float);
	void Render();
	bool Is(std::string);

	void NotifyCollision(GameObject&);
	static int alienCount;
private:
	enum AlienState {MOVING, RESTING};
	AlienState state;
	Timer restTimer;
	Vec2 destination;
	int hp;
	Vec2 speed;
	int minions;
	std::vector<std::weak_ptr<GameObject> > minionArray;
};

#endif //C_ALIEN