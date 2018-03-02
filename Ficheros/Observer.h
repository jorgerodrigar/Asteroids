#ifndef OBSERVER_H_
#define OBSERVER_H_

#include "GameObject.h"
#include "Messages.h"

//recibe mensajes
class Observer {
public:
	Observer();
	virtual ~Observer();
	virtual void receive(Message* msg) = 0;
};

#endif /* OBSERVER_H_ */
