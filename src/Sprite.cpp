#include "../include/Game.h"
#include "../include/Rect.h"
#include "../include/Sprite.h"
#include "../include/Resources.h"

Sprite::Sprite(GameObject& go) : Component(go) {
	texture = nullptr;
}
Sprite::Sprite(GameObject& go, std::string file) : Component(go){
	// std::cout << "Construtor do sprite" << std::endl;
	texture = nullptr;
	Open(file);
}
Sprite::~Sprite(){
	// std::cout << "Destrutor do sprite" << std::endl;
}
void Sprite::Open(std::string file){
	texture = Resources::GetImage(file);
	SDL_QueryTexture(texture, nullptr, nullptr, &width, &height);
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

	associated.box = Rect(x, y, w, h);
}
void Sprite::Update(float dt){}
bool Sprite::Is(std::string type){
	if(type=="Sprite") return true;
	return false;
}
void Sprite::Render(){
	// std::cout << "Render do sprite" << std::endl;
	SDL_Rect r;
	r.x = associated.box.x; r.y = associated.box.y;
	r.w = width; r.h = height;
	SDL_RenderCopy(Game::GetInstance().GetRenderer(), 
		texture, &clipRect, &r);
}
void Sprite::Render(float x, float y){
	// std::cout << "Render do sprite" << std::endl;
	SDL_Rect r;
	r.x = x; r.y = y;
	r.w = width; r.h = height;
	SDL_RenderCopy(Game::GetInstance().GetRenderer(), 
		texture, &clipRect, &r);
}
int Sprite::GetWidth(){ return width; }
int Sprite::GetHeight(){ return height; }
bool Sprite::IsOpen(){ return (texture != nullptr); }
