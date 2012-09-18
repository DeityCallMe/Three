#ifndef _CONTEXT_H
#define _CONTEXT_H
#include "BaseGame.h"
#include "State.h"
#include "Graphic.h"



#define MAXLIST 10

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

	void ClearState();
private:
	Context(State*,Graphic*);
	~Context();
	bool Rending;
	static Context* soleContext;
	State*  state;
	int m_last;
	int m_clearLast;
	State* m_stateList[MAXLIST];
	State* m_beClearList[MAXLIST];
};
#endif