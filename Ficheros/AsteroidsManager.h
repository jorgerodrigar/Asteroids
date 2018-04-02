#ifndef ASTEROIDMANAGER_H_
#define ASTEROIDMANAGER_H_
#include "GameObject.h"
#include "Observer.h"
#include "Observable.h"
#include "ImageRenderer.h"
#include "CircularMotionPhysics.h"
#include "RotationPhysics.h"
#include "checkML.h"

//gestor de asteroides
class AstroidsManager : public GameObject, public Observer, public Observable {
public:
	AstroidsManager(SDLGame* game) :GameObject(game){
		SDL_Rect rect;
		rect.x = 0;
		rect.y = 0;
		rect.w = 145;
		rect.h = 130;
		//componentes que tendran todos los asteroides
		astroidImage_ = new ImageRenderer(game->getResources()->getImageTexture(Resources::asteroid), rect);
		circularPhysics_ = new CircularMotionPhysics();
		rotationPhysics_ = new RotationPhysics(2.0);
		numOfAstroids_ = 0;
	}
	virtual ~AstroidsManager(){
		for (int i = 0; i < astroids_.size(); i++) delete(astroids_[i]);
	}
	virtual void handleInput(Uint32 time, const SDL_Event& event){}
	virtual void update(Uint32 time){ for (int i = 0; i < astroids_.size(); i++)if (astroids_[i]->getActive())astroids_[i]->update(time); }
	virtual void render(Uint32 time){ for (int i = 0; i < astroids_.size(); i++)if (astroids_[i]->getActive())astroids_[i]->render(time); }
	virtual vector<Asteroid*>& getAstroids(){ return astroids_; }
	virtual void receive(Message* msg);
private:
	Asteroid* getAstroid();
	void initAsteroids();

	vector<Asteroid*> astroids_;//vector de todos los asteroides del juego (activos e inactivos)
	RenderComponent* astroidImage_;
	PhysicsComponent* circularPhysics_;
	PhysicsComponent* rotationPhysics_;
	int numOfAstroids_, numAstroidsInicial = 5;
};

#endif /* ASTEROIDMANAGER_H_ */