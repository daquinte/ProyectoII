#include "EnemigoPlanta.h"


EnemigoPlanta::EnemigoPlanta(Juego* ptr, int px, int py) : enemy(ptr, px, py)
{
	textura = juego->getTextura(Juego::TEnemyPlanta); //TODO: cambiar a la textura de la planta
	vida = 5;
	rectAnim = { 0, 0, 32, 32 };
	contador = 0;

	rectCollision = rect;
}

void EnemigoPlanta::animacionBasica(){ //Para el paso de frames
	if (rectAnim.x >= 128){
		rectAnim.x = 0;
	}
	else {
		rectAnim.x += 32;
	}
}

EnemigoPlanta::~EnemigoPlanta()
{
}

void EnemigoPlanta::draw() const {
	textura->drawAnimacion(pRenderer, rect.x - juego->camera.x, rect.y - juego->camera.y, rect, rectAnim);
}
void EnemigoPlanta::update(int delta){
	contador += delta;
	if (contador >= 4){ //Paso de imagenes mas lento
		animacionBasica();
		contador = 0;
	}

	//int x, y;
	SDL_Rect aux_rect;
	aux_rect = juego->arrayObjetos[0]->getRect();
	//static_cast <Play*> (juego->topEstado())->posPlayer(x, y); << Hay que evitar los cast
	++contDis;
	if (contDis >= freDis){
		shoot(aux_rect.x, aux_rect.y);
		contDis = 0;
	}

	//rectCollision.x = (rect.x + rect.w / 3) * delta;
	//rectCollision.y = (rect.y + rect.h / 3) * delta;

	if (inmunidad) {
		if (contInm < 50) contInm++;
		else if (contInm == 50)
		{
			inmunidad = false;
			contInm = 0;
		}
	}
}

void EnemigoPlanta::onCollision() { //onCollision de gestor de vida

	gestorVida();
}

void EnemigoPlanta::gestorVida()
{
	if (!inmunidad) {
		vida--;
		cout << "Vida enemigo: " << vida << "\n";
		inmunidad = true;
	}

	if (vida <= 0) {
		cout << "Enemy Dead! \n";
		dead = true;
	}
}
