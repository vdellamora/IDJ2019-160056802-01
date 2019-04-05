#include "../include/Face.h"

Face::Face(GameObject& associated) : Component(associated){
	// this.associated = associated;
	hitpoints = 30;
}
//Face::~Face();
void Face::Damage(int damage){
	if(hitpoints<0){
		Component* pegado = associated.GetComponent("Sound");
		((Sound *) pegado)->Play(1);
		associated.RequestDelete();
	} else {
		hitpoints -= damage;
	}
}
void Face::Update(float dt){}
void Face::Render(){}
bool Face::Is(std::string type){return (type == "Face");}