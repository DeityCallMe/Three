#ifndef _BASEGAME_H
#define _BASEGAME_H
#include "Graphic.h"


class BaseGame
{
public:
	BaseGame(Graphic*);
	virtual ~BaseGame();
	virtual void Render(int,Graphic*)=0;
	//virtual void Clearup()=0;
private:
	Graphic* bGraphic;
};
#endif