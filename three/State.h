#ifndef _STATE_H
#define _STATE_H
#include "Graphic.h"
#include "Context.h"
#include "GameManager.h"
#include "BackgroundAnimation.h"
#include "SettingGUI.h"
#include "ImmediateData.h"
#include "DInput.h"
#include <math.h>



class Context;
class BackgroundAnimation;
class State
{
public:
	State();
	virtual ~State();
	virtual void console(BYTE*,UINT)=0;
	virtual void frame(Context*,int,Graphic*)=0;
};
class MainState
	:public  State
{
public:
	MainState(Graphic*);
	virtual ~MainState();
protected:
	UINT m_LastClickTime;

	void GeneralConsole(BYTE*,UINT);
	void GeneralRender(Context*,int,Graphic*);
	void upFra(UINT,UINT);
	void downFra(UINT);
	UINT getDigit(UINT);
	static ImmediateData* data;
	static BackgroundAnimation* _background;
};
class StateBegin
	:public MainState
{
public:
	StateBegin(Graphic*);
	~StateBegin();
	void console(BYTE*,UINT);
	void frame(Context*,int, Graphic*);
private:

	int elapseTime;
};
//
class StateBetDown
	:public MainState
{
public:
	StateBetDown(Graphic*);
	~StateBetDown();
	void console(BYTE*,UINT);
	void frame(Context*,int, Graphic*);
private:
	int elapseTime;

};
//
class StateView
	:public MainState
{
public:
	StateView(Graphic*);
	~StateView();
	void console(BYTE*,UINT);
	void frame(Context*,int, Graphic*);
private:
	int elapseTime;
};
class StateSetting
	:public State
{
public:
	StateSetting(Graphic*);
	~StateSetting();
	void console(BYTE*,UINT);
	void frame(Context*,int, Graphic*);
	void exitSetting();
private:
	SettingGUI* m_gui;
	int elapseTime;
};
#endif