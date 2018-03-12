#include "AsteroidsManager.h"

void AstroidsManager::receive(Message* msg) {
	if (msg->id_ == BULLET_ASTROID_COLLISION) {
		BulletAstroidCollision* m = static_cast<BulletAstroidCollision*>(msg);
		m->astroid_->setActive(false);
		numOfAstroids_--;
		if (m->astroid_->getGenerations() > 0) {
			int randomNum = 2 + rand() % 5;
			for (int i = 0; i < randomNum; i++) {
				Asteroid* a = getAstroid();
				a->setGenerations(m->astroid_->getGenerations() - 1);
				a->setPosition(m->astroid_->getPosition());
				a->setVelocity(m->astroid_->getVelocity());
				a->setActive(true);
				numOfAstroids_++;
			}
		}
	}
	else if (msg->id_ == ROUND_START)initAsteroids();
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