#include "MenuPausa.h"
#include "Boton.h"


MenuPausa::MenuPausa(Juego* ptr) : Estado(ptr)
{
	type = PAUSE;
	active = false;
	//resetCamera();
	juego->arrayMenu.push_back(new Boton(juego, (juego->SCREEN_WIDTH / 2) - 150 , (juego->SCREEN_HEIGHT / 2) - 100, Juego::TBResumeA, Juego::TBResumeE, BOTON_RESUME));
	juego->arrayMenu.push_back(new Boton(juego, (juego->SCREEN_WIDTH / 2) - 150, (juego->SCREEN_HEIGHT / 2) + 150, Juego::TBExitA, Juego::TBExitE, BOTON_MENU));
}

MenuPausa::~MenuPausa()
{
}

