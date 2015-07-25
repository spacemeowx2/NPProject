#ifndef POSOBJECT_H
#define POSOBJECT_H
class Game;

#include "baseobject.h"
class PosObject:
	public BaseObject
{
	public:
		PosObject(Game*);
		virtual ~PosObject();

};

#endif // POSOBJECT_H