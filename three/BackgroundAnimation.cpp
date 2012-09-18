#include "BackgroundAnimation.h"

#include "Header.h"
//Í¼ÐÅÏ¢
//#define DRAWX 0
//#define	DRAWY 1
#define STARTX 0
#define STARTY 1
#define WIDTH 2	
#define HIGHT 3	
#define TURN 4
#define MINSPEED 5
#define MAXSPEED 6
#define MINANGLE 7
#define MAXANGLE 8
#define TIME 9
#define PICWIDTH 10
#define PICHIGHT 11
//#define COUNT 7
//#define ANGLE 8
//#define TIME  9
//#define SPEED 10

#define FRAME 20.0f

#define TORTOISE 0
#define WHALE 1
#define ACALEPH 2
#define INKFISH 3
#define FISH1 4
#define FISH2 5
#define FISH3 6
#define FISH4 7 
#define FISH5 8 
#define FISH6 9 
#define FISH7 10



	//float startx=DESIGNTEXSTARTX/1024.0f;
	//float starty=DESIGNTEXSTARTY/512.0f;
	//float width=DESIGNWIDTH/1024.0f;
	//float hight=DESIGNHIGHT/512.0f;


#define DESIGNTEXSTARTX (0.0f/1024.0f)
#define DESIGNTEXSTARTY (465.0f/512.0f)
#define DESIGNWIDTH (34.0f/1024.0f)
#define DESIGNHIGHT (35.0f/512.0f)

#define POKERWIDTH (186.0f/1024.0f)
#define POKERHIGHT (263.0f/1024.0f)

#define BACKWIDTH (186.0f/2048.0f)
#define BACKHIGHT (263.0f/1024.0f)
		//float uw=186.0f/1024.0f;
		//float uh=263.0f/1024.0f;

BackgroundAnimation::BackgroundAnimation(Graphic* graphic)
	:elapseTime(0),DrawPoker(BACK),m_Poker(0),m_Back(0)
{


	number=new NumberImage(graphic);

	_record=ImmediateData::immediateData->recordData.record[ImmediateData::immediateData->recordData.wheelTimes];

	info=new ImageInfo(0,150,1920,1080,100.0f,0.0f,0.0f,1.0f,1.0f);
	m_info2=new ImageInfo(0,0,1920,1080,90.0f,0.0f,0.0f,1.0f,1.0f);

	graphic->loadImage(L"3.dds",info->pTexture);

	graphic->loadImage(L"0.dds",m_pokerTexture);
	graphic->loadImage(L"2.dds",m_info2->pTexture);

	graphic->loadImage(L"5.dds",m_TPoker[0]);
	graphic->loadImage(L"6.dds",m_TPoker[1]);
	graphic->loadImage(L"7.dds",m_TPoker[2]);
	graphic->loadImage(L"8.dds",m_TPoker[3]);
	graphic->loadImage(L"9.dds",m_TPoker[4]);
	graphic->loadImage(L"10.dds",m_TPoker[5]);

	m_IPoker[0]=ImageInfo(887,-692,150,209,20.0f);
	m_IPoker[1]=ImageInfo(390,-465,150,209,20.0f);
	m_IPoker[2]=ImageInfo(1032,-384,150,209,20.0f);
	m_IPoker[3]=ImageInfo(1528,-613,150,209,20.0f);

	InitAnimation(graphic);



	initVertices(graphic);
}

BackgroundAnimation::~BackgroundAnimation()
{
	delete number;
	delete info;
	delete m_info2;
}

void BackgroundAnimation::SetPoker(UINT data,DWORD flag)
{
	switch(flag)
	{
	case POKER:
		m_Poker=data;
		break;
	case BACKSIDE:
		m_Back=data;
		break;
	case DESIGN:
		m_Design=data;
		break;
	default:
		break;
	}
}

void BackgroundAnimation::InitAnimation(Graphic* graphic )
{
	graphic->loadImage(_T("0.dds"),m_animationTexture[TORTOISE]);
	graphic->loadImage(_T("1.dds"),m_animationTexture[WHALE]);
	graphic->loadImage(_T("4.dds"),m_animationTexture[ACALEPH]);
	graphic->loadImage(_T("4.dds"),m_animationTexture[INKFISH]);
	graphic->loadImage(_T("0.dds"),m_animationTexture[FISH1]);
	graphic->loadImage(_T("1.dds"),m_animationTexture[FISH2]);
	graphic->loadImage(_T("1.dds"),m_animationTexture[FISH3]);
	graphic->loadImage(_T("4.dds"),m_animationTexture[FISH4]);
	graphic->loadImage(_T("0.dds"),m_animationTexture[FISH5]);
	graphic->loadImage(_T("1.dds"),m_animationTexture[FISH6]);
	graphic->loadImage(_T("4.dds"),m_animationTexture[FISH7]);

	infoArray[TORTOISE][STARTX]=0;
	infoArray[TORTOISE][STARTY]=0;
	infoArray[TORTOISE][WIDTH]=148;
	infoArray[TORTOISE][HIGHT]=148;
	infoArray[TORTOISE][MINSPEED]=10;
	infoArray[TORTOISE][MAXSPEED]=15;
	infoArray[TORTOISE][MINANGLE]=-2;
	infoArray[TORTOISE][MAXANGLE]=2;
	infoArray[TORTOISE][TURN]=5;
	infoArray[TORTOISE][PICWIDTH]=1024;
	infoArray[TORTOISE][PICHIGHT]=512;
	infoArray[TORTOISE][TIME]=60;

	infoArray[WHALE][STARTX]=0;
	infoArray[WHALE][STARTY]=0;
	infoArray[WHALE][WIDTH]=416;
	infoArray[WHALE][HIGHT]=180;
	infoArray[WHALE][MINSPEED]=200;
	infoArray[WHALE][MAXSPEED]=300;
	infoArray[WHALE][MINANGLE]=-5;
	infoArray[WHALE][MAXANGLE]=5;
	infoArray[WHALE][TURN]=4;
	infoArray[WHALE][PICWIDTH]=2048;
	infoArray[WHALE][PICHIGHT]=1024;
	infoArray[WHALE][TIME]=10;

	infoArray[ACALEPH ][STARTX]=0;
	infoArray[ACALEPH ][STARTY]=396;
	infoArray[ACALEPH ][WIDTH]=108;
	infoArray[ACALEPH ][HIGHT]=120;
	infoArray[ACALEPH ][MINSPEED]=20;
	infoArray[ACALEPH ][MAXSPEED]=30;
	infoArray[ACALEPH ][MINANGLE]=-2;
	infoArray[ACALEPH ][MAXANGLE]=2;
	infoArray[ACALEPH ][TURN]=8;
	infoArray[ACALEPH ][PICWIDTH]=2048;
	infoArray[ACALEPH ][PICHIGHT]=2048;
	infoArray[ACALEPH ][TIME]=15;

	infoArray[INKFISH ][STARTX]=0;
	infoArray[INKFISH ][STARTY]=636;
	infoArray[INKFISH ][WIDTH]=180;
	infoArray[INKFISH ][HIGHT]=100;
	infoArray[INKFISH ][MINSPEED]=30;
	infoArray[INKFISH ][MAXSPEED]=40;
	infoArray[INKFISH ][MINANGLE]=-2;
	infoArray[INKFISH ][MAXANGLE]=2;
	infoArray[INKFISH ][TURN]=5;
	infoArray[INKFISH ][PICWIDTH]=2048;
	infoArray[INKFISH ][PICHIGHT]=2048;
	infoArray[INKFISH ][TIME]=20;

	infoArray[FISH1 ][STARTX]=740;
	infoArray[FISH1 ][STARTY]=160;
	infoArray[FISH1 ][WIDTH]=80;
	infoArray[FISH1 ][HIGHT]=36;
	infoArray[FISH1 ][MINSPEED]=50;
	infoArray[FISH1 ][MAXSPEED]=70;
	infoArray[FISH1 ][MINANGLE]=-2;
	infoArray[FISH1 ][MAXANGLE]=2;
	infoArray[FISH1 ][TURN]=3;
	infoArray[FISH1 ][PICWIDTH]=1024;
	infoArray[FISH1 ][PICHIGHT]=512;
	infoArray[FISH1 ][TIME]=18;

	infoArray[FISH2 ][STARTX]=1664;
	infoArray[FISH2 ][STARTY]=0;
	infoArray[FISH2 ][WIDTH]=112;
	infoArray[FISH2 ][HIGHT]=76;
	infoArray[FISH2 ][MINSPEED]=40;
	infoArray[FISH2 ][MAXSPEED]=50;
	infoArray[FISH2 ][MINANGLE]=-2;
	infoArray[FISH2 ][MAXANGLE]=2;
	infoArray[FISH2 ][TURN]=3;
	infoArray[FISH2 ][PICWIDTH]=2048;
	infoArray[FISH2 ][PICHIGHT]=1024;
	infoArray[FISH2 ][TIME]=25;

	infoArray[FISH3 ][STARTX]=0;
	infoArray[FISH3 ][STARTY]=768;
	infoArray[FISH3 ][WIDTH]=148;
	infoArray[FISH3 ][HIGHT]=124;
	infoArray[FISH3 ][MINSPEED]=10;
	infoArray[FISH3 ][MAXSPEED]=15;
	infoArray[FISH3 ][MINANGLE]=-2;
	infoArray[FISH3 ][MAXANGLE]=2;
	infoArray[FISH3 ][TURN]=13;
	infoArray[FISH3 ][PICWIDTH]=2048;
	infoArray[FISH3 ][PICHIGHT]=1024;
	infoArray[FISH3 ][TIME]=10;

	infoArray[FISH4  ][STARTX]=0;
	infoArray[FISH4  ][STARTY]=0;
	infoArray[FISH4  ][WIDTH]=192;
	infoArray[FISH4  ][HIGHT]=132;
	infoArray[FISH4  ][MINSPEED]=20;
	infoArray[FISH4  ][MAXSPEED]=30;
	infoArray[FISH4  ][MINANGLE]=-2;
	infoArray[FISH4  ][MAXANGLE]=2;
	infoArray[FISH4  ][TURN]=5;
	infoArray[FISH4  ][PICWIDTH]=2048;
	infoArray[FISH4  ][PICHIGHT]=2048;
	infoArray[FISH4  ][TIME]=16;

	infoArray[FISH5  ][STARTX]=740;
	infoArray[FISH5  ][STARTY]=0;
	infoArray[FISH5  ][WIDTH]=60;
	infoArray[FISH5  ][HIGHT]=40;
	infoArray[FISH5  ][MINSPEED]=30;
	infoArray[FISH5  ][MAXSPEED]=50;
	infoArray[FISH5  ][MINANGLE]=-2;
	infoArray[FISH5  ][MAXANGLE]=2;
	infoArray[FISH5  ][TURN]=4;
	infoArray[FISH5  ][PICWIDTH]=1024;
	infoArray[FISH5  ][PICHIGHT]=512;
	infoArray[FISH5  ][TIME]=12;

	infoArray[FISH6  ][STARTX]=0;
	infoArray[FISH6  ][STARTY]=720;
	infoArray[FISH6  ][WIDTH]=108;
	infoArray[FISH6  ][HIGHT]=48;
	infoArray[FISH6  ][MINSPEED]=20;
	infoArray[FISH6  ][MAXSPEED]=40;
	infoArray[FISH6  ][MINANGLE]=-2;
	infoArray[FISH6  ][MAXANGLE]=2;
	infoArray[FISH6  ][TURN]=15;
	infoArray[FISH6  ][PICWIDTH]=2048;
	infoArray[FISH6  ][PICHIGHT]=1024;
	infoArray[FISH6  ][TIME]=22;

	infoArray[FISH7   ][STARTX]=0;
	infoArray[FISH7   ][STARTY]=936;
	infoArray[FISH7   ][WIDTH]=306;
	infoArray[FISH7   ][HIGHT]=340;
	infoArray[FISH7   ][MINSPEED]=60;
	infoArray[FISH7   ][MAXSPEED]=100;
	infoArray[FISH7   ][MINANGLE]=-2;
	infoArray[FISH7   ][MAXANGLE]=2;
	infoArray[FISH7   ][TURN]=6;
	infoArray[FISH7   ][PICWIDTH]=2048;
	infoArray[FISH7   ][PICHIGHT]=2048;
	infoArray[FISH7   ][TIME]=30;

	for(int i=0,fish;i<NUMBEROFFISH;i++)
	{
		fish=rand()%NUMBEROFIMAGE;
		m_fish[i]=Fish();
		m_fish[i].angle=rand()%360;
		m_fish[i].info=infoArray[fish];
		m_fish[i].changeAngle=rand()%(int)(infoArray[fish][MAXANGLE]-infoArray[fish][MINANGLE]);
		m_fish[i].speed=rand()%(int)(infoArray[fish][MAXSPEED]-infoArray[fish][MINSPEED])+infoArray[fish][MINSPEED];
		m_fish[i].posX=rand()%4000-1000;
		m_fish[i].posY=rand()%4000-2000;
		m_fish[i].p_Texture=m_animationTexture[fish];
	}




	//for(int i=0;i<3;i++)
	//{
	//	iinfo[i]=ImageInfo();
	//	iinfo[i].beginX=infoArray[i][DRAWX];
	//	iinfo[i].beginY=infoArray[i][DRAWY];
	//	iinfo[i].width=infoArray[i][WIDTH];
	//	iinfo[i].height=infoArray[i][HIGHT];
	//	iinfo[i].uvW=((float)infoArray[i][WIDTH])/PICWIDTH;
	//	iinfo[i].uvH=((float)infoArray[i][HIGHT])/PICHIGHT;
	//	iinfo[i].Z=0.9f;

	//}
	//graphic->loadImage(L"0.dds",iinfo[TORTOISE].pTexture);
	//graphic->loadImage(L"0.dds",iinfo[YELLOWFIN].pTexture);
	//graphic->loadImage(L"0.dds",iinfo[REDFIN].pTexture);
}
void BackgroundAnimation::Animation(UINT time)
{
	float cx,cy;
	for(int i=0;i<NUMBEROFFISH;i++)
	{
		cx=cos(m_fish[i].angle*3.1415f/180.f)*m_fish[i].speed/FRAME;
		cy=sin(m_fish[i].angle*3.1415f/180.f)*m_fish[i].speed/FRAME;
		m_fish[i].posX+=cx;
		m_fish[i].posY-=cy;
		m_fish[i].angle+=m_fish[i].changeAngle/FRAME;
		

		m_fish[i].count++;
		if(m_fish[i].count>=AMOUNT)
		{
			m_fish[i].count=0;
		}
		m_fish[i].time+=time;
		if(m_fish[i].time>=m_fish[i].info[TIME]*1000)
		{
			m_fish[i].changeAngle=rand()%(int)(m_fish[i].info[MAXANGLE]-m_fish[i].info[MINANGLE]);
			m_fish[i].speed=rand()%(int)(m_fish[i].info[MAXSPEED]-m_fish[i].info[MINSPEED])+m_fish[i].info[MINSPEED];
			m_fish[i].time-=m_fish[i].info[TIME]*1000;
		}
		if(	m_fish[i].posX<=-1000||m_fish[i].posX>=3000)
		{
			m_fish[i].angle=(int)m_fish[i].angle%360;
			if(m_fish[i].angle>0&&m_fish[i].angle<=180)
			{
				m_fish[i].angle=180-m_fish[i].angle;
			}
			else
			{
				m_fish[i].angle=540-m_fish[i].angle;
			}
		}
		else if(	m_fish[i].posY<=-1000||m_fish[i].posY>=3000)
		{
			m_fish[i].angle=(int)m_fish[i].angle%360;

			m_fish[i].angle=360-m_fish[i].angle;
		}
	}

}
void BackgroundAnimation::initVertices(Graphic* pGraphic)
{

	int xy6;
	for(int y=0;y<4;y++)
	{
		for(int x=0;x<25;x++)
		{
			xy6=(x+y*25)*6;
			v3Array[xy6+0]=D3DXVECTOR3((21.6f*x),(-23*y),10.0f);
			v3Array[xy6+1]=D3DXVECTOR3((21.6f*x+19),(-23*y),10.0f);
			v3Array[xy6+2]=D3DXVECTOR3((21.6f*x),(-23*y-20),10.0f);
			v3Array[xy6+3]=v3Array[xy6+1];
			v3Array[xy6+4]=D3DXVECTOR3((21.6f*x+19),(-23*y-20),10.0f);
			v3Array[xy6+5]=v3Array[xy6+2];

		}
	}
}
void BackgroundAnimation::Render(int time,Graphic* g)
{


	ImmediateData* data=ImmediateData::immediateData;
	elapseTime+=time;
	if(elapseTime>=1000/FRAME)
	{
		Animation(time);
		elapseTime-=1000/FRAME;
	}
	
	g->DrawImage(info);
	

	ImageInfo fishInfo;
	for(int i=0;i<NUMBEROFFISH;i++)
	{
		fishInfo=ImageInfo();
		fishInfo.beginX=m_fish[i].posX;
		fishInfo.beginY=m_fish[i].posY;
		fishInfo.width=m_fish[i].info[WIDTH];
		fishInfo.height=m_fish[i].info[HIGHT];
		fishInfo.uvW=m_fish[i].info[WIDTH]/(float)m_fish[i].info[PICWIDTH];
		fishInfo.uvH=m_fish[i].info[HIGHT]/(float)m_fish[i].info[PICHIGHT];
		fishInfo.Z=95.0f;
		fishInfo.uvX= (((int)m_fish[i].count%(int)m_fish[i].info[TURN]*m_fish[i].info[WIDTH])+m_fish[i].info[STARTX])/(float)m_fish[i].info[PICWIDTH];
		fishInfo.uvY= (((int)(m_fish[i].count/m_fish[i].info[TURN])*m_fish[i].info[HIGHT])+m_fish[i].info[STARTY])/(float)m_fish[i].info[PICHIGHT];
		fishInfo.pTexture=m_fish[i].p_Texture;

		g->DrawImage(&fishInfo,m_fish[i].angle);

	}
	
	g->DrawImage(m_info2);
	
	number->DrawNumber(ONENUMBER,717,-913,0,data->realdata.prizeGold,4);
	number->DrawNumber(ONENUMBER,708,-950,0,data->recordData.wheelTimes,3);
	number->DrawNumber(ONENUMBER,708,-990,0,data->realdata.bureauTimes,3);
	number->DrawNumber(ONENUMBER,705,-1030,0,data->realdata.spade,3);
	number->DrawNumber(ONENUMBER,835,-1030,0,data->realdata.heart,3);
	number->DrawNumber(ONENUMBER,975,-1030,0,data->realdata.club,3);
	number->DrawNumber(ONENUMBER,1105,-1030,0,data->realdata.diamond,3);
	number->DrawNumber(ONENUMBER,1240,-1030,0,data->realdata.joker,3);

	number->DrawNumber(ONENUMBER,165,-290,90,data->realdata.prizeGold,4);
	number->DrawNumber(ONENUMBER,133,-285,90,data->recordData.wheelTimes,3);
	number->DrawNumber(ONENUMBER,96,-285,90,data->realdata.bureauTimes,3);
	number->DrawNumber(ONENUMBER,55,-283,90,data->realdata.spade,3);
	number->DrawNumber(ONENUMBER,55,-410,90,data->realdata.heart,3);
	number->DrawNumber(ONENUMBER,55,-555,90,data->realdata.club,3);
	number->DrawNumber(ONENUMBER,55,-690,90,data->realdata.diamond,3);
	number->DrawNumber(ONENUMBER,55,-825,90,data->realdata.joker,3);

	number->DrawNumber(ONENUMBER,1205,-162,180,data->realdata.prizeGold,4);
	number->DrawNumber(ONENUMBER,1215,-128,180,data->recordData.wheelTimes,3);
	number->DrawNumber(ONENUMBER,1215,-88,180,data->realdata.bureauTimes,3);
	number->DrawNumber(ONENUMBER,1217,-50,180,data->realdata.spade,3);
	number->DrawNumber(ONENUMBER,1082,-50,180,data->realdata.heart,3);
	number->DrawNumber(ONENUMBER,948,-50,180,data->realdata.club,3);
	number->DrawNumber(ONENUMBER,813,-50,180,data->realdata.diamond,3);
	number->DrawNumber(ONENUMBER,678,-50,180,data->realdata.joker,3);

	number->DrawNumber(ONENUMBER,1750,-785,270,data->realdata.prizeGold,4);
	number->DrawNumber(ONENUMBER,1788,-793,270,data->recordData.wheelTimes,3);
	number->DrawNumber(ONENUMBER,1827,-793,270,data->realdata.bureauTimes,3);
	number->DrawNumber(ONENUMBER,1865,-793,270,data->realdata.spade,3);
	number->DrawNumber(ONENUMBER,1865,-658,270,data->realdata.heart,3);
	number->DrawNumber(ONENUMBER,1865,-523,270,data->realdata.club,3);
	number->DrawNumber(ONENUMBER,1865,-388,270,data->realdata.diamond,3);
	number->DrawNumber(ONENUMBER,1865,-253,270,data->realdata.joker,3);
	
	record(m_recordVertices[0],762,-912,0,g);
	record(m_recordVertices[1],170,-343,90,g);
	record(m_recordVertices[2],1154,-164,180,g);
	record(m_recordVertices[3],1749,-735,270,g);
	
	if(DrawPoker==BACK)
	{
		int x,y;
		x=m_Back%10;
		y=m_Back/10;
		for(int i=0;i<4;i++)
		{
			m_IPoker[i].pTexture=m_TPoker[5];
			m_IPoker[i].uvX=x*BACKWIDTH;
			m_IPoker[i].uvY=y*BACKHIGHT;
			m_IPoker[i].uvW=BACKWIDTH;
			m_IPoker[i].uvH=BACKHIGHT;
		}
		g->DrawImage(&m_IPoker[0],0,UPPERLEFT);
		g->DrawImage(&m_IPoker[1],90,UPPERLEFT);
		g->DrawImage(&m_IPoker[2],180,UPPERLEFT);
		g->DrawImage(&m_IPoker[3],270,UPPERLEFT);
	}
	else if(DrawPoker==FRONT)
	{
		int x,y;
		x=m_Poker%5;
		y=m_Poker/5;


		for(int i=0;i<4;i++)
		{
			m_IPoker[i].pTexture=m_TPoker[m_Design];
			m_IPoker[i].uvX=x*POKERWIDTH;
			m_IPoker[i].uvY=y*POKERHIGHT;
			m_IPoker[i].uvW=POKERWIDTH;
			m_IPoker[i].uvH=POKERHIGHT;
		}
		g->DrawImage(&m_IPoker[0],0,UPPERLEFT);
		g->DrawImage(&m_IPoker[1],90,UPPERLEFT);
		g->DrawImage(&m_IPoker[2],180,UPPERLEFT);
		g->DrawImage(&m_IPoker[3],270,UPPERLEFT);
	}
	

}
bool BackgroundAnimation::record(CUSTOMVERTEX* vertices,int x,int y,float angle,Graphic* g)
{

	bool result=false;
	int view=ImmediateData::immediateData->realdata.view;

	int view2=view*2;
	int view6=view*6;

	if(view==0)		
	{
		result = true;
		goto ends;
	}

	//ImmediateData* data=ImmediateData::immediateData;


	D3DXMATRIX mTra;
	D3DXMATRIX mMov=D3DXMATRIX
		(
		1,0,0,0,
		0,1,0,0,
		0,0,1,0,
		x,y,0,1
		);

	//D3DXMatrixIdentity( &mTra ); 
	D3DXMatrixRotationZ(&mTra,-angle*3.1415f/180.0f);

	D3DXMatrixMultiply(&mTra,&mTra,&mMov);



	//int view2=2;
	//int view6=6;
	



	D3DXVECTOR3 v3Temp=D3DXVECTOR3();
	for(int i=0,i6=0;i<view;i++)
	{
		i6=i*6;
		//v3Temp=v3Array[i6];
		D3DXVec3TransformCoord(&v3Temp,&v3Array[i6],&mTra);
		vertices[i6]=CUSTOMVERTEX(v3Temp,DESIGNTEXSTARTX+_record[i]*DESIGNWIDTH,DESIGNTEXSTARTY);

		//v3Temp=v3Array[i6+1];
		D3DXVec3TransformCoord(&v3Temp,&v3Array[i6+1],&mTra);
		vertices[i6+1]=CUSTOMVERTEX(v3Temp,DESIGNTEXSTARTX+_record[i]*DESIGNWIDTH+DESIGNWIDTH,DESIGNTEXSTARTY);

		//v3Temp=v3Array[i6+2];
		D3DXVec3TransformCoord(&v3Temp,&v3Array[i6+2],&mTra);
		vertices[i6+2]=CUSTOMVERTEX(v3Temp,DESIGNTEXSTARTX+_record[i]*DESIGNWIDTH,DESIGNTEXSTARTY+DESIGNHIGHT);

		vertices[i6+3]=vertices[i6+1];

		//v3Temp=v3Array[i6+4];
		D3DXVec3TransformCoord(&v3Temp,&v3Array[i6+4],&mTra);
		vertices[i6+4]=CUSTOMVERTEX(v3Temp,DESIGNTEXSTARTX+_record[i]*DESIGNWIDTH+DESIGNWIDTH,DESIGNTEXSTARTY+DESIGNHIGHT);


		vertices[i6+5]=vertices[i6+2];

	}
	g->DrawImage(vertices,10.0f,view6,m_pokerTexture,TRANSPARENT);
	//int vic6=view6*sizeof(CUSTOMVERTEX);

	//if( FAILED( g->g_pd3dDevice->CreateVertexBuffer(vic6,
	//	D3DUSAGE_WRITEONLY, CUSTOMVERTEX::D3DFVF_CUSTOMVERTEX, D3DPOOL_DEFAULT, &g->g_pVB, NULL ) ) )
	//	return false;

	//VOID* pVertices;
	//if( FAILED(g->g_pVB->Lock(0,vic6, ( void** )&pVertices, 0)))
	//{
	//	return false;
	//}
	//memcpy( pVertices,vertices,vic6);
	//if( FAILED(g->g_pVB->Unlock()))
	//	return false;

	//if( FAILED(g->g_pd3dDevice->SetTexture( 0,m_pokerTexture)))
	//	return false;

	////g->defaultState();


	//if( FAILED(g->g_pd3dDevice->SetFVF( CUSTOMVERTEX::D3DFVF_CUSTOMVERTEX )))
	//	return false;



	//// Rendering of scene objects can happen here
	//if( FAILED(g->g_pd3dDevice->SetStreamSource( 0, g->g_pVB, 0, sizeof( CUSTOMVERTEX ) )))
	//	return false;
	//if( FAILED( g->g_pd3dDevice->DrawPrimitive(D3DPT_TRIANGLELIST,0,view2)))
	//	return false;

	//delete[] vertices;


ends:
	return result;
}