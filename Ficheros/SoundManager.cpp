#include "SoundManager.h"

//dependiendo del mensaje recibido reproducimos el efecto o musica correspondiente
void SoundManager::receive(Message* msg) {
	switch (msg->id_) {
	case BULLET_CREATED:
		game_->getResources()->getSoundEffect(Resources::GunShot)->play();
		break;
	case BULLET_ASTROID_COLLISION:
		game_->getResources()->getSoundEffect(Resources::Explosion)->play();
		break;
	case ASTROID_FIGHTER_COLLISION:
		game_->getResources()->getSoundEffect(Resources::Explosion)->play();
		break;
	case ROUND_START:
		game_->getResources()->getMusic(Resources::ImperialMarch)->play();
		break;
	case ROUND_OVER:
		game_->getResources()->getMusic(Resources::ImperialMarch)->pause();
		break;
	}
}
