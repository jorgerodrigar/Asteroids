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
		bullet->addRenderComponent(&bulletRenderer_);
		bullet->addPhysicsComponent(&bulletPhysics_);
		bullets.push_back(bullet);
		bullet = nullptr;
		return bullets[bullets.size() - 1];
	}
}

//recibe distintos tipos de mensaje
void StarWarsBulletsManager::receive(Message* msg) {
	if (msg->id_ == ROUND_START) //si la ronda empieza o acaba pone todas las balas a inactivo
		for (int i = 0; i < bullets.size(); i++)bullets[i]->setActive(false);
	else if (msg->id_ == ROUND_OVER)
		for (int i = 0; i < bullets.size(); i++)bullets[i]->setActive(false);

	else if (msg->id_ == BULLET_ASTROID_COLLISION) {//cuando choca con un asteroide o una nave pone esa bala a inactivo
		BulletAstroidCollision* m = static_cast<BulletAstroidCollision*>(msg);
		if(!super)m->bullet_->setActive(false);
	}
	else if (msg->id_ == BULLET_FIGHTER_COLLISION){
		BulletFighterCollision* m = static_cast<BulletFighterCollision*>(msg);
		m->bullet_->setActive(false);
	}

	else if (msg->id_ == FIGHTER_SHOOT) {//cuando se manda disparar (desde el componente GunInput) se cogen la pos y la vel del jugador

		int rotation = 360 / numBalas;
		rotation = asin(player->getDirection().getY());
		for (int i = 0; i < numBalas; i++) {
			Vector2D position = { player->getPosition().getX() + player->getWidth() / 2, player->getPosition().getY() + player->getHeight() / 2 };
 			Vector2D direction(sin(rotation*i*(M_PI/180)), -cos(rotation*i*M_PI / 180 + M_PI/2));
			position = position + direction*(player->getHeight() / 2);
			double velocity = std::max(player->getVelocity().magnitude() * 7, 2.0);
			shoot(position, direction*velocity);//y se llama al metodo shoot con ellas
			Message msg = { BULLET_CREATED };
			send(&msg); 
		}
	}
	else if (msg->id_ == SUPER_ON)super = true;
	else if (msg->id_ == SUPER_OFF)super = false;
	else if (msg->id_ == MULTI_ON)numBalas = 6;
	else if (msg->id_ == MULTI_OFF)numBalas = 1;
}