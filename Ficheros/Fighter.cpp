#include "Fighter.h"

//inicializamos atributos y añadimos componentes
Fighter::Fighter(SDLGame* game, int id) : Container(game), id_(id){
	setWidth(53);
	setHeight(71);

	Vector2D dir(0, -1);
	setDirection(dir);
}