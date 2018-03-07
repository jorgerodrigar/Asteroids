#include "AsteroidsManager.h"

void AstroidsManager::receive(Message* msg) {
	switch (msg->id_) {
	case BULLET_ASTROID_COLLISION:
		break;
	case ROUND_START:
		initAsteroids();
		break;
	};
}

Asteroid* AstroidsManager::getAstroid(){
	int i = 0;
	while (i < astroids_.size() && astroids_[i]->getActive())i++;

	if (i < astroids_.size()) return astroids_[i];
	else {
		Asteroid* asteroid = new Asteroid(game_);
		asteroid->addRenderComponent(astroidImage_);
		asteroid->addPhysicsComponent(circularPhysics_);
		asteroid->addPhysicsComponent(rotationPhysics_);
		astroids_.push_back(asteroid);
		return astroids_[astroids_.size() - 1];
	}
	numOfAstroids_++;
}

void AstroidsManager::initAsteroids(){

	for (int i = 0; i < astroids_.size(); i++){
		astroids_[i]->setActive(false);
	}
	for (int i = 0; i < 5; i++){
		Asteroid* a = getAstroid();
		astroids_.push_back(a);
		double randomPosX;
		double randomVelX = 0;
		double randomVelY = 0;
		while (randomVelX == 0 && randomVelY == 0)
		{
			randomVelX = (-rand() % 2) + (rand() % 2);
			randomVelY = (-rand() % 2) + (rand() % 2);
		}
		randomPosX = rand() % game_->getWindowWidth();
		a->setPosition(Vector2D(randomPosX, 5));
		a->setVelocity(Vector2D(randomVelX, randomVelY));
		a->setActive(true);
		numOfAstroids_++;
	}
}