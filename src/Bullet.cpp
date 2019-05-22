#include "../include/Bullet.h"
#include "../include/PenguinBody.h"
#include "../include/Alien.h"
#include "../include/Collider.h"
#include "../include/Sprite.h"

Bullet::Bullet(GameObject& associated, float angle, float speed, int damage, float maxDistance, std::string sprite, bool targetsPlayer) : Component(associated){
	this->speed = Vec2(speed, 0); this->speed.Rotacao(angle);
	this->damage = damage;
	this->targetsPlayer = targetsPlayer;
	if(targetsPlayer) associated.AddComponent(new Sprite(associated, sprite, 3, 0.1));
	else associated.AddComponent(new Sprite(associated, sprite, 4, 0.1));
	associated.AddComponent(new Collider(associated));
	Sprite* spr = (Sprite*) associated.GetComponent("Sprite");
	// TRACEN("Bullet width: ");
	// TRACEN(associated.box.w);
	// TRACEN(" // ");
	// TRACEN(spr->GetClipW());
	// TRACEN(" // ");
	// TRACE(spr->GetWidth());
	spr->angleDeg = angle * 180 / M_PI;
	// spr->SetScaleX(0.33f, 1); // gambs
	distanceLeft = maxDistance;
}
void Bullet::Update(float dt){
	// TRACEN("Bullito: ");
	// TRACEN(associated.box.x);
	// TRACEN(' ');
	// TRACEN(associated.box.y);
	// TRACE("");
	associated.box.x += speed.x * dt;
	associated.box.y += speed.y * dt;
	Vec2 sp = Vec2(speed.x*dt, speed.y*dt);
	distanceLeft -= sp.GetMagnitude();
	// TRACEN("B left: ");
	// TRACE(distanceLeft);
	if(distanceLeft <= 0) associated.RequestDelete();
}

void Bullet::NotifyCollision(GameObject& other){
	Bullet* bul = (Bullet*) other.GetComponent("Bullet");
	PenguinBody* pb = (PenguinBody*) other.GetComponent("PenguinBody");
	Alien* a = (Alien*) other.GetComponent("Alien");
	if(bul) return;
	if((targetsPlayer) && (pb)) associated.RequestDelete();
	if((!targetsPlayer) && (a)) associated.RequestDelete();	
}
int Bullet::GetDamage(){ return damage; }
bool Bullet::Is(std::string type){ return type == "Bullet"; }
void Bullet::Render(){}
Bullet::~Bullet(){}