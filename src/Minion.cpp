#include "../include/Minion.h"
#include "../include/Collider.h"
#include "../include/Sprite.h"
#include "../include/Bullet.h"
#include "../include/Game.h"
#include "../include/State.h"
#include <ctime>

Minion::Minion(GameObject& associated, std::weak_ptr<GameObject> alienCenter, float arcOffsetDeg = 0) : Component(associated){
	associated.AddComponent(new Sprite(associated, "assets/img/minion.png"));
	associated.AddComponent(new Collider(associated));
	Sprite* spr = (Sprite*) associated.GetComponent("Sprite");
	float escala = 1 + ((std::rand() % 100) / 2.0f / 100.0f);
	TRACEN("Minion escala: "); TRACE(escala);
	spr->SetScaleX(escala, escala);
	arc = arcOffsetDeg;
	this->alienCenter = alienCenter.lock().get();
}

void Minion::Update(float dt){
	if(alienCenter->IsDead()){
		associated.RequestDelete();
		return;
	}
	arc += 1.0f * dt;
	Vec2 offset = Vec2(200, 0);
	offset.Rotacao(arc);
	Vec2 aux = Vec2(alienCenter->box.GetCentro()->x, alienCenter->box.GetCentro()->y);
	aux = Vec2::Soma(&offset, &aux);
	associated.box.x = aux.x - associated.box.w/2;
	associated.box.y = aux.y - associated.box.h/2;

	Sprite* spr = (Sprite*) associated.GetComponent("Sprite");
	spr->angleDeg = offset.GetInclinacao() * 180 / M_PI;
}

void Minion::Shoot(Vec2 target){
	float angulo = Vec2::InclinacaoReta(&target, associated.box.GetCentro());
	GameObject* bullito = new GameObject();
	bullito->box.x = associated.box.GetCentro()->x - bullito->box.w/2;
	bullito->box.y = associated.box.GetCentro()->y - bullito->box.h/2;
	bullito->AddComponent(new Bullet(*bullito, angulo, 200, 25, 1000, "assets/img/minionbullet2.png", true));
	Game::GetInstance().GetState().AddObject(bullito);
}
void Minion::NotifyCollision(GameObject& other){
	Bullet* bul = (Bullet*) other.GetComponent("Bullet");
	// if((bul) && !(bul->targetsPlayer)) associated.RequestDelete();
}
Minion::~Minion(){}
void Minion::Render(){}
bool Minion::Is(std::string type){ return type == "Minion"; }