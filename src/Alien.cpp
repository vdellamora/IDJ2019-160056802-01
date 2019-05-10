#include "../include/Alien.h"
#include "../include/InputManager.h"
#include "../include/Sprite.h"
#include "../include/Minion.h"
#include "../include/Game.h"
#include "../include/State.h"
#include "../include/Camera.h"
#define M_PI           3.14159265358979323846  /* pi */


Alien::Alien(GameObject& associated, int nMinions) : Component (associated) {
	associated.AddComponent(new Sprite(associated, "assets/img/alien.png"));
	hp = 100;
	speed = Vec2(1000,0);
	minions = nMinions;
}
Alien::~Alien(){
	minionArray.clear();
}
void Alien::Start(){
	// Popular array de minions
	for(int i = 0; i<minions; i++){
		GameObject* minino = new GameObject();
		minino->AddComponent(new Minion(*minino, 
			Game::GetInstance().GetState().GetObjectPtr(&associated), 2*M_PI/minions * i));
		Game::GetInstance().GetState().AddObject(minino);
		minionArray.push_back(Game::GetInstance().GetState().GetObjectPtr(minino));
	}
}
void Alien::Update(float dt){
	InputManager im = InputManager::GetInstance();
	if(im.MousePress(LEFT_MOUSE_BUTTON)){ taskQueue.push(Action( Action::SHOOT, im.GetMouseX() + Camera::pos.x, im.GetMouseY() + Camera::pos.y));}
	if(im.MousePress(RIGHT_MOUSE_BUTTON)){ 
		TRACE("RightMouse " + std::to_string(im.GetMouseX()) + " " + std::to_string(im.GetMouseY()));
		taskQueue.push(Action( Action::MOVE, im.GetMouseX() + Camera::pos.x, im.GetMouseY() + Camera::pos.y));
		TRACE("Size: " + std::to_string(taskQueue.size()));
	}


	if (taskQueue.size() >= 1){
		Action selected = taskQueue.front();
		if(selected.type == Action::MOVE){
			Vec2* goPos = associated.box.GetCentro();
			float dist = Vec2::Distancia(&(selected.pos), goPos);
			speed = Vec2(1000,0);
			speed = speed.MultEscalar(&speed, dt);
			speed.Rotacao(Vec2::InclinacaoReta(&(selected.pos), goPos));

			if(dist <= speed.GetMagnitude()){
				TRACE("Movi");
				associated.box.x = selected.pos.x - associated.box.w/2;
				associated.box.y = selected.pos.y - associated.box.h/2;
				taskQueue.pop();
			} else {
				// TRACE("Movendo... " + std::to_string(associated.box.x) + std::to_string(associated.box.y));
				//goPos = Vec2::Soma(goPos, &speed);
				associated.box.x += speed.x;
				associated.box.y += speed.y;
			}
		}

		if(selected.type == Action::SHOOT){
			float distMin = 9999.9f; int candidato = -1;
			for(int i = 0; i<minions; i++){
				GameObject* go = minionArray[i].lock().get();
				float dist = Vec2::Distancia(&(selected.pos), go->box.GetCentro());
				if(dist < distMin){ distMin = dist; candidato = i; }
			}

			Minion* m = (Minion*) minionArray[candidato].lock().get()->GetComponent("Minion");
			m->Shoot(selected.pos);
			taskQueue.pop();
		}
	}

	Sprite* spr = (Sprite*) associated.GetComponent("Sprite");
	spr->angleDeg -= 0.3f;

	if (hp <= 0) associated.RequestDelete();
}
void Alien::Render(){}
bool Alien::Is(std::string type){ return type == "Alien"; }


Alien::Action::Action(ActionType type, float x, float y){
	this->type = type;
	this->pos = Vec2(x,y);
}