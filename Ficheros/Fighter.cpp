#include "Fighter.h"

//inicializamos atributos y añadimos componentes
Fighter::Fighter(SDLGame* game, int id) : Container(game), id_(id){
	setWidth(40);//tamaño y direccion por defecto
	setHeight(55);

	Vector2D dir(0, -1);
	setDirection(dir);
}