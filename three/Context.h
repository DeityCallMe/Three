#ifndef _CONTEXT_H
#define _CONTEXT_H
#include "BaseGame.h"
#include "State.h"
#include "Graphic.h"



#define MAXLIST 100

#define REMOVE 0
#define SAVE 1
class State;
class Context
	:BaseGame
{
public:	

	static Context* InitializeContext(State* state=0,Graphic* graphic=0);
	int changeState(State* change,UINT flag=REMOVE);
	void Render(int,Graphic*);
	void Clearup();
	int pushState(State*);
	int popState(State**);
	State* GetState();

private:
	Context(State*,Graphic*);
	~Context();

	static Context* soleContext;
	State*  state;
	int m_last;
	State* m_stateList[MAXLIST];
};
#endif