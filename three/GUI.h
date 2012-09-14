#ifndef _GUI_H
#define _GUI_H

#undef max
#undef min

#include <CEGUI.h>
#include <d3dx9.h>
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


class GUI
{
public:
	static GUI* InitializeGUI(LPDIRECT3DDEVICE9 lp=0);
	void renderGUI();
private:
	GUI();
	~GUI();
	bool initialize(LPDIRECT3DDEVICE9);
	static GUI* soleGUI;
};



#endif