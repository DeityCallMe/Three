#ifndef _BACKGROUNDANIMATION_H
#define _BACKGROUNDANIMATION_H
#include "BaseGame.h"
#include "NumberImage.h"
#include "ImmediateData.h"
#include <tchar.h>



#define AMOUNT 15

#define NUMBEROFIMAGE 11
#define NUMBEROFINFO 12

#define NUMBEROFFISH 30

#define FRONT 0
#define BACK 1

#define POKER 0
#define BACKSIDE 1
#define DESIGN 2


class NumberImage;
class ImmediateData;
struct Fish
{
	int* info;

	float angle;

	float posX;
	float posY;
	int speed;
	int time;
	int changeAngle;
	int count;

	LPDIRECT3DTEXTURE9 p_Texture;
};
class BackgroundAnimation
{
public:
	BackgroundAnimation(Graphic*);
	~BackgroundAnimation();
	void Render(int,Graphic*);
	
	void SetPoker(UINT,DWORD);

	//void Clearup();
	DWORD  DrawPoker;

private:

	UINT m_Back;
	UINT m_Poker;
	UINT m_Design;

	ImageInfo m_IPoker[4];
	LPDIRECT3DTEXTURE9 m_TPoker[6];

	void InitAnimation(Graphic*);

	void Animation(UINT);

	bool record(CUSTOMVERTEX*,int,int,float,Graphic*);

	void initVertices(Graphic*);

	LPDIRECT3DTEXTURE9 m_pokerTexture;
	LPDIRECT3DTEXTURE9 m_animationTexture[NUMBEROFIMAGE];

	int infoArray[NUMBEROFIMAGE][NUMBEROFINFO];

	ImageInfo iinfo[NUMBEROFIMAGE];

	ImageInfo* info;
	ImageInfo* m_info2;
	int elapseTime;
	int tortoiseCount;

	CUSTOMVERTEX m_recordVertices[4][600];

	Fish m_fish[NUMBEROFFISH];

	D3DXVECTOR3  v3Array[100*6+4*6];
	const BYTE* _record;

	NumberImage* number;
};
#endif