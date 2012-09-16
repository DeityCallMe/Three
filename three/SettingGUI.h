#ifndef _SETTINGGUI_H
#define _SETTINGGUI_H
#undef max
#undef min

#include "Sound.h"
#include <CEGUI.h>
#include <d3dx9.h>
#include "DInput.h"
#include <RendererModules\Direct3D9\CEGUIDirect3D9Renderer.h>
#if defined(_DEBUG)
#	if defined(CEGUI_STATIC)
#	   pragma comment(lib, "CEGUIDirect3D9Renderer_Static_d.lib")
#	else
#      pragma comment(lib, "CEGUIDirect3D9Renderer_d.lib")
#	   pragma comment(lib, "CEGUIBase_d.lib")
#	endif
#else
#	if defined(CEGUI_STATIC)
#	   pragma comment(lib, "CEGUIDirect3D9Renderer_Static.lib")
#	else
#      pragma comment(lib, "CEGUIDirect3D9Renderer.lib")
#	   pragma comment(lib, "CEGUIBase.lib")
#	endif
#endif
#include "ImmediateData.h"
#include <tchar.h>



class IGeneralCall {
 
public:
    virtual ~IGeneralCall() { }
    virtual void Invoke() = 0;
};
template<typename T>
class  GeneralCall
	:public IGeneralCall
{
public:
    GeneralCall(T* pT,void (T::*function)(void))
        : m_pT(pT), m_pFunc(function) { }
 
    void Invoke() 
	{
        (m_pT->*m_pFunc)();
    }
 
private:
    T* m_pT;
	//void (T::*m_pFunc)(int,Graphic*);
    void (T::*m_pFunc)(void);
};
//
class SettingGUI
{
public:
	SettingGUI(LPDIRECT3DDEVICE9);
	~SettingGUI();

	template<typename T>
	void onExitCall(void (T::*function)(void), T* obj)
	{
		gCall=new GeneralCall<T>(obj,function);
	}
private:
	IGeneralCall* gCall;
	


	void initEnter();
	void initSetting();
	bool setting(const CEGUI::EventArgs&);
	bool exit(const CEGUI::EventArgs&);
	

	bool RemoveMusic(const CEGUI::EventArgs&);
	bool AddMusic(const CEGUI::EventArgs&);

	void musicToList(TCHAR*);



	UINT m_nameConut;
	HANDLE m_thread;

	char buff[128];

	static void ToUTF8(TCHAR*,char*);
	static DWORD WINAPI CopyThread(LPVOID);
};
#endif