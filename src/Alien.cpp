#include "../include/Alien.h"
#include "../include/InputManager.h"
#include "../include/Collider.h"
#include "../include/Sprite.h"
#include "../include/Sound.h"
#include "../include/Minion.h"
#include "../include/PenguinBody.h"
#include "../include/Bullet.h"
#include "../include/Game.h"
#include "../include/State.h"
#include "../include/Camera.h"

int Alien::alienCount = 0;

Alien::Alien(GameObject& associated, int nMinions) : Component (associated) {
	associated.AddComponent(new Sprite(associated, "assets/img/alien.png"));
	associated.AddComponent(new Collider(associated));
	hp = 100;
	speed = Vec2(1000,0);
	minions = nMinions;
	Alien::alienCount++;
	state = RESTING;
}
Alien::~Alien(){
	Alien::alienCount--;
	minionArray.clear();
}
void Alien::Start(){
	// Popular array de minions
	for(int i = 0; i<minions; i++){
		GameObject* minino = new GameObject();
		minino->AddComponent(new Minion(*minino, 
			Game::GetInstance().GetCurrentState().GetObjectPtr(&associated), 2*M_PI/minions * i));
		Game::GetInstance().GetCurrentState().AddObject(minino);
		minionArray.push_back(Game::GetInstance().GetCurrentState().GetObjectPtr(minino));
	}
}
void Alien::Update(float dt){
	Sprite* spr = (Sprite*) associated.GetComponent("Sprite");
	spr->angleDeg -= 0.3f;
	if(PenguinBody::player == nullptr) return;

	if(state == RESTING){
		restTimer.Update(dt);
		if(restTimer.Get() > 2){
			destination = PenguinBody::player->GetCentro();
			Vec2* goPos = associated.box.GetCentro();
			speed = Vec2(200,0);
			speed = speed.MultEscalar(&speed, dt);
			speed.Rotacao(Vec2::InclinacaoReta(&(destination), goPos));
			state = MOVING;
		}
	}

	if(state == MOVING){
		Vec2* goPos = associated.box.GetCentro();
		float dist = Vec2::Distancia(&(destination), goPos);

		if(dist <= speed.GetMagnitude()){
			// TRACE("Movi");
			associated.box.x = destination.x - associated.box.w/2;
			associated.box.y = destination.y - associated.box.h/2;
			
			//ATIRA
			destination = PenguinBody::player->GetCentro();
			float distMin = 9999.9f; int candidato = -1;
			for(int i = 0; i<minions; i++){
				GameObject* go = minionArray[i].lock().get();
				float dist1 = Vec2::Distancia(&(destination), go->box.GetCentro());
				if(dist1 < distMin){ distMin = dist1; candidato = i; }
			}
			Minion* m = (Minion*) minionArray[candidato].lock().get()->GetComponent("Minion");
			m->Shoot(destination);
			TRACE("Alien: atirei");
			restTimer.Restart();
			state = RESTING;

		} else {
			// TRACE("Movendo... " + std::to_string(associated.box.x) + std::to_string(associated.box.y));
			//goPos = Vec2::Soma(goPos, &speed);
			associated.box.x += speed.x;
			associated.box.y += speed.y;
		}
	}


	if (hp <= 0){
		TRACE("Comeca a morte");
		GameObject* explosao = new GameObject();
		TRACE("Seta a explosao e posicao");
		explosao->AddComponent(new Sprite(*explosao, "assets/img/aliendeath.png", 4, 0.1f, 0.4f));
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
void Alien::NotifyCollision(GameObject& other){
	Bullet* bul = (Bullet*) other.GetComponent("Bullet");
	if(bul && !(bul->targetsPlayer)) hp -= bul->GetDamage();
}
void Alien::Render(){}
bool Alien::Is(std::string type){ return type == "Alien"; }