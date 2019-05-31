#include "../include/PenguinCannon.h"
#include "../include/Game.h"
#include "../include/State.h"
#include "../include/Camera.h"
#include "../include/InputManager.h"
#include "../include/Bullet.h"
#include "../include/Collider.h"
#include "../include/Sprite.h"

PenguinCannon::PenguinCannon(GameObject& associated, std::weak_ptr<GameObject> penguinBody) : Component(associated) {
	pbody = penguinBody;
	angle = 0;
	timer = Timer();
	associated.AddComponent(new Sprite(associated, "assets/img/cubngun.png"));
	associated.AddComponent(new Collider(associated));
}
void PenguinCannon::Update(float dt){
	if(!associated.IsDead()){
		GameObject &bod = *pbody.lock();
		if(bod.IsDead()){ TRACE("Time to die"); associated.RequestDelete();}
		associated.box.x = bod.box.x;
		associated.box.y = bod.box.y;
	}

	InputManager im = InputManager::GetInstance();
	Vec2 temp = Vec2(im.GetMouseX() + Camera::pos.x, 
			im.GetMouseY() + Camera::pos.y);
	angle = Vec2::InclinacaoReta(&(temp), 
		associated.box.GetCentro()) *(180/M_PI);

	Sprite* spr = (Sprite*) associated.GetComponent("Sprite");
	spr->angleDeg = angle;

	if((im.MousePress(LEFT_MOUSE_BUTTON)) && (timer.Get() >= 1)){ Shoot(); timer.Restart(); }
	timer.Update(dt);
}
void PenguinCannon::Shoot(){
	GameObject* bullito = new GameObject();
	Vec2 ajuste = Vec2(associated.box.w/2,0);
	ajuste.Rotacao(angle/(180/M_PI));
	bullito->box.x = associated.box.GetCentro()->x - bullito->box.w/2 + ajuste.x;
	bullito->box.y = associated.box.GetCentro()->y - bullito->box.h/2 + ajuste.y;
	bullito->AddComponent(new Bullet(*bullito, angle/(180/M_PI), 200, 34, 1000, "assets/img/penguinbullet.png", false));
	Game::GetInstance().GetCurrentState().AddObject(bullito);
	TRACE("Cannon: Atirei");
}
void PenguinCannon::NotifyCollision(GameObject& other){
	Bullet* bul = (Bullet*) other.GetComponent("Bullet");
	if(bul) return;
}
bool PenguinCannon::Is(std::string type){ return type == "PenguinCannon"; }
void PenguinCannon::Render(){}
PenguinCannon::~PenguinCannon(){}