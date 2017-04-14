#include "Player.h"
#include "GestorVida.h"



Player::Player(Juego* ptr, int px, int py) : Objeto(ptr, px, py)
{
	textura = juego->getTextura(Juego::TPlayer);
	rect.w = 100;
	rect.h = 100;

	rectCollision.w = 32;
	rectCollision.h = 32;
	rectCollision.x = rect.x + rect.w / 3;
	rectCollision.y = rect.y + rect.h / 3;
	velX = 0;
	velY = 0;

	tipo = PJ;

	vidaActual = VIDAMAX; //Inicializaci�n de la vida a su m�ximo
}


Player::~Player()
{
}

void Player::update(int delta) {

	rect.x += juego->getVelX() * delta;
	rect.y += juego->getVelY() * delta;
	
	rectCollision.x = (rect.x + rect.w / 3) * delta;
	rectCollision.y = (rect.y + rect.h / 3) * delta;

	if (juego->touchesWall(this)){
		printf("Wall touched!\n");
		rect.x -= juego->getVelX() * delta;
		rect.y -= juego->getVelY() * delta;
		
		
	}/*
		//Move the dot left or right
		rect.x += juego->getVelX();
		//Move the dot up or down
		rect.y += juego->getVelY();
	*/

	//COMPROBAR AQU� LA COLISI�N DEL JUGADOR CON TODO > LLAMAR CON UN FOR A CADA OBJETO DEL ARRAY
	for (int i = 0; i < juego->topEstado()->getArray().size(); ++i){
		//Comprueba si se ha colisionado con el objeto de la posici�n i del array de objetos
		if (juego->checkCollision(this, juego->topEstado()->getArray()[i])) {
			if(juego->topEstado()->getArray()[i]->getType() == ENEMY) vidaActual--;
		}
	}

	//-- - Gesti�n de la vida-- -
	if (vidaActual <= 0) GestorVida::muerteYDestruccion();
	
} 

bool Player::onClick() {
	

	static_cast <Play*> (juego->topEstado())->newDisparo(this, rect.x + rect.w / 2, rect.y + rect.h / 2);
	return true;
}

void Player::getPos(int& x, int& y) {
	x = rect.x;
	y = rect.y;
}

void Player::onCollision(){

	printf("Auch!");
	dead = true;

}
