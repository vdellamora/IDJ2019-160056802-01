#include "../include/Face.h"
#include "../include/InputManager.h"
#include "../include/Camera.h"
#include <ctime>

Face::Face(GameObject& associated) : Component(associated){
	// this.associated = associated;
	hitpoints = 30;
}
//Face::~Face();
void Face::Damage(int damage){
	if(hitpoints<=0){
		associated.RemoveComponent(associated.GetComponent("Sprite"));
		Component* pegado = associated.GetComponent("Sound");
		((Sound *) pegado)->Play(1);
		associated.RequestDelete();
	} else {
		hitpoints -= damage;
	}
}
void Face::Update(float dt){
	InputManager im = InputManager::GetInstance();

	if(im.MousePress(LEFT_MOUSE_BUTTON)){
		int mX = im.GetMouseX(),
		mY = im.GetMouseY();

		if(associated.box.IsInside( new Vec2(
			(float)mX + Camera::pos.x, (float)mY + Camera::pos.y) ) ) {
			if (!associated.IsDead()){
				// Aplica dano
				Damage(std::rand() % 10 + 10);
			}
		}

	}
}
void Face::Render(){}
bool Face::Is(std::string type){return (type == "Face");}