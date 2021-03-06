#pragma once
#include "Objeto.h"
#include "Dialogo.h"
class Aura : public Objeto
{
public:
	Aura(Juego* ptr, int px, int py, int ancho, int alto, std::string texto);
	~Aura();
	void destruyeAlma();
	//void onCollision();

	void onCollision(collision type);

	void update(int delta);
	void draw() const;
private:
	Dialogo* mensaje;
	bool activo;	
	int topeUp, topeDown, contDestruccion;
};

