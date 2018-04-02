#include "AsteroidsManager.h"

//recibidor de mensajes
void AstroidsManager::receive(Message* msg) {
	if (msg->id_ == BULLET_ASTROID_COLLISION) {//si una bala y un asteroide han colisionado
		BulletAstroidCollision* m = static_cast<BulletAstroidCollision*>(msg);
		m->astroid_->setActive(false);//ponemos inactivo el asteroide
		numOfAstroids_--;
		if (m->astroid_->getGenerations() > 0) {//si aun tenia generaciones este se divide en 2 o 3 asteroides
			int randomNum = rand() % 4 + 2;
			for (int i = 0; i < randomNum; i++) {//para cada nuevo asteroide
				Asteroid* a = getAstroid();
				a->setGenerations(m->astroid_->getGenerations() - 1);
				a->setPosition(m->astroid_->getPosition());
				a->reduceTam();//con su misma posicion, generaciones de su padre menos 1 y mitad de tamaño
				int randomVelX = (rand() % 2);
				int randomVelY = (rand() % 2);
				if (randomVelX == 0)randomVelX = 1;
				else randomVelX = -1;
				if (randomVelY == 0)randomVelY = 1;
				else randomVelY = -1;//con la direccion cambiada, misma velocidad
				a->setVelocity(Vector2D(m->astroid_->getVelocity().getX()*randomVelX, m->astroid_->getVelocity().getY()*randomVelY));
				a->setActive(true);//lo activamos
				numOfAstroids_++;
			}
		}
		if (numOfAstroids_ == 0) {//si ya no quedan asteroides se manda el mensaje correspondiente
			Message msg = { NO_MORE_ATROIDS };
			send(&msg);
		}
	}
	else if (msg->id_ == ROUND_START)initAsteroids();//si empieza la ronda generamos los asteroides
}

//devuelve un asteroide inactivo y, en caso de no haberlo, crea uno nuevo y lo devuelve
Asteroid* AstroidsManager::getAstroid(){
	int i = 0;
	while (i < astroids_.size() && astroids_[i]->getActive())i++;

	//si hay un asteroide inactivo lo devolvemos
	if (i < astroids_.size()) return astroids_[i];
	else {//si no, creamos uno nuevo y lo devolvemos
		Asteroid* asteroid = new Asteroid(game_);
		asteroid->addRenderComponent(&astroidImage_);
		asteroid->addPhysicsComponent(&circularPhysics_);
		asteroid->addPhysicsComponent(&rotationPhysics_);
		astroids_.push_back(asteroid);
		asteroid = nullptr;
		return astroids_[astroids_.size() - 1];
	}
}

//instancia los asteroides iniciales, llmado al comienzo de cada ronda
void AstroidsManager::initAsteroids(){
	//desactivamos todos los que habia
	for (int i = 0; i < astroids_.size(); i++){
		astroids_[i]->setActive(false);
	}
	//para todos los asteroides iniciales
	for (int i = 0; i < numAstroidsInicial; i++){
		Asteroid* a = getAstroid();
		double randomPosX;
		double randomVelX = 0;
		double randomVelY = 0;
		while (randomVelX == 0 && randomVelY == 0)
		{
			randomVelX = (-rand() % 2) + (rand() % 2);
			randomVelY = (-rand() % 2) + (rand() % 2);
		}
		randomPosX = rand() % game_->getWindowWidth();
		a->setWidth(40);
		a->setHeight(40);
		a->setGenerations(2);
		a->setPosition(Vector2D(randomPosX, 5));
		a->setVelocity(Vector2D(randomVelX, randomVelY));
		a->setActive(true);//lo creamos con getAstroid, le damos posicion y velocidad aleatorias
		//y lo ponemos activo
	}
	numOfAstroids_ = numAstroidsInicial;
}