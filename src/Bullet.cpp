#include "../include/Bullet.h"
#include "../include/Sprite.h"
#define M_PI           3.14159265358979323846  /* pi */

Bullet::Bullet(GameObject& associated, float angle, float speed, int damage, float maxDistance, std::string sprite) : Component(associated){
	associated.AddComponent(new Sprite(associated, sprite));
	Sprite* spr = (Sprite*) associated.GetComponent("Sprite");
	spr->angleDeg = angle * 180 / M_PI;
	this->speed = Vec2(speed, 0); this->speed.Rotacao(angle);
	distanceLeft = maxDistance;
	this->damage = damage;
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
int Bullet::GetDamage(){ return damage; }
bool Bullet::Is(std::string type){ return type == "Bullet"; }
void Bullet::Render(){}
Bullet::~Bullet(){}