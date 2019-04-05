#ifndef C_GAMEOBJECT
#define C_GAMEOBJECT

#include "inclusao.h"
#include <iostream>
#include <memory>
#include <vector>
#include "Component.h"
#include "Rect.h"

class Component;
class GameObject{

public:
	GameObject();
	~GameObject();
	void Update(float);
	void Render();
	bool IsDead();
	void RequestDelete();
	void AddComponent(Component*);
	void RemoveComponent(Component*);
	Component* GetComponent(std::string);

	Rect box;
private:
	std::vector<std::shared_ptr<Component>> components;
	bool isDead;
};

#endif //C_GAMEOBJECT