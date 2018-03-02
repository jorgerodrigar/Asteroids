#include "StarWarsBulletsManager.h"

//recoge la primera bala inactiva del vector o crea una nueva (metodo getBullet),
//la activa y le pone pos y vel
void StarWarsBulletsManager::shoot(Vector2D p, Vector2D v) {
	Bullet* bullet = getBullet();
	bullet->setActive(true);
	bullet->setPosition(p);
	bullet->setVelocity(v);
}

//actualiza todas las balas que esten activas y desactiva las que salen de la pantalla
void StarWarsBulletsManager::update(Uint32 time) {
	for (int i = 0; i < bullets.size(); i++) 
		if (bullets[i]->getActive()) {
			bullets[i]->update(time);
			if ((bullets[i]->getPosition().getX() < 0 || bullets[i]->getPosition().getX() >= game_->getWindowWidth()) ||
				(bullets[i]->getPosition().getY() < 0 || bullets[i]->getPosition().getY() >= game_->getWindowHeight()))
				bullets[i]->setActive(false);
		}
}

//devuelve la primera bala inactiva del vector y si no hay crea una nueva y la devuelve
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

//recibe distintos tipos de mensaje
void StarWarsBulletsManager::receive(Message* msg) {
	switch (msg->id_) {
	case ROUND_START://si la ronda empieza o acaba pone todas las balas a inactivo
		for (int i = 0; i < bullets.size(); i++)bullets[i]->setActive(false);
		break;
	case ROUND_OVER:
		for (int i = 0; i < bullets.size(); i++)bullets[i]->setActive(false);
		break;
	case BULLET_ASTROID_COLLISION://cuando choca con un asteroide o una nave pone esa bala a inactivo
		break;
	case BULLET_FIGHTER_COLLISION:
		break;
	case FIGHTER_SHOOT://cuando se manda disparar (desde el componente GunInput) se cogen la pos y la vel del jugador
		Vector2D position = { player->getPosition().getX() + player->getWidth() / 2, player->getPosition().getY() + player->getHeight() / 2 };
		Vector2D direction(-player->getDirection().getX(), player->getDirection().getY());
		position = position + direction*(player->getHeight() / 2);
		double velocity = std::max(player->getVelocity().magnitude() * 7, 2.0);
		shoot(position, direction*velocity);//y se llama al metodo shoot con ellas
		break;
	}
}