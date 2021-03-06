#ifndef C_BULLET
#define C_BULLET

#include "inclusao.h"
#include "GameObject.h"
#include "Vec2.h"
#include <iostream>

class GameObject;
class Bullet : public Component{

public:
	Bullet(GameObject&, float, float, int, float, std::string, bool);
	~Bullet();
	void Update(float);
	void Render();
	bool Is(std::string);
	int GetDamage();
	void NotifyCollision(GameObject&);
	bool targetsPlayer;
private:
	Vec2 speed;
	float distanceLeft;
	int damage;
};

#endif //C_BULLET