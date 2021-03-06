#include "Objeto.h"


Objeto::Objeto(Juego* ptr, int px, int py)
{
	juego = ptr;
	pRenderer = juego->getRender();

	//Position
	rect.x = px;
	rect.y = py;
	cont = cont2 = 0;

	inmunidad = false;

	rectAnim = { 0, 0, 0, 0 };
	contadorFrames = 0;
}


Objeto::~Objeto() {
	juego = nullptr;
	textura = nullptr;
	pRenderer = nullptr;
	sonido = nullptr; //Ojo
}

void Objeto::draw() const
{
	if (animado){
		textura->drawAnimacion(pRenderer, rect.x - juego->camera.x, rect.y - juego->camera.y, rect, rectAnim);
	}
	else textura->draw(pRenderer, rect.x - juego->camera.x, rect.y - juego->camera.y, rect);
}


bool Objeto::dentro(int x, int y)const
{
	return  (x >= rect.x && x <= (rect.w + rect.x) && y >= rect.y && y <= (rect.h + rect.y));
}

bool Objeto::onClick()
{
/*	//printf("onclick objeto \n");
	int x, y;
	juego->getMousePos(x, y);
	if (dentro(x, y)) {
		return true;
	}*/
	return false;
}

SDL_Rect Objeto::getRect(){
	return rectCollision;
}

void Objeto::getPos(int& x, int& y) {
	x = rect.x;
	y = rect.y;
}

void Objeto::Oscilar(int delta){
	cont += delta;
	cont2 += delta;

	if (cont > 2 && arriba){
		rect.y++;
		cont = 0;
	}
	else if (cont > 2){
		rect.y--;
		cont = 0;
	}

	if (cont2 > 100){
		arriba = !arriba;
		cont2 = 0;
	}
}


