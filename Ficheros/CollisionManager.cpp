﻿#include "CollisionManager.h"

void CollisionManager::update(Uint32 time) {
	vector<Bullet*> bullets = bulletsManager_->getBullets();
	vector<Asteroid*> astroids = astroidsManager_->getAstroids();
	Fighter* fighter = ﬁghtersManager_->getFighter();

	//colisiones entre nave y asteroides
	for (int i = 0; i < astroids.size(); i++) {
		if (Collisions::collides(fighter, astroids[i])) {
			AstroidFighterCollision msg = { astroids[i], fighter };
			send(msg);
		}
	}

	//colisiones entre balas y asteroides
	bool balaChocada = false;
	int j = 0;
	for (int i = 0; i < bullets.size(); i++) {
		j = 0;
		while (j < astroids.size() && !balaChocada) {
			if (Collisions::collides(bullets[i], astroids[j])) {
				BulletAstroidCollision msg = { bullets[i], astroids[j] };
				send(msg);
				balaChocada = true;
			}
			else j++;
		}
	}
}
