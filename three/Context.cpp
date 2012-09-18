#include "Context.h"

#include "Header.h"
Context* Context::soleContext=0;
Context::Context(State* s,Graphic* g)
	:BaseGame(g),state(s),m_clearLast(MAXLIST),m_last(MAXLIST)
{
	//m_last=MAXLIST;
}
Context::~Context()
{
	
}
Context* Context::InitializeContext(State* state,Graphic* graphic)
{
	if(state==0||graphic==0)
		goto ends;
	if(soleContext!=0)
		goto ends;

	soleContext=new Context(state,graphic);

ends:
	return soleContext;
}
State* Context::GetState()
{
	return state;
}
void Context::Render(int time,Graphic* graphic)
{
	Rending=true;
	state->frame(this,time,graphic);
	ClearState();
	Rending=false;
}
void Context::ClearState()
{
	while(m_clearLast<MAXLIST)
	{
		delete m_beClearList[m_clearLast];
		m_clearLast++;
	}
}
int Context::pushState(State* push)
{
	if(m_last>0)
	{
		m_last--;
		m_stateList[m_last]=push;
		return 1;
	}
	return 0;
}
int Context::popState(State** pop)
{
	if(m_last<MAXLIST)
	{
		*pop=m_stateList[m_last];
		m_last++;
		return 1;
	}
	return 0;
}
int Context::changeState(State* change,UINT flag)
{
	int ret;
	if(flag==SAVE)
	{
		ret=pushState(state);
	}
	else if(flag==REMOVE)
	{
		if(Rending)
		{
			m_clearLast--;
			m_beClearList[m_clearLast]=state;
		}
		else
			delete state;
		ret=1;
	}
	if(ret)
	{
		state=change;
	}
	return ret;
}
