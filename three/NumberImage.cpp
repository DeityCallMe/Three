#include "NumberImage.h"

#include "Header.h"
#define DIGITS(a) (int)log10((float)a)+1

//Í¼ÐÅÏ¢
#define STARTX 0
#define STARTY 1
#define WIDTH 2	
#define HIGHT 3	


#define PICWIDTH 1024.0f
#define PICHIGHT 512.0f
NumberImage::NumberImage()
{
	pGraphic=GameManager::GetGraphic();
	initialize();
}
NumberImage::NumberImage(Graphic* graphic)
{
	pGraphic=graphic;
	initialize();
}
NumberImage::~NumberImage()
{
	pGraphic->releaseImage(pPicture);
}

void NumberImage::initialize()
{
	loadPicture();
	infoArray[0][0]=0;
	infoArray[0][1]=444;
	infoArray[0][2]=16;
	infoArray[0][3]=20;

	infoArray[1][0]=740;
	infoArray[1][1]=340;
	infoArray[1][2]=25;
	infoArray[1][3]=28;

	infoArray[2][0]=200;
	infoArray[2][1]=444;
	infoArray[2][2]=34;
	infoArray[2][3]=24;
}

void NumberImage::loadPicture()
{
	pGraphic->loadImage(L"0.dds",pPicture);
}
inline int NumberImage::digits(int n)
{
	if(n==0)
		return 0;

	return DIGITS(n);
}
bool NumberImage::DrawNumber(NUMBERSTYLE style,int x,int y,float angle,int n,int min)
{
	assert(min>=0);

	D3DXMATRIX mRot;
	D3DXMatrixIdentity( &mRot ); 
	D3DXMatrixRotationZ(&mRot,-angle*3.1415f/180.0f);

	int ds=digits(n);
	ds=ds>min?ds:min;

	int* pn=new int[ds];
	ZeroMemory(pn,ds*sizeof(int));


	if(style!=::THREENUMBER)
	{
		getDigit(n,pn);
	}
	else
	{
		pn=new int[1];
		*pn=n;
	}



	D3DXVECTOR3* v3Array=new D3DXVECTOR3[ds*2+2];


	CUSTOMVERTEX*  vertices=new CUSTOMVERTEX[ds*6];

	int i2;
	for(int i=0;i<=ds;i++)
	{
		i2=i*2;

		v3Array[i2+0]=D3DXVECTOR3(-i*infoArray[style][WIDTH],0,0);
		v3Array[i2+1]=D3DXVECTOR3(-i*infoArray[style][WIDTH],-infoArray[style][HIGHT],0);


		D3DXVec3TransformCoord(v3Array+i2+0,v3Array+i2+0,&mRot);
		D3DXVec3TransformCoord(v3Array+i2+1,v3Array+i2+1,&mRot);
	}
	int i6;

	float startx=infoArray[style][STARTX]/PICWIDTH;
	float starty=infoArray[style][STARTY]/PICHIGHT;
	float width=infoArray[style][WIDTH]/PICWIDTH;
	float hight=infoArray[style][HIGHT]/PICHIGHT;


	for(int i=0;i<ds;i++)
	{
		i6=i*6;
		i2=i*2;
		vertices[i6+0]=CUSTOMVERTEX(v3Array[i2+2].x+x,v3Array[i2+2].y+y,10.0f,startx+pn[i]*width,starty);
		vertices[i6+1]=CUSTOMVERTEX(v3Array[i2+0].x+x,v3Array[i2+0].y+y,10.0f,startx+pn[i]*width+width,starty);
		vertices[i6+2]=CUSTOMVERTEX(v3Array[i2+3].x+x,v3Array[i2+3].y+y,10.0f,startx+pn[i]*width,starty+hight);
		vertices[i6+3]=vertices[i6+1];
		vertices[i6+4]=CUSTOMVERTEX(v3Array[i2+1].x+x,v3Array[i2+1].y+y,10.0f,startx+pn[i]*width+width,starty+hight);
		vertices[i6+5]=vertices[i6+2];
	}




	pGraphic->DrawImage(vertices,10.0f,ds*6,pPicture,TRANSPARENT|RELEASEVTONEND);


	//int dsc6=ds*6*sizeof(CUSTOMVERTEX);
	//if( FAILED( pGraphic->g_pd3dDevice->CreateVertexBuffer(dsc6,
	//	D3DUSAGE_WRITEONLY, CUSTOMVERTEX::D3DFVF_CUSTOMVERTEX, D3DPOOL_DEFAULT, &pGraphic->g_pVB, NULL ) ) )
	//	return false;


	//VOID* pVertices;
	//if( FAILED(pGraphic->g_pVB->Lock(0,dsc6, ( void** )&pVertices, 0)))
	//{
	//	return false;
	//}
	//memcpy( pVertices, vertices,dsc6);
	//if( FAILED(pGraphic->g_pVB->Unlock()))
	//	return false;

	//if( FAILED(pGraphic->g_pd3dDevice->SetTexture( 0, pPicture )))
	//	return false;

	////pGraphic->defaultState();


	//if( FAILED(pGraphic->g_pd3dDevice->SetFVF( CUSTOMVERTEX::D3DFVF_CUSTOMVERTEX )))
	//	return false;



	//// Rendering of scene objects can happen here
	//if( FAILED(pGraphic->g_pd3dDevice->SetStreamSource( 0, pGraphic->g_pVB, 0, sizeof( CUSTOMVERTEX ) )))
	//	return false;
	//if( FAILED( pGraphic->g_pd3dDevice->DrawPrimitive(D3DPT_TRIANGLELIST,0,ds*2)))
	//	return false;


	//pGraphic->g_pVB->Release();

	delete[] pn;
	delete[] v3Array;
	//delete[] vertices;

	return true;
}
inline void NumberImage::getDigit(int n,int* list)
{
	for(int i=0;n!=0;i++)
	{
		*(list+i)=n%10;
		n/=10;
	}
}