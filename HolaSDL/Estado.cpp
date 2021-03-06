#include "Estado.h"
#include "Interfaz.h"
#include "Boton.h"

Estado::Estado(Juego* ptr)
{
	juego = ptr;

	pRenderer = juego->getRender();
	height = juego->getHeight();
	width = juego->getWidth();
	//camera_ = juego->getCamera();
}


Estado::~Estado() 
{
}

void Estado::draw()
{
	//Limpia el buffer
	SDL_RenderClear(pRenderer);

	SDL_SetRenderDrawColor(pRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
	//Dibuja el fondo (tendremos que cambiarlo cuando empecemos con los fondos y los niveles)
	SDL_Rect rect;
	rect.h = height;
	rect.w = width;
	rect.x = 0;
	rect.y = 0;

	textura = juego->getTextura(Juego::TFondo);
	textura->draw(pRenderer, 0, 0, rect);

	for (int aux = 0; aux < juego->arrayMenu.size(); ++aux) {
			juego->arrayMenu[aux]->draw();
		
	}
	SDL_RenderPresent(pRenderer);
};


void Estado::update(){

	bool clicked = false;
	while (!clicked){


		for (int aux = 0; aux < juego->arrayMenu.size(); ++aux) {
			juego->arrayMenu[aux]->update();
		}

		if (SDL_PollEvent(&e)) {
			if (e.type == SDL_QUIT) {
				salir();
				clicked = true;
			}
			else if (e.type == SDL_MOUSEBUTTONUP) {
				if (e.button.button == SDL_BUTTON_LEFT) {
					
					mouse_x = e.button.x; //+ (camera.x + camera.w / 2) - SCREEN_WIDTH / 2;
					mouse_y = e.button.y; //+ (camera.y + camera.h / 2) - SCREEN_HEIGHT / 2;
					if (onClick()) { clicked = true; }
				}
				// else if(...)    
			}
		}

		draw();
	}
	active = false;
}


bool Estado::onClick() 
{	
	int aux = 0;
	bool flag = false;

	while (aux < juego->arrayMenu.size() && !flag) {
		if (juego->arrayMenu[aux]->dentro(mouse_x, mouse_y))
			flag = true;
		else ++aux;
	}

	if (flag) {

		juego->arrayMenu[aux]->onClick();

		switch (juego->arrayMenu[aux]->getType())
		{
		case BOTON_PLAY:
			play();
			break;
		case BOTON_MENU:
			menu();
			break;
		case BOTON_EXIT:
			salir();
			break;
		case BOTON_RESUME:
			//Back to game (clicked = true)
			//SDL_FlushEvents(1, 10000);
			juego->mVelX = 0;
			juego->mVelY = 0;
			break;
		case BOTON_OPTIONS:
			options();
			break;
		case BOTON_CONTROLS:
			controls();
			break;
		case BOTON_SANGRE:
			juego->arrayMenu[aux]->changeText();
			juego->setSangre();
			return false;
			break;
		case BOTON_FILTER:
			juego->arrayMenu[aux]->changeText();
			juego->setFiltro();
			break;
		case BOTON_RESIZE:
			
			juego->arrayMenu[aux]->changeText();
			juego->changePanoramica();
			
			if (juego->panoramica){
				juego->SCREEN_WIDTH = 1366;
				juego->SCREEN_HEIGHT = 720;
			}
			else{
				juego->SCREEN_WIDTH = 1000;
				juego->SCREEN_HEIGHT = 750;
			}

			SDL_SetWindowSize(juego->pWindow, juego->SCREEN_WIDTH, juego->SCREEN_HEIGHT);
			resetCamera();

			return false;
			break;
		default:
			break;
		}
		
		return true;
	}

	return false;
};

void Estado::play()
{
	juego->estado->changeCurrentState(NIVEL_1);
}

void Estado::cinematicaFinal()
{
	juego->estado->changeCurrentState(CINEMATICA_FINAL);
}

void Estado::menu()
{
	juego->estado->changeCurrentState(MENU_PRINCIPAL);
}

void Estado::options() {
	juego->estado->changeCurrentState(MENU_OPCIONES);
}

void Estado::controls() {

	juego->arrayMenu.push_back(new Boton(juego, 0, 0, width, height, Juego::TControles, Juego::TControles, BOTON_OPTIONS));
	juego->estado->draw();
	SDL_Delay(4000);
}

void Estado::salir() 
{
	juego->setSalir();
}

void Estado::resetCamera() {
	juego->resetCamera();
}