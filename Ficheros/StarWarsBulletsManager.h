#pragma once
#include "BulletsManager.h"
#include "Bullet.h"
#include <algorithm>
#include "Fighter.h"
#include "Observer.h"
#include "checkML.h"

using namespace std;

//hereda de la clase abstracta BulletsManager, es un objeto de la escena que gestiona las balas
class StarWarsBulletsManager : public GameObject, public BulletsManager{
private:
	std::vector<Bullet*> bullets;//vector de balas en escena (activas o inactivas)
	RenderComponent* bulletRenderer_;//componentes que llevan todas las balas
	PhysicsComponent* bulletPhysics_;
	Fighter* player;//puntero a la nave jugador para obtener su vel y pos y darsela a las nuevas balas
	
	Bullet* getBullet();//devuelve la primera bala inactiva del vector y si no hay crea una nueva y la devuelve
	virtual void receive(Message* msg);//recibe mensajes
	virtual void shoot(Vector2D position, Vector2D velocity);//dispara una bala
public:
	StarWarsBulletsManager(SDLGame* game): GameObject(game) {
		bulletRenderer_ = new FillRectRenderer();//inicializamos todos los atributos
		bulletPhysics_ = new BasicMotionPhysics();
	}
	~StarWarsBulletsManager() {//borramos todas las balas
		for (int i = 0; i < bullets.size();i++) delete(bullets[i]);
	}

	//actualiza todas las balas que esten activas y desactiva las que salen de la pantalla
	virtual void update(Uint32 time);
	//pinta todas las balas que esten activas
	virtual void render(Uint32 time) { for (int i = 0; i < bullets.size(); i++)if (bullets[i]->getActive())bullets[i]->render(time); }
	virtual void handleInput(Uint32 time, const SDL_Event& event) {}//no hace nada

	virtual std::vector<Bullet*>& getBullets() { return bullets; }//devuelve el vector de balas

	void setPlayer(Fighter* f) { player = f; }
};

