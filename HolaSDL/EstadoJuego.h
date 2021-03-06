#pragma once

#include "ObjetoJuego.h"
#include "SDL.h"
#include <vector>

enum GAME_STATES {MENU_PRINCIPAL, NIVEL_1, GAME_OVER, PAUSE, MENU_OPCIONES, MENU_FINAL, CINEMATICA_FINAL};

class EstadoJuego
{
public:

	EstadoJuego() {}
	virtual ~EstadoJuego(){}

	virtual void draw() = 0;

	virtual void update(double delta) = 0;

	virtual void update() = 0;

	virtual bool onClick() = 0;

	virtual GAME_STATES getCurrentState() = 0;

	virtual void changeCurrentState(GAME_STATES newType) = 0;

	virtual ObjetoJuego* getObjeto(int i) const = 0;

	virtual int getSizeArray() const = 0;

	virtual bool isActive() = 0;
	
	virtual void setActive(bool act) = 0;
};

