#ifndef C_ALIEN
#define C_ALIEN

#include "inclusao.h"
#include "GameObject.h"
#include "Vec2.h"
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
private:
	class Action{
	public:
		enum ActionType{MOVE, SHOOT};
		Action(ActionType, float, float);
		ActionType type;
		Vec2 pos;
	};

	int hp;
	Vec2 speed;
	int minions;
	std::queue<Action> taskQueue;
	std::vector<std::weak_ptr<GameObject> > minionArray;
};

#endif //C_ALIEN