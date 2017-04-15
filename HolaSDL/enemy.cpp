#include "enemy.h"
#include "Player.h"


enemy::enemy(Juego* ptr, int px, int py) : Objeto(ptr, px, py)
{
	textura = juego->getTextura(Juego::TEnemy);

	vel = 6;
	freDis = 100;
	velDis = 20;

	rect.w = 50;
	rect.h = 50;

	rect.x = 100;
	rect.y = 100;
}


enemy::~enemy()
{
}

void enemy::update() 
{	
	int x, y;
	static_cast <Play*> (juego->topEstado())->posPlayer(x, y);
	if (contDis < freDis - 10){ //Algo tope chungo para que se pare al disparar
		follow(x, y);
	}
	//follow(x, y);
	++contDis;
	if (contDis >= freDis){
		shoot(x, y);
		contDis = 0;
	}
}

void enemy::follow(int x, int y){ // posicion del objeto que vas a seguir 
	
	int distance = sqrt((x - rect.x)*(x - rect.x) + (y - rect.y)*(y - rect.y));

	if (distance > vel / 2) { //este numero es un margen de error que tendra que ir acorde con la velocidad del enemigo (vel)
		vX = vel * (x - rect.x) / distance;
		vY = vel * (y - rect.y) / distance;
	}
	else {
		vX = 0;
		vY = 0;
	}
	rect.x += vX;
	rect.y += vY;
}

void enemy::shoot(int targetX, int targetY){
	static_cast <Play*> (juego->topEstado())->newDisparoEnemigo(rect.x, rect.y, targetX, targetY, velDis);
}