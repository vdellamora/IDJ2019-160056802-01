#include "../include/PenguinBody.h"
#include "../include/Game.h"
#include "../include/State.h"
#include "../include/Camera.h"
#include "../include/InputManager.h"
#include "../include/Collider.h"
#include "../include/Sprite.h"
#include "../include/Sound.h"
#include "../include/Bullet.h"

PenguinBody *PenguinBody::player = nullptr;

PenguinBody::PenguinBody(GameObject& associated) : Component(associated){
	speed = Vec2(0, 0); linearSpeed = 0;
	angle = 0; hp = 100;
	associated.AddComponent(new Sprite(associated, "assets/img/penguin.png"));
	associated.AddComponent(new Collider(associated));
	PenguinBody::player = this;
}
PenguinBody::~PenguinBody(){
	// TRACEN("PEnguimorto ");
	player = nullptr;
	// int po = (player==nullptr)?1:0;
	// TRACE(po);
}
void PenguinBody::Start(){
	GameObject* pinguino = new GameObject();
	pinguino->AddComponent(new PenguinCannon(*pinguino, 
		Game::GetInstance().GetState().GetObjectPtr(&associated)));
	pcannon = Game::GetInstance().GetState().AddObject(pinguino);
}
void PenguinBody::Update(float dt){
	InputManager im = InputManager::GetInstance();
	if((im.IsKeyDown(A_KEY)) || (im.IsKeyDown(D_KEY))){
		if (im.IsKeyDown(A_KEY)) angle -= 90*dt;
		else angle += 90*dt;
	}
	if((im.IsKeyDown(W_KEY)) || (im.IsKeyDown(S_KEY))){
		float acc;
		if (im.IsKeyDown(W_KEY)) acc = 500; 
		else acc = -500;
		linearSpeed += acc*dt*dt/2;
	}
	Sprite* spr = (Sprite*) associated.GetComponent("Sprite");
	spr->angleDeg = angle;
	speed = Vec2(linearSpeed, 0);
	speed.Rotacao(angle*(M_PI/180));

	associated.box.x += speed.x;
	associated.box.y += speed.y;

	if(linearSpeed>0) linearSpeed -= 300*dt*dt/2;
	if(linearSpeed<0) linearSpeed += 300*dt*dt/2;

	if((im.KeyPress(W_KEY)) && (im.KeyPress(S_KEY))){
		TRACEN("AnguloP: ");
		TRACEN(spr->angleDeg);
		TRACEN(" Speed: ");
		TRACEN(speed.x);
		TRACEN(" ");
		TRACE(speed.y);
	}

	////////////////////////////////////
	if(hp<=0){
		(*pcannon.lock()).RequestDelete();
		Camera::Unfollow();
		TRACE("Comeca a morte");
		GameObject* explosao = new GameObject();
		TRACE("Seta a explosao e posicao");
		explosao->AddComponent(new Sprite(*explosao, "assets/img/penguindeath.png", 5, 0.1f, 0.5f));
		explosao->box.x = associated.box.x;
		explosao->box.y = associated.box.y;
		TRACE("Explosao component");
		Sound* som = new Sound(*explosao, "assets/audio/boom.wav");
		explosao->AddComponent(som);
		TRACE("Explosao som");
		som->Play();
		TRACE("Explosao play");
		associated.RequestDelete();
		TRACE("Fim");
	}
}
void PenguinBody::NotifyCollision(GameObject& other){
	Bullet* bul = (Bullet*) other.GetComponent("Bullet");
	if(bul && bul->targetsPlayer) hp -= bul->GetDamage();;
}
Vec2 PenguinBody::GetCentro(){return Vec2(associated.box.GetCentro()->x, associated.box.GetCentro()->y); }
bool PenguinBody::Is(std::string type){ return type == "PenguinBody"; }
void PenguinBody::Render(){}