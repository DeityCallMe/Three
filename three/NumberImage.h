#ifndef _NUMBERIMAGE_H
#define _NUMBERIMAGE_H
#include "Graphic.h"
#include "GameManager.h"
#include <Windows.h>
#include "HAssert.h"
enum  NUMBERSTYLE{ONENUMBER=0,TWONUMBER,THREENUMBER};
class NumberImage
{
public:
	NumberImage();
	NumberImage(Graphic*);
	~NumberImage();

	bool DrawNumber(NUMBERSTYLE,int x,int y,float angle,int n,int min);
private:
	LPDIRECT3DTEXTURE9 pPicture;
	int infoArray[3][4];
	void loadPicture();


	inline int digits(int);
	inline void getDigit(int,int*);
	void initialize();

	Graphic* pGraphic;
};
#endif