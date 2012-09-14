#ifndef _GAMEMANAGER_H
#define _GAMEMANAGER_H
#include <Windows.h>
#include "Graphic.h"
#include "BackgroundAnimation.h"
#include "Context.h"
#include "ImmediateData.h"
#include "SerialPort.h" 
#include "SettingGUI.h"
#include "DInput.h"
#include "GUI.h"
#include "Sound.h"
#include <tchar.h>
#include <time.h>


class Context;
class BackgroundAnimation;
class GameManager
{
public:
	~GameManager();
	void Frame();
	void mouseEnters();
	void mouseLeaves();
	bool winProc( HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam ); 


	static GameManager*	initManager(HWND);
	static Graphic* GetGraphic();
	static GameManager* GetGame();
	static void DataReceived(SerialPort*);



	void bet(UINT,UINT);
	void change(UINT);
	void clearBet(UINT);
	void upFra(UINT,UINT);
private:
	GameManager(HWND h);
	void Initialize();
	HWND       hWnd;
	DWORD   tPre,tNow;
	Graphic* pGraphic;
	bool d_mouseInWindow;

	CRITICAL_SECTION  g_csThreadCode;  

	SerialPort m_SerialPort;

	static GameManager* gameManager;
};
#endif