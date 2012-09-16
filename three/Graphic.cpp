#include "Graphic.h"

#include "Header.h"
DWORD CUSTOMVERTEX::D3DFVF_CUSTOMVERTEX=(D3DFVF_XYZ|D3DFVF_TEX1);
UINT DrawInfo::TotalLenght=0;
Graphic::Graphic(HWND hwnd)
	:g_hWnd(hwnd),firstNodeTran(0),firstNodeNoTr(0),m_vbLastLen(0)
	,m_pVB(0)
{
	initPosition();
	renderDelegate=new RenderDelegate();
	initD3D();
	//loadImage(L"0.dds",tex);
}
Graphic::~Graphic()
{
	release_com(g_pD3D);
}
void Graphic::initPosition()
{
	LPRECT rc=new RECT();
	GetWindowRect(g_hWnd,rc);
	currentWidth=rc->right-rc->left;
	currentHeight=rc->bottom-rc->top;


}
void Graphic::aaaaa()
{
	D3DXMATRIX mat_proj, mat_view,mat_world;
	
	D3DXMatrixOrthoLH(&mat_proj,DEFAULTWIDTH,DEFAULTHEIGHT,1.0f,1000.0f);
	//D3DXMatrixPerspectiveFovLH(&mat_proj, D3DX_PI/4.0, 1.33333, 1.0, 1000.0);


	D3DXMatrixLookAtLH(&mat_view, 
		&D3DXVECTOR3(0.0, 0.0f, -100.0f),
		&D3DXVECTOR3(0.0f, 0.0f, 0.0f), 
		&D3DXVECTOR3(0.0f, 1.0f, 0.0f));

	mat_world=D3DXMATRIX
		(
		1,0,0,0,
		0,1,0,0,
		0,0,1,0,
		DEFAULTWIDTH*-0.5f,DEFAULTHEIGHT*0.5f,0,1
		);


	g_pd3dDevice->SetTransform(D3DTS_PROJECTION, &mat_proj);
	g_pd3dDevice->SetTransform(D3DTS_VIEW, &mat_view);
	g_pd3dDevice->SetTransform(D3DTS_WORLD, &mat_world);
	

	g_pd3dDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	g_pd3dDevice->SetRenderState(D3DRS_ALPHABLENDENABLE,TRUE);
	g_pd3dDevice->SetRenderState(D3DRS_SRCBLEND,  D3DBLEND_SRCALPHA);
	g_pd3dDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);



	g_pd3dDevice->SetRenderState(D3DRS_ZENABLE, TRUE);
	g_pd3dDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
	g_pd3dDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);

	defaultState();

	FAILED(g_pd3dDevice->SetFVF( CUSTOMVERTEX::D3DFVF_CUSTOMVERTEX ));


	g_pd3dDevice->SetRenderState(D3DRS_LIGHTING, FALSE);


}
void Graphic::render(int time)
{
	g_pd3dDevice->Clear( 0, NULL, D3DCLEAR_TARGET| D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB( 0, 0, 0 ), 1.0f, 0 );
	if( SUCCEEDED( g_pd3dDevice->BeginScene() ) )
	{
		(*renderDelegate)(time,this);

		//CUSTOMVERTEX*  vertices =new CUSTOMVERTEX[6];
		//vertices[0]=CUSTOMVERTEX( -100,100,100,  0,0);
		//vertices[1]=CUSTOMVERTEX( 100,100,100,  1,0);
		//vertices[2]=CUSTOMVERTEX( -100,-100,100,  0,1);
		//vertices[3]=CUSTOMVERTEX( 100,100,100, 1,0);
		//vertices[4]=CUSTOMVERTEX( 100,-100,100,  1,1);
		//vertices[5]=CUSTOMVERTEX( -100,-100,100,  0,1);
		//DrawImage(vertices,100,6,tex,TRANSPARENT|RELEASEVTONEND|0x100);

		

		RenderList();

		g_pd3dDevice->EndScene();
	}
	// Present the backbuffer contents to the display
	g_pd3dDevice->Present( NULL, NULL, NULL, NULL );

}
bool Graphic::loadImage(LPCTSTR path,LPDIRECT3DTEXTURE9& const pTex)
{
#ifdef UNICODE
	wstring str(path);
#else
	string str(path);
#endif // UNICODE
	//MapPath::iterator itr;
	//itr=mapPath.find(str);

	if(_mapCount[mapPath[path]]==0)
	{
		if(FAILED(D3DXCreateTextureFromFile(g_pd3dDevice,path,&pTex)))
		return false;
		//if(FAILED(D3DXCreateTextureFromFileEx(g_pd3dDevice,path,
		//	D3DX_DEFAULT,
		//	D3DX_DEFAULT,
		//	D3DX_DEFAULT,
		//	D3DUSAGE_RENDERTARGET,
		//	D3DFMT_A8R8G8B8,  
		//	D3DPOOL_DEFAULT,  
		//	D3DX_FILTER_NONE,  
		//	D3DX_DEFAULT,    
		//	0,   //colorkey
		//	NULL,  
		//	NULL,   
		//	&pTex)))
		//	return false;
		mapPath[str]=pTex;
	}
	else
	{
		pTex=mapPath[path];
	}
	_mapCount[pTex]++;
	return true;
}
bool Graphic::releaseImage(LPDIRECT3DTEXTURE9& pTex)
{
	_mapCount[pTex]--;
	if(_mapCount[pTex]==0)
	{
		release_com(pTex);
		return TRUE;
	}
	return FALSE;

}
HRESULT Graphic::initD3D()
{

	D3DXMATRIX mat_proj, mat_view,mat_world;

	D3DDISPLAYMODE  display_mode;
		D3DPRESENT_PARAMETERS d3dpp; 
	if( NULL == ( g_pD3D = Direct3DCreate9( D3D_SDK_VERSION ) ) )
		return E_FAIL;
	 if(FAILED(g_pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &display_mode)))
        return FALSE;


	ZeroMemory( &d3dpp, sizeof(d3dpp) );
	d3dpp.Windowed = TRUE;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;
	d3dpp.EnableAutoDepthStencil = TRUE;
    d3dpp.AutoDepthStencilFormat = D3DFMT_D16;

	//if( FAILED( g_pD3D->CreateDevice( D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, g_hWnd,
	//	D3DCREATE_HARDWARE_VERTEXPROCESSING,
	//	&d3dpp, &g_pd3dDevice ) ) )
	//	return E_FAIL;

	if( FAILED( g_pD3D->CreateDevice( D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, g_hWnd,
								D3DCREATE_SOFTWARE_VERTEXPROCESSING,
								&d3dpp, &g_pd3dDevice ) ) )
	return E_FAIL;


	D3DXMatrixOrthoLH(&mat_proj,DEFAULTWIDTH,DEFAULTHEIGHT,1.0f,1000.0f);
	//D3DXMatrixPerspectiveFovLH(&mat_proj, D3DX_PI/4.0, 1.33333, 1.0, 1000.0);


	D3DXMatrixLookAtLH(&mat_view, 
		&D3DXVECTOR3(0.0, 0.0f, -100.0f),
		&D3DXVECTOR3(0.0f, 0.0f, 0.0f), 
		&D3DXVECTOR3(0.0f, 1.0f, 0.0f));

	mat_world=D3DXMATRIX
		(
		1,0,0,0,
		0,1,0,0,
		0,0,1,0,
		DEFAULTWIDTH*-0.5f,DEFAULTHEIGHT*0.5f,0,1
		);


	g_pd3dDevice->SetTransform(D3DTS_PROJECTION, &mat_proj);
	g_pd3dDevice->SetTransform(D3DTS_VIEW, &mat_view);
	g_pd3dDevice->SetTransform(D3DTS_WORLD, &mat_world);
	

	g_pd3dDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	g_pd3dDevice->SetRenderState(D3DRS_ALPHABLENDENABLE,TRUE);
	g_pd3dDevice->SetRenderState(D3DRS_SRCBLEND,  D3DBLEND_SRCALPHA);
	g_pd3dDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);



	g_pd3dDevice->SetRenderState(D3DRS_ZENABLE, TRUE);
	g_pd3dDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
	g_pd3dDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);

	defaultState();

	if( FAILED(g_pd3dDevice->SetFVF( CUSTOMVERTEX::D3DFVF_CUSTOMVERTEX )))
		return E_FAIL;



	return S_OK;
}

//void Graphic::SortList()
//{
//	DrawInfo* node1=new DrawInfo();
//	node1->next=firstNode;
//
//	DrawInfo* node2=node1;
//
//	bool bc=false;
//	do
//	{
//		bc=swap(node1);
//		while(node1->next!=0)
//		{
//			node1=node1->next;
//			bc=swap(node1);
//		}
//		node1=node2;
//	}while(bc);
//		
//	delete node1;
//}
//bool  Graphic::swap(DrawInfo* chain)
//{
//	DrawInfo* centre;
//	if(chain->next!=0&&chain->next->next!=0)
//	{
//		centre=chain->next;
//		if(centre->Z>centre->next->Z
//			||((centre->flag&TRANSPARENT)&&!(centre->next->flag&TRANSPARENT))
//			)
//		{
//			//swap
//			void* temp;
//			temp=centre->next->next;
//			chain->next=centre->next;
//			centre->next=centre;
//			centre->next=(DrawInfo*)temp;
//			return true;
//		}
//	}
//	return false;
//}
void Graphic::defaultState()
{


	g_pd3dDevice->SetTextureStageState( 0, D3DTSS_COLOROP, D3DTOP_MODULATE );

	g_pd3dDevice->SetTextureStageState( 0, D3DTSS_COLORARG1, D3DTA_TEXTURE );

	g_pd3dDevice->SetTextureStageState( 0, D3DTSS_COLORARG2, D3DTA_DIFFUSE );

	g_pd3dDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);


}
bool Graphic::DrawImage( ImageInfo*  info,float angle,DWORD flag)
{
	int cx,cy;
	if(flag==CENTRE)
	{
		cx=info->width/2.0f;
		cy=info->height/2.0f;
	}
	else if(flag==UPPERLEFT)
	{
		cx=0;
		cy=0;
	}
	D3DXVECTOR3 v3[5]=
	{
		
		D3DXVECTOR3(info->beginX,  info->beginY,info->Z),
		D3DXVECTOR3((info->beginX+info->width),  info->beginY, info->Z),
		D3DXVECTOR3(info->beginX,  (info->beginY-info->height),info->Z),
		D3DXVECTOR3((info->beginX+info->width), (info->beginY-info->height), info->Z),
		D3DXVECTOR3((info->beginX+cx), (info->beginY-cy),info->Z),
	};
	if(angle!=0)
	{
		D3DXMATRIX mTra;
		//D3DXMatrixIdentity( &mTra ); 
		D3DXMATRIX mMov=D3DXMATRIX
		(
		1,0,0,0,
		0,1,0,0,
		0,0,1,0,
		-v3[4].x,-v3[4].y,-v3[4].z,1
		);

		D3DXMatrixRotationZ(&mTra,-angle*3.1415f/180.0f);
		D3DXMatrixMultiply(&mTra,&mMov,&mTra);
		mMov=D3DXMATRIX
		(
		1,0,0,0,
		0,1,0,0,
		0,0,1,0,
		v3[4].x,v3[4].y,v3[4].z,1
		);
		D3DXMatrixMultiply(&mTra,&mTra,&mMov);

		for(int i=0;i<4;i++)
		{
			D3DXVec3TransformCoord(&v3[i],&v3[i],&mTra);
		}
	}

	CUSTOMVERTEX*  vertices =new CUSTOMVERTEX[6];
	vertices[0]=CUSTOMVERTEX( v3[0],  info->uvX,info->uvY);
	vertices[1]=CUSTOMVERTEX( v3[1],  info->uvX+info->uvW,info->uvY);
	vertices[2]=CUSTOMVERTEX( v3[2],  info->uvX,info->uvY+info->uvH );
	vertices[3]=vertices[1];
	vertices[4]=CUSTOMVERTEX( v3[3],  info->uvX+info->uvW,info->uvY+info->uvH );
	vertices[5]=vertices[2];
	DrawImage(vertices,info->Z,6, info->pTexture,TRANSPARENT|RELEASEVTONEND);
	//if( FAILED( g_pd3dDevice->CreateVertexBuffer( 4 * sizeof(CUSTOMVERTEX),
	//	D3DUSAGE_WRITEONLY, CUSTOMVERTEX::D3DFVF_CUSTOMVERTEX, D3DPOOL_DEFAULT, &m_pVB, NULL ) ) )
	//	return false;

	//VOID* pVertices;
	//if( FAILED( m_pVB->Lock( 0, sizeof( vertices ), ( void** )&pVertices, 0 ) ) )
	//	return false;
	//memcpy( pVertices, vertices, sizeof( vertices ) );
	//m_pVB->Unlock();

	//g_pd3dDevice->SetTexture( 0, info->pTexture );

	////defaultState();
	//

	//g_pd3dDevice->SetFVF( CUSTOMVERTEX::D3DFVF_CUSTOMVERTEX );

	//// Rendering of scene objects can happen here
	//g_pd3dDevice->SetStreamSource( 0, m_pVB, 0, sizeof( CUSTOMVERTEX ) );
	//if( FAILED( g_pd3dDevice->DrawPrimitive( D3DPT_TRIANGLESTRIP,0,2)))
	//	return false;
	return true;
}
void Graphic::RenderList()
{
	if(DrawInfo::TotalLenght > m_vbLastLen)
	{

		release_com(m_pVB);

		if( FAILED( g_pd3dDevice->CreateVertexBuffer( DrawInfo::TotalLenght * sizeof(CUSTOMVERTEX),
			D3DUSAGE_WRITEONLY|D3DUSAGE_DYNAMIC, CUSTOMVERTEX::D3DFVF_CUSTOMVERTEX, D3DPOOL_DEFAULT, &m_pVB, NULL ) ) )
			goto ends;

		m_vbLastLen=DrawInfo::TotalLenght;
	}

	UINT count1;
	UINT count2;
	UINT lenList1[1000];
	UINT lenList2[1000];
	LPDIRECT3DTEXTURE9 texList1[1000];
	LPDIRECT3DTEXTURE9 texList2[1000];
	void* pVertices;

	if( FAILED( m_pVB->Lock( 0,DrawInfo::TotalLenght * sizeof(CUSTOMVERTEX), ( void** )&pVertices, 0 ) ) )
		goto ends;

	count1=CopyData(&pVertices,firstNodeTran,lenList1,texList1);
	count2=CopyData(&pVertices,firstNodeNoTr,lenList2,texList2);

	m_pVB->Unlock();

	if( FAILED(g_pd3dDevice->SetStreamSource( 0, m_pVB, 0, sizeof( CUSTOMVERTEX ) )))
		goto ends;
	//g_pd3dDevice->SetFVF( CUSTOMVERTEX::D3DFVF_CUSTOMVERTEX );

	g_pd3dDevice->SetRenderState(D3DRS_ALPHABLENDENABLE,TRUE);
	UINT offset=0;
	RenderData(&offset,count1,lenList1,texList1);
	g_pd3dDevice->SetRenderState(D3DRS_ALPHABLENDENABLE,FALSE);
	RenderData(&offset,count2,lenList2,texList2);


ends:
	ReleaseList(firstNodeTran);
	ReleaseList(firstNodeNoTr);
	firstNodeTran=0;
	firstNodeNoTr=0;

	DrawInfo::TotalLenght=0;

	return;
}
void Graphic::ReleaseList(DrawInfo* node)
{
	DrawInfo* temp;
	while(node)
	{
		temp=node->next;
		delete node;
		node=temp;
	}
}


void Graphic::RenderData(UINT* offset,UINT count,UINT* lenList,LPDIRECT3DTEXTURE9* texList)
{
	for(UINT i=0;i<count;i++)
	{
		if( FAILED(g_pd3dDevice->SetTexture( 0,texList[i])))
			goto ends;
		//int a=lenList[i];
		if( FAILED(g_pd3dDevice->DrawPrimitive(D3DPT_TRIANGLELIST,*offset,lenList[i]/3)))
			goto ends ;

		*offset+=lenList[i];
	}
ends:
	return;
}
UINT Graphic::CopyData(void** vp,DrawInfo* node,UINT* lenList,LPDIRECT3DTEXTURE9* texList)
{
	UINT count=0;
	UINT lenght=0;
	while(node)
	{
		lenght+=node->length;
		memcpy(*vp, node->p_vertex,node->length*sizeof(CUSTOMVERTEX));
		*vp=(CUSTOMVERTEX*)*vp+node->length;
		if(node->next==0 || node->tex!=node->next->tex)
		{
			lenList[count]=lenght;
			texList[count]=node->tex;
			count++;
			lenght=0;
		}
		node=node->next;
	}
	return count;
}
bool Graphic::DrawImage(CUSTOMVERTEX* vertex,int depth,UINT length,LPDIRECT3DTEXTURE9 texture,DWORD flag)
{
	/*if(flag&0x100)
	{*/
		DrawInfo* info=new DrawInfo();
		info->p_vertex=vertex;
		info->Z=depth;
		info->flag=flag;
		info->tex=texture;
		info->length=length;
		DrawInfo::TotalLenght+=length;
		if(flag&TRANSPARENT)
		{
			AddList(&firstNodeTran,info);
		}
		else
		{
			AddList(&firstNodeNoTr,info);
		}
	//}
	return true;
}
void Graphic::AddList(DrawInfo** ListHead,DrawInfo* info)
{
	DrawInfo* node;
	node=*ListHead;
	if(node==0 || info->Z > node->Z)
	{
		info->next=node;
		*ListHead=info;

		goto ends;
	}
	while(node->next)
	{
		if(info->Z > node->next->Z || (info->Z == node->next->Z&&info->tex==node->next->tex ))
		{
			info->next=node->next;
			node->next=info;
			goto ends;
		}
		node=node->next;
	}
	node->next=info;
ends:
	return;
}