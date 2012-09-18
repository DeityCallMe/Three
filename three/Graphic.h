#ifndef _G_H
#define _G_H
#include "RenderDelegate.h"
#include <string>
#include <map>
#include <windows.h>
#include <d3dx9.h>




#define release_com(p)	do { if(p) { (p)->Release(); (p) = NULL; } } while(0)

using namespace std;
class RenderDelegate;
struct ImageInfo
{
	ImageInfo(float bx=0,float by=0,float wh=0,float ht=0,float z=0,float ux=0,float uy=0,float uw=0,float uh=0,LPDIRECT3DTEXTURE9 pT=0)
		:beginX(bx),beginY(by),width(wh),height(ht),Z(z),uvX(ux),uvY(uy),uvW(uw),uvH(uh),pTexture(pT)
	{

	}
	~ImageInfo()
	{

	}
	LPDIRECT3DTEXTURE9  pTexture;
	float beginX;
	float beginY;
	float width;
	float height;

	float Z;

	float uvX;
	float uvY;
	float uvW;
	float uvH;

};
struct CUSTOMVERTEX
{
	CUSTOMVERTEX()
	{
		x=0;
		y=0;
		z=0;
		tu=0;
		tv=0;
	}
	CUSTOMVERTEX(float ix,float iy,float iz,float itu,float itv)
		:x(ix),y(iy),z(iz),tu(itu),tv(itv)
	{

	}
	CUSTOMVERTEX(D3DXVECTOR3 iv,float itu,float itv)
		:x(iv.x),y(iv.y),z(iv.z),tu(itu),tv(itv)
	{

	}
	~CUSTOMVERTEX()
	{

	}
    FLOAT x, y, z; // The transformed position for the vertex
	FLOAT       tu, tv;
	static DWORD D3DFVF_CUSTOMVERTEX;
};
#undef TRANSPARENT
#define TRANSPARENT 0x1
#define RELEASEVTONEND 0x10
struct DrawInfo
{
	DrawInfo()
		:p_vertex(0),length(0),Z(0),flag(0),next(0),tex(0)
	{}
	~DrawInfo()
	{
		if(flag&RELEASEVTONEND)
		{
			delete[] p_vertex;
		}
	}
	CUSTOMVERTEX*  p_vertex;
	UINT length;
	int Z;
	DWORD flag;
	DrawInfo* next;
	LPDIRECT3DTEXTURE9 tex;
	static UINT TotalLenght;
};
typedef map<LPDIRECT3DTEXTURE9,int> MapCount;

#ifdef UNICODE
	typedef map<wstring,LPDIRECT3DTEXTURE9> MapPath;
#else
	typedef map<string,LPDIRECT3DTEXTURE9> MapPath;
#endif // UNICODE

//////
#define CENTRE 0
#define UPPERLEFT 1
class Graphic 
{
public:
	static Graphic* InitializeGraphic(HWND hwnd=0);
	static void ReleaseGraphic();




	float currentWidth;
	float currentHeight;

	IDirect3DDevice9* g_pd3dDevice;

	RenderDelegate* renderDelegate;
	//IDirect3DVertexBuffer9* g_pVB;
	//IDirect3DIndexBuffer9  * g_IB;
	///

	
	bool loadImage(LPCTSTR,LPDIRECT3DTEXTURE9&);
	bool releaseImage(LPDIRECT3DTEXTURE9&);
	void render(int);
	void defaultState();
	//»ù±¾µÄ»­Í¼
	bool DrawImage(ImageInfo*,float angle=0,DWORD flag=CENTRE);
	bool DrawImage(CUSTOMVERTEX*,int,UINT,LPDIRECT3DTEXTURE9,DWORD flag=0);

private:
	Graphic(HWND);
	~Graphic();

	static Graphic* soleGraphic;


	IDirect3D9* g_pD3D;

	//void SortList();
	IDirect3DVertexBuffer9* m_pVB;

	//LPDIRECT3DTEXTURE9 tex;

	void  RenderList();

	UINT CopyData(void**,DrawInfo*,UINT*,LPDIRECT3DTEXTURE9*);
	void RenderData(UINT*,UINT,UINT*,LPDIRECT3DTEXTURE9*);

	void AddList(DrawInfo**,DrawInfo*);
	//inline bool swap(DrawInfo*);
	void ReleaseList(DrawInfo*);


	DrawInfo* firstNodeNoTr;
	DrawInfo* firstNodeTran;

	HWND        g_hWnd;
	MapPath mapPath;
	MapCount _mapCount;

	UINT m_vbLastLen;


	///
	HRESULT initD3D();
	void initPosition();
};
#endif