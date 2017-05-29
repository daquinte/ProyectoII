#include "Play.h"
#include "ObjetoJuego.h"
#include "objetoDecorativo.h"
#include "GameOver.h"
#include "Player.h"
#include "BalaPlayer.h"
#include "BalaEnemigo.h"
#include "enemigoGuardia.h"

#include "BossRino.h"
#include "Spider.h"

#include "EnemigoPlanta.h"
#include <iostream>

#include "BarraVida.h"
#include "BarraVidaVacia.h"
#include "Cargador.h"
#include "EnergiaDisponible.h"
#include "Checkpoint.h"
#include "EnemigoPlanta.h"
#include "Dialogo.h"
#include "Aura.h"
#include "Botiquin.h"
#include "Bobina.h"
#include "EnemigoBomba.h"

#include "Key.h"
#include "Puerta.h"

#include <time.h>
using namespace std;

Play::Play(Juego* ptr) : Estado(ptr)
{
	type = NIVEL_1;

	init();
}

Play::~Play()
{
	for (int i = 0; i < musicFiles.size(); i++){
		delete musicFiles[i];
	}
}

void Play::init() {
	SDL_PollEvent(NULL);
	//TUTORIAL
	juego->arrayObjetos.push_back(new Aura(juego, 200, 350, 400, 50, "Para moverte, utiliza WASD"));
	juego->arrayObjetos.push_back(new Aura(juego, 1450, 300, 440, 50, "Click izquierdo para disparar"));
	juego->arrayObjetos.push_back(new Aura(juego, 450, 1090, 460, 50, "Necesitas una llave para pasar"));
	juego->arrayObjetos.push_back(new Aura(juego, 980, 1090, 400, 50, "SPACE para hacer dash"));

	//MUSICA//
	musicNames.push_back("..\\bmps\\city.mp3");
	musicNames.push_back("..\\bmps\\synd.mp3");
	musicNames.push_back("..\\bmps\\DieHistoric.mp3");

	for (int j = 0; j < musicNames.size(); j++) {
		cancion = new Musica();
		cancion->load(musicNames[j]);
		musicFiles.push_back(cancion);
	}

	//La cancion del nivel es aleatoria
	srand(time(NULL));
	int rnd = rand() % musicFiles.size();
	musicFiles[rnd]->play();

	///		PUSH DE OBJETOS DECORATIVOS		///
	//Los pusheamos antes para que el jugador pase por delante de los objetos
	juego->arrayObjetos.push_back(new objetoDecorativo(juego, 450, 110, "MesaRota2"));
	juego->arrayObjetos.push_back(new objetoDecorativo(juego, 520, 110, "MesaRota"));
	juego->arrayObjetos.push_back(new objetoDecorativo(juego, 590, 110, "MesaPeque"));
	juego->arrayObjetos.push_back(new objetoDecorativo(juego, 660, 110, "MesaCorazon"));
	juego->arrayObjetos.push_back(new objetoDecorativo(juego, 800, 50, "VitrinaLib"));
	juego->arrayObjetos.push_back(new objetoDecorativo(juego, 900, 50, "VitrinaFeto"));

	juego->arrayObjetos.push_back(new objetoDecorativo(juego, 350, 420, "MesaRota"));
	juego->arrayObjetos.push_back(new objetoDecorativo(juego, 420, 420, "MesaTentaculo"));
	juego->arrayObjetos.push_back(new objetoDecorativo(juego, 490, 420, "MesaPeque"));
	juego->arrayObjetos.push_back(new objetoDecorativo(juego, 560, 420, "MesaPeque"));
	juego->arrayObjetos.push_back(new objetoDecorativo(juego, 900, 350, "Planta3"));
	juego->arrayObjetos.push_back(new objetoDecorativo(juego, 1520, 570, "Cafetera"));

	//Sala 1
	juego->arrayObjetos.push_back(new objetoDecorativo(juego, 2100, 370, "Hojas"));
	juego->arrayObjetos.push_back(new objetoDecorativo(juego, 1800, 130, "VitrinaLib"));
	juego->arrayObjetos.push_back(new objetoDecorativo(juego, 1880, 130, "VitrinaLib"));
	juego->arrayObjetos.push_back(new objetoDecorativo(juego, 1960, 130, "VitrinaFeto"));
	juego->arrayObjetos.push_back(new objetoDecorativo(juego, 2040, 130, "VitrinaLib"));
	juego->arrayObjetos.push_back(new objetoDecorativo(juego, 2300, 180, "MesaTentaculo"));
	juego->arrayObjetos.push_back(new objetoDecorativo(juego, 2365, 180, "MesaCorazon"));
	juego->arrayObjetos.push_back(new objetoDecorativo(juego, 2035, 320, "MesaDoble"));
	juego->arrayObjetos.push_back(new objetoDecorativo(juego, 2035, 490, "MesaDoble"));
	juego->arrayObjetos.push_back(new objetoDecorativo(juego, 1800, 500, "Planta2"));
	juego->arrayObjetos.push_back(new objetoDecorativo(juego, 2080, 380, "papelera3"));

	//Sala 2
	juego->arrayObjetos.push_back(new objetoDecorativo(juego, 1900, 1060, "Hojas"));
	juego->arrayObjetos.push_back(new objetoDecorativo(juego, 2130, 1270, "Hojas"));
	juego->arrayObjetos.push_back(new objetoDecorativo(juego, 2200, 900, "Hojas"));
	juego->arrayObjetos.push_back(new objetoDecorativo(juego, 1850, 850, "VitrinaFeto"));
	juego->arrayObjetos.push_back(new objetoDecorativo(juego, 1930, 850, "VitrinaLib"));
	juego->arrayObjetos.push_back(new objetoDecorativo(juego, 2010, 850, "VitrinaFeto"));
	juego->arrayObjetos.push_back(new objetoDecorativo(juego, 2190, 980, "papelera3"));
	juego->arrayObjetos.push_back(new objetoDecorativo(juego, 2000, 1060, "MesaTentaculo"));
	juego->arrayObjetos.push_back(new objetoDecorativo(juego, 2065, 1060, "MesaPeque"));
	juego->arrayObjetos.push_back(new objetoDecorativo(juego, 2130, 1060, "MesaRota"));
	juego->arrayObjetos.push_back(new objetoDecorativo(juego, 2250, 1150, "Planta1"));
	juego->arrayObjetos.push_back(new objetoDecorativo(juego, 2290, 1210, "Planta3"));
	juego->arrayObjetos.push_back(new objetoDecorativo(juego, 1800, 1180, "VitrinaFeto"));
	juego->arrayObjetos.push_back(new objetoDecorativo(juego, 1880, 1180, "VitrinaLib"));

	//Pasillos
	juego->arrayObjetos.push_back(new objetoDecorativo(juego, 360, 1380, "MesaPeque"));
	juego->arrayObjetos.push_back(new objetoDecorativo(juego, 425, 1380, "MesaRota"));
	juego->arrayObjetos.push_back(new objetoDecorativo(juego, 300, 1000, "VitrinaFeto"));
	juego->arrayObjetos.push_back(new objetoDecorativo(juego, 125, 2360, "VitrinaFeto"));
	juego->arrayObjetos.push_back(new objetoDecorativo(juego, 220, 2360, "Cafetera"));

	juego->arrayObjetos.push_back(new objetoDecorativo(juego, 180, 1300, "BancoDcha"));
	juego->arrayObjetos.push_back(new objetoDecorativo(juego, 1250, 180, "BancoArriba"));
	juego->arrayObjetos.push_back(new objetoDecorativo(juego, 1395, 840, "BancoDcha"));
	juego->arrayObjetos.push_back(new objetoDecorativo(juego, 825, 3300, "BancoDcha"));
	juego->arrayObjetos.push_back(new objetoDecorativo(juego, 550, 2600, "BancoIzda"));

	juego->arrayObjetos.push_back(new objetoDecorativo(juego, 670, 2970, "MesaRota"));
	juego->arrayObjetos.push_back(new objetoDecorativo(juego, 735, 2970, "MesaTentaculo"));
	juego->arrayObjetos.push_back(new objetoDecorativo(juego, 860, 3150, "Planta3"));

	juego->arrayObjetos.push_back(new objetoDecorativo(juego, 1100, 4640, "Cafetera"));

	//Sala 5
	juego->arrayObjetos.push_back(new objetoDecorativo(juego, 1000, 1560, "Hojas"));
	juego->arrayObjetos.push_back(new objetoDecorativo(juego, 1200, 1660, "Hojas"));
	juego->arrayObjetos.push_back(new objetoDecorativo(juego, 890, 1340, "VitrinaFeto"));
	juego->arrayObjetos.push_back(new objetoDecorativo(juego, 975, 1340, "VitrinaFeto"));
	juego->arrayObjetos.push_back(new objetoDecorativo(juego, 1200, 1560, "Planta2"));	

	//Sala 6
	juego->arrayObjetos.push_back(new objetoDecorativo(juego, 935, 2600, "Hojas"));
	juego->arrayObjetos.push_back(new objetoDecorativo(juego, 1560, 2430, "VitrinaFeto"));
	juego->arrayObjetos.push_back(new objetoDecorativo(juego, 1640, 2430, "VitrinaLib"));
	juego->arrayObjetos.push_back(new objetoDecorativo(juego, 1450, 2800, "MesaDoble"));

	//Sala 7	
	juego->arrayObjetos.push_back(new objetoDecorativo(juego, 380, 3550, "Hojas"));
	juego->arrayObjetos.push_back(new objetoDecorativo(juego, 380, 3750, "Planta3"));

	//Sala 8
	juego->arrayObjetos.push_back(new objetoDecorativo(juego, 210, 5730, "Hojas"));
	juego->arrayObjetos.push_back(new objetoDecorativo(juego, 145, 5500, "VitrinaFeto"));
	juego->arrayObjetos.push_back(new objetoDecorativo(juego, 405, 5500, "VitrinaLib"));

	juego->arrayObjetos.push_back(new objetoDecorativo(juego, 140, 4900, "Planta3"));

	//Sala 9
	juego->arrayObjetos.push_back(new objetoDecorativo(juego, 1700, 5340, "Servers"));
	juego->arrayObjetos.push_back(new objetoDecorativo(juego, 1850, 5340, "Servers"));
	juego->arrayObjetos.push_back(new objetoDecorativo(juego, 1950, 5560, "Hojas"));
	juego->arrayObjetos.push_back(new objetoDecorativo(juego, 2180, 5530, "MesaRota2"));
	juego->arrayObjetos.push_back(new objetoDecorativo(juego, 2245, 5530, "MesaRota"));
	juego->arrayObjetos.push_back(new objetoDecorativo(juego, 1670, 5700, "Planta2"));

	//Humo
	juego->arrayObjetos.push_back(new objetoDecorativo(juego, -50, -200, "Humo"));
	juego->arrayObjetos.push_back(new objetoDecorativo(juego, 0, 1200, "Humo"));

	//Random
	juego->arrayObjetos.push_back(new objetoDecorativo(juego, 1470, 2600, "Hojas"));
	juego->arrayObjetos.push_back(new objetoDecorativo(juego, 1100, 3670, "Hojas"));
	juego->arrayObjetos.push_back(new objetoDecorativo(juego, 480, 3400, "VitrinaFeto"));
	juego->arrayObjetos.push_back(new objetoDecorativo(juego, 1385, 4800, "BancoIzda"));
	juego->arrayObjetos.push_back(new objetoDecorativo(juego, 570, 4140, "mesaEE"));
	juego->arrayObjetos.push_back(new objetoDecorativo(juego, 450, 4450, "Caja"));
	juego->arrayObjetos.push_back(new objetoDecorativo(juego, 1240, 3570, "Caja"));
	juego->arrayObjetos.push_back(new objetoDecorativo(juego, 330, 2960, "Servers"));

	juego->arrayObjetos.push_back(new Checkpoint(juego, 1100, 5650));

	//LLAVES Y PUERTAS
	//1
	juego->arrayObjetos.push_back(new Key(juego, 2050, 1200));
	juego->arrayObjetos.push_back(new Puerta(juego, 150, 1250, 600, 200));
	//2
	//Llave en la ara�a
	juego->arrayObjetos.push_back(new Puerta(juego, 1200, 2350, 150, 150));
	//3
	juego->arrayObjetos.push_back(new Key(juego, 595, 4360));
	juego->arrayObjetos.push_back(new Puerta(juego, 700, 5360, 150, 150));

	///		*PLAYER		///
	if (juego->getCheck()){
		juego->player = new Player(juego, 1100, 5650);
		//juego->player = new Player(juego, 570, 6700);

		juego->arrayObjetos.push_back(juego->player);
	}
	else{
		//juego->player = new Player(juego, 200, 300);
		juego->player = new Player(juego, 2000, 6700);
		juego->arrayObjetos.push_back(juego->player);
	}

					///      BOBINA     ///
	juego->arrayObjetos.push_back(new Bobina(juego, 570, 6425));
	juego->arrayObjetos.push_back(new Bobina(juego, 1260, 6425));
	juego->arrayObjetos.push_back(new Bobina(juego, 570, 6975));
	juego->arrayObjetos.push_back(new Bobina(juego, 1260, 6975));

					///       BOSS      ///
	juego->arrayObjetos.push_back(new BossRino(juego, 570, 6700));

					///		ENEMIGOS	///
	
	//ENEMIGOS GUARDIA
	juego->arrayObjetos.push_back(new enemigoGuardia(juego, 1260, 1750));
	juego->arrayObjetos.push_back(new enemigoGuardia(juego, 430, 2300));
	juego->arrayObjetos.push_back(new enemigoGuardia(juego, 380, 3690));

	//ENEMIGOS PLANTA
	juego->arrayObjetos.push_back(new EnemigoPlanta(juego, 1350, 1150));
	juego->arrayObjetos.push_back(new EnemigoPlanta(juego, 580, 1150));
	juego->arrayObjetos.push_back(new EnemigoPlanta(juego, 320, 1800));
	juego->arrayObjetos.push_back(new EnemigoPlanta(juego, 1220, 2700));
	juego->arrayObjetos.push_back(new EnemigoPlanta(juego, 350, 3500));
	juego->arrayObjetos.push_back(new EnemigoPlanta(juego, 600, 5250));
	juego->arrayObjetos.push_back(new EnemigoPlanta(juego, 1260, 1500));
	juego->arrayObjetos.push_back(new EnemigoPlanta(juego, 1350, 3100));
	juego->arrayObjetos.push_back(new EnemigoPlanta(juego, 1680, 3100));

	//ENEMIGOS BOMBA
	juego->arrayObjetos.push_back(new EnemigoBomba(juego, 2020, 6500));

	//ENEMIGOS ARA�A
	juego->arrayObjetos.push_back(new Spider(juego, 320, 2600, true)); //LLAVE

					///		INTERFAZ	///	
	juego->elemInterfaz.push_back(new BarraVidaVacia(juego, juego->player, 128, 32, 0, 0));
	juego->elemInterfaz.push_back(new BarraVida(juego, juego->player, 32, 32, 0, 0));
	juego->elemInterfaz.push_back(new Cargador(juego, juego->player, 75, 75, juego->SCREEN_WIDTH - 75, juego->SCREEN_HEIGHT - 85));
	juego->elemInterfaz.push_back(new EnergiaDisponible(juego, juego->player, 32, 32, 0, 0));

}

void Play::update(double delta) {
	
	
	for (auto i : juego->arrayObjetos) {
		if (!i->isInside())
			juego->addToScreen(i);
		else if (i->isInside() && !juego->isInScreen(i->getRect()))
			i->putInside(false);
	}

	//COLISIONES CON OBJETOS
	for (int i = 0; i < juego->objVisible.size(); ++i) {
		for (int j = 0; j < juego->objVisible.size(); ++j) {
			if (juego->checkCollision(juego->objVisible[i], juego->objVisible[j])) {
				juego->objVisible[i]->onCollision(juego->objVisible[j]->getType());
				juego->objVisible[j]->onCollision(juego->objVisible[i]->getType());
			}
		}
	}

	//cout << juego->objVisible.size() << "\n";
	/*
	for (auto obj1 : juego->arrayObjetos) {
	for (auto obj2 : juego->arrayObjetos) {
	if (juego->checkCollision(obj1, obj2)) {
	obj1->onCollision(obj2->getType());
	obj2->onCollision(obj1->getType());
	}
	}

	}
	*/

	///REVISAR
	/*
	for (auto obj1 : juego->arrayObjetos) {
	for (auto obj2 : juego->arrayObjetos) {
	if (juego->checkCollision(obj1, obj2)) {
	obj1->onCollision(obj2->getType());
	obj2->onCollision(obj1->getType());
	}
	}

	}

	for (auto enemy : juego->enemyArray) {
	if (juego->checkCollision(enemy, juego->player)) {
	enemy->onCollision(juego->player->getType());
	juego->player->onCollision(enemy->getType());
	}

	}

	for (auto bullet : juego->enemyBullets) {
	if (juego->checkCollision(bullet, juego->player)) {
	bullet->onCollision(juego->player->getType());
	juego->player->onCollision(bullet->getType());
	}
	for (auto enemyb : juego->enemyBullets) {
	if (juego->checkCollision(enemyb, bullet)) {
	enemyb->onCollision(bullet->getType());
	bullet->onCollision(enemyb->getType());
	}

	}

	}

	*/
	/*
	for (auto bullet : juego->playerBullets) {

	if (juego->checkCollision(juego->player, bullet)) {
	juego->player->onCollision(bullet->getType());
	bullet->onCollision(juego->player->getType());
	}

	for (auto enemy : juego->arrayObjetos) {
	if (juego->checkCollision(enemy, bullet)) {
	enemy->onCollision(bullet->getType());
	bullet->onCollision(enemy->getType());
	}
	}

	}
	*/


	/*
	//PERSONAJE CON ENEMIGOS
	for (int i = 1; i < juego->arrayObjetos.size(); ++i){
	if (!juego->player->isDead() && juego->checkCollision(juego->player, juego->arrayObjetos[i])){
	juego->player->onCollision(juego->arrayObjetos[i]-> getType());
	juego->arrayObjetos[i]->onCollision(juego->player->getType());
	}
	}


	for (auto i : juego->arrayObjetos) // access by value, the type of i is int
	std::cout << i << ' ';
	std::cout << '\n';


	//PERSONAJE CON BALAS ENEMIGAS
	for (int i = 0; i < juego->enemyBullets.size(); ++i) {
	if (!juego->player->isDead() && juego->checkCollision(juego->player, juego->enemyBullets[i])) {
	juego->player->onCollision(juego->enemyBullets[i]->getType());
	juego->enemyBullets[i]->onCollision(juego->player->getType());
	}
	}

	//BALAS CON ENEMIGOS
	for (int i = 0; i < juego->playerBullets.size(); ++i) {
	for (int j = 1; j < juego->arrayObjetos.size(); ++j) {
	if (!juego->playerBullets[i]->isDead() && juego->checkCollision(juego->playerBullets[i], juego->arrayObjetos[j])) {
	juego->playerBullets[i]->onCollision(juego->arrayObjetos[j]->getType());
	juego->arrayObjetos[j]->onCollision(juego->playerBullets[i]->getType());
	}
	}
	}


	*/

	if (juego->player->isDead()){		
		juego->estado->changeCurrentState(GAME_OVER);
	}

	else {
		//LIMPIEZA DE VECTOR DE OBJETOS
		for (int aux = 0; aux < juego->arrayObjetos.size(); ++aux) {
			if (juego->arrayObjetos[aux]->isDead())
				juego->arrayObjetos.erase(juego->arrayObjetos.begin() + aux);
		}
		for (int aux2 = 0; aux2 < juego->playerBullets.size(); ++aux2) {
			if (juego->playerBullets[aux2]->isDead())
				juego->playerBullets.erase(juego->playerBullets.begin() + aux2);
		}
		for (int aux3 = 0; aux3 < juego->enemyBullets.size(); ++aux3) {
			if (juego->enemyBullets[aux3]->isDead())
				juego->enemyBullets.erase(juego->enemyBullets.begin() + aux3);
		}
		for (int aux4 = 0; aux4 < juego->objVisible.size(); ++aux4) {
			if (!juego->isInScreen(juego->objVisible[aux4]->getRect()) || juego->objVisible[aux4]->isDead())
				juego->objVisible.erase(juego->objVisible.begin() + aux4);
		}
	}
		//UPDATE
		for (int i = 0; i < juego->arrayObjetos.size(); ++i) {
			juego->arrayObjetos[i]->update(delta);
		}
		/*for (int x = 0; x < juego->playerBullets.size(); ++x) {
			juego->playerBullets[x]->update(delta);

		for (int i = 0; i < juego->elemInterfaz.size(); i++){
			juego->elemInterfaz[i]->update(); //
		}
		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	}

	//UPDATE
	for (int i = 0; i < juego->arrayObjetos.size(); ++i) {
		juego->arrayObjetos[i]->update(delta);
	}
	/*for (int x = 0; x < juego->playerBullets.size(); ++x) {
	juego->playerBullets[x]->update(delta);
	}
	for (int x = 0; x < juego->enemyBullets.size(); ++x) {
	juego->enemyBullets[x]->update(delta);
	}*/

	for (int i = 0; i < juego->elemInterfaz.size(); i++){
		juego->elemInterfaz[i]->update(); 
	}
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//}
	
}


void Play::draw()
{
	//Limpia el buffer
	//SDL_RenderClear(pRenderer);
	SDL_SetRenderDrawColor(pRenderer, 0xFF, 0xFF, 0xFF, 0xFF);

	//Dibuja los objetos

	for (int aux = 0; aux < juego->arrayObjetos.size(); ++aux) {
		juego->arrayObjetos[aux]->draw();
	}
	for (int aux2 = 0; aux2 < juego->playerBullets.size(); ++aux2) {
		juego->playerBullets[aux2]->draw();
	}
	for (int aux3 = 0; aux3 < juego->enemyBullets.size(); ++aux3) {
		juego->enemyBullets[aux3]->draw();
	}

	//Dibuja interfaz, por encima de los objetos
	for (int i = 0; i < juego->elemInterfaz.size(); i++) {
		juego->elemInterfaz[i]->draw();
	}
	/*
	//Pintado de texto (cargador)
	if (juego->stats[2] > 0 && !juego->player->isDead()){
	fuenteCargador->load(juego->getTexto(1), 18);
	mensaje->loadFromText(pRenderer, to_string(juego->stats[2]), *fuenteCargador, Black);
	if (juego->stats[2] < 10){
	mensaje->render(pRenderer, juego->SCREEN_WIDTH - 44, juego->SCREEN_HEIGHT - 50);
	}
	else{ mensaje->render(pRenderer, juego->SCREEN_WIDTH - 54, juego->SCREEN_HEIGHT - 50); }
	}
	else{
	fuenteCargador->load(juego->getTexto(1), 18);
	mensaje->loadFromText(pRenderer, "Recargando", *fuenteCargador, Red);
	mensaje->render(pRenderer, ((juego->SCREEN_WIDTH / 2) - 100), ((juego->SCREEN_HEIGHT / 2) - 100));
	}
	*/

	SDL_RenderPresent(pRenderer);
}


void Play::newDisparo(ObjetoJuego * po, int posX, int posY) {

	//posiciones del rat�n
	int mX, mY;
	juego->getMousePos(mX, mY);

	int distance = sqrt((mX - posX)*(mX - posX) + (mY - posY)*(mY - posY));

	int vX = 75 * (mX - posX) / distance;
	int vY = 75 * (mY - posY) / distance;

	//Disparo
	juego->playerBullets.push_back(new BalaPlayer(juego, posX, posY, vX, vY));
}
/*
void Play::posPlayer(int& x, int& y) {
	static_cast <Player*>(juego->player)->getPos(x, y);
}*/

void Play::newDisparoEnemigo(int posEx, int posEy, int targetX, int targetY, int velDis) {
	//desde donde dispara //hacia donde dispara     //velocidad disparo


	int distance = sqrt((targetX - posEx)*(targetX - posEx) + (targetY - posEy)*(targetY - posEy));

	if (distance == 0) //He puesto esto para que no salga la excepci�n de que divide entre 0
		distance = 5;

	int vX = velDis * (targetX - posEx) / distance;
	int vY = velDis * (targetY - posEy) / distance;

	if (vX == 0 && vY == 0){ // Para que con lo de antes no se quede la bala flotando
		vX = vY = 10; // Si se hace lo de que al tocar al jugador haga da�o y te empuje un poco igual no hace falta
	}

	//float vX = velDis * (targetX - posEx) / distance + 0.01; //Arreglad esto para que no se haga 0
	//float vY = velDis * (targetY - posEy) / distance + 0.01;

	//Disparo
	juego->enemyBullets.push_back(new BalaEnemigo(juego, posEx, posEy, vX, vY));
}
