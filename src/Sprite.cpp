#include "../include/Game.h"
#include "../include/Sprite.h"


	Sprite::Sprite(){
		texture = nullptr;
	}
	Sprite::Sprite(std::string file){
		texture = nullptr;
		Open(file);
	}
	Sprite::~Sprite(){
		if(texture != nullptr) SDL_DestroyTexture(texture);
	}
	void Sprite::Open(std::string file){
		texture = IMG_LoadTexture(Game::GetInstance().GetRenderer(), file.c_str());
		if(texture == nullptr){
			// Tratar erro
			std::cout << "Não consegui abrir a textura. Detalhes: " << SDL_GetError() << std::endl;
			exit(1);
		}

		SDL_QueryTexture(texture, nullptr, nullptr, &width, &height);
		SetClip(0, 0, width, height);
	}
	void Sprite::SetClip(int x, int y, int w, int h){
		width = w;
		height = h;
		clipRect.x = x;
		clipRect.y = y;
		clipRect.w = w;
		clipRect.h = h;
	}
	void Sprite::Render(int x, int y){
		SDL_Rect r;
		r.x = x; r.y = y;
		r.w = width; r.h = height;
		SDL_RenderCopy(Game::GetInstance().GetRenderer(), 
			texture, &clipRect, &r);
	}
	int Sprite::GetWidth(){ return width; }
	int Sprite::GetHeight(){ return height; }
	bool Sprite::IsOpen(){ return (texture != nullptr); }
