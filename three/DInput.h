#ifndef _DINPUT_H
#define _DINPUT_H
#include <dinput.h>


#pragma comment(lib, "DInput8.lib")
#pragma comment(lib,"dxguid.lib")
class DInput
{
public:
	static DInput* InitializeDInput(HWND hwnd=0);
	static void ReleaseDInput();
	LPDIRECTINPUT8 m_directInput;
	LPDIRECTINPUTDEVICE8 m_keyboardDevice ;
	LPDIRECTINPUTDEVICE8 m_mouseDevice ;
	bool Nexclusive();
	bool NoNexclusive();
private:
	DInput();
	~DInput();
	HWND w;
	bool initialize(HWND);
	static DInput* soleDInput;
	bool m_isNexclusive;
};
#endif