#pragma once
#include "ObjetoJuego.h"
#include "SDL.h"
#include "Play.h"

class Objeto : public ObjetoJuego
{
public:
	Objeto(Juego* ptr, int px, int py);
	virtual ~Objeto();

	void update() {};
	void update(int delta) {};
	bool dentro(int x, int y) const; 
	void draw() const;
	bool onClick();
	SDL_Rect getRect();

	void gestorVida() {};
	void onCollision() {};
	void onCollision(collision type) {};

	collision getType() {
		return tipo;
	}

	bool isDead() {
		return dead;
	}

	void Oscilar(int delta);

	bool isInside() { return inside; };

	void putInside() { inside = true; };

protected:
	Juego* juego;
	Textura* textura;
	SDL_Renderer* pRenderer;


	SDL_Rect rectAnim;			//Rectangulo para la animación, si hubiera
	SDL_Rect rect;				//Cuadrado en el que se va a dibujar el objeto
	SDL_Rect rectCollision;		//Rect de la colisión.

	collision tipo;
	bool dead = false;
	bool inside = false;
	bool inmunidad;

	bool animado =false;		//Bool que determina si el objeto tiene animación o no
	int velX, velY;				//Velocidad del objeto

	int vida;
	int contadorFrames;
	//Para oscilar
	int cont;
	int cont2;
	bool arriba = true;

	void getStats(int &life, int &bullets, int &dash) {};
};

