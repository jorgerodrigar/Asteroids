#include "StarWarsBulletsManager.h"

void StarWarsBulletsManager::shoot(Vector2D p, Vector2D v) {
	Bullet* bullet = getBullet();
	bullet->setActive(true);
	bullet->setPosition(p);
	bullet->setVelocity(v);
}

void StarWarsBulletsManager::update(Uint32 time) {
	for (int i = 0; i < bullets.size(); i++) if(bullets[i]->getActive())bullets[i]->update(time);
}

void StarWarsBulletsManager::render(Uint32 time) {
	for (int i = 0; i < bullets.size(); i++)if (bullets[i]->getActive())bullets[i]->render(time);
}

Bullet* StarWarsBulletsManager::getBullet() {
	int i = 0;
	while (i < bullets.size() && bullets[i]->getActive())i++;

	if (i < bullets.size()) return bullets[i];
	else {
		Bullet* bullet = new Bullet(this->getGame());
		bullet->addRenderComponent(bulletRenderer_);
		bullet->addPhysicsComponent(bulletPhysics_);
		bullets.push_back(bullet);
		return bullets[bullets.size() - 1];
	}
}

void StarWarsBulletsManager::receive(Message* msg) {
	switch (msg->id_) {
	case ROUND_START:
		for (int i = 0; i < bullets.size(); i++)bullets[i]->setActive(false);
		break;
	case ROUND_OVER:
		for (int i = 0; i < bullets.size(); i++)bullets[i]->setActive(false);
		break;
	case BULLET_ASTROID_COLLISION:
		break;
	case BULLET_FIGHTER_COLLISION:
		break;
	case FIGHTER_SHOOT:
		Vector2D position = { player->getPosition().getX() + player->getWidth() / 2, player->getPosition().getY() + player->getHeight() / 2 };
		Vector2D direction(-player->getDirection().getX(), player->getDirection().getY());
		position = position + direction*(player->getHeight() / 2);
		double velocity = std::max(player->getVelocity().magnitude() * 7, 2.0);
		shoot(position, direction*velocity);
		break;
	}
}