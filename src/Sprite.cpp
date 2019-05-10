#include "../include/Game.h"
#include "../include/Rect.h"
#include "../include/Sprite.h"
#include "../include/Resources.h"
#include "../include/Camera.h"

Sprite::Sprite(GameObject& go) : Component(go) {
	texture = nullptr;
	scale.x = 1.0f; scale.y = 1.0f;
	angleDeg = 0;
}
Sprite::Sprite(GameObject& go, std::string file) : Component(go){
	// std::cout << "Construtor do sprite" << std::endl;
	// if(file == "assets/img/alien.png") TRACE("Sprite Alien");
	texture = nullptr;
	scale.x = 1.0f; scale.y = 1.0f;
	angleDeg = 0;
	Open(file);
}
Sprite::~Sprite(){
	// std::cout << "Destrutor do sprite" << std::endl;
}
void Sprite::Open(std::string file){
	texture = Resources::GetImage(file);
	SDL_QueryTexture(texture, nullptr, nullptr, &width, &height);
	associated.box.w = width;
	associated.box.h = height;
	SetClip(0, 0, width, height);
}
void Sprite::SetClip(int x, int y, int w, int h){
	// std::cout << "SetClip do sprite" << std::endl;
	width = w;
	height = h;
	clipRect.x = x;
	clipRect.y = y;
	clipRect.w = w;
	clipRect.h = h;

	// associated.box = Rect(x, y, w, h);
}
void Sprite::Update(float dt){}
bool Sprite::Is(std::string type){ return type=="Sprite"; }
void Sprite::Render(){
	// std::cout << "Render do sprite" << std::endl;
	SDL_Rect r;
	float auxX = associated.box.w, auxY = associated.box.h;
	r.w = width * scale.x; r.h = height * scale.y;
	r.x = associated.box.x - Camera::pos.x; r.y = associated.box.y - Camera::pos.y;
	// r.x -= r.x - auxX;
	// r.y -= r.y - auxY;
	SDL_RenderCopyEx(Game::GetInstance().GetRenderer(), 
		texture, &clipRect, &r,
		angleDeg, nullptr, SDL_FLIP_NONE);
}
void Sprite::Render(float x, float y){
	// std::cout << "Render do sprite" << std::endl;
	SDL_Rect r;
	float auxX = associated.box.w, auxY = associated.box.h;
	r.w = width * scale.x; r.h = height * scale.y;
	r.x = x - Camera::pos.x; r.y = y - Camera::pos.y;
	// r.x -= r.x - auxX;
	// r.y -= r.y - auxY;
	SDL_RenderCopyEx(Game::GetInstance().GetRenderer(), 
		texture, &clipRect, &r,
		angleDeg, nullptr, SDL_FLIP_NONE);
}
void Sprite::SetScaleX(float scaleX, float scaleY){
	if(scaleX != 0) scale.x = scaleX;
	if(scaleY != 0) scale.y = scaleY;
}
int Sprite::GetWidth(){ return width*scale.x; }
int Sprite::GetHeight(){ return height*scale.y; }
Vec2 Sprite::GetScale(){ return scale; }
bool Sprite::IsOpen(){ return (texture != nullptr); }
