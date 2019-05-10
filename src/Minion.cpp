#include "../include/Minion.h"
#include "../include/Sprite.h"
#include "../include/Bullet.h"
#include "../include/Game.h"
#include "../include/State.h"
#include <ctime>
#define M_PI           3.14159265358979323846  /* pi */

Minion::Minion(GameObject& associated, std::weak_ptr<GameObject> alienCenter, float arcOffsetDeg = 0) : Component(associated){
	associated.AddComponent(new Sprite(associated, "assets/img/minion.png"));
	Sprite* spr = (Sprite*) associated.GetComponent("Sprite");
	float escala = 1 + ((std::rand() % 100) / 2.0f / 100.0f);
	TRACEN("Minion escala: "); TRACE(escala);
	spr->SetScaleX(escala, escala);
	arc = arcOffsetDeg;
	this->alienCenter = alienCenter.lock().get();
}

void Minion::Update(float dt){
	if(associated.IsDead()){
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
	// TRACEN("Bullito: ");
	// TRACEN(bullito->box.x);
	// TRACEN(' ');
	// TRACEN(bullito->box.y);
	// TRACE("");
	bullito->AddComponent(new Bullet(*bullito, angulo, 200, 10, 1000, "assets/img/minionbullet1.png"));
	Game::GetInstance().GetState().AddObject(bullito);

}

Minion::~Minion(){}
void Minion::Render(){}
bool Minion::Is(std::string type){ return type == "Minion"; }