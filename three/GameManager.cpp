#include "GameManager.h"
#include "Header.h"
GameManager* GameManager::gameManager=0;
GameManager::GameManager(HWND h)
	:hWnd(h),d_mouseInWindow(false)
{

	srand((unsigned) time(NULL)); /*播种子*/ 

	InitializeCriticalSection(&g_csThreadCode);
	pGraphic=Graphic::InitializeGraphic(h);
	GUI::InitializeGUI(pGraphic->g_pd3dDevice);
	ImmediateData::immediateData=new ImmediateData();

	DInput::InitializeDInput(h);

	Sound::InitializeSound();


}
GameManager* GameManager::initManager(HWND h)
{
	if(gameManager==0)
	{
		gameManager=new GameManager(h);
		gameManager->Initialize();
	}
	return gameManager;
}
GameManager::~GameManager()
{
	DeleteCriticalSection(&g_csThreadCode);  
	pGraphic->ReleaseGraphic();
}
void GameManager::Initialize()
{
	tPre= GetTickCount();

	if(!m_SerialPort.InitPort(3))
	{
		//MessageBox(NULL,_T("初始化串口失败"),_T("错误"),0);
	}
	if(!m_SerialPort.OpenListenThread())
	{
		//MessageBox(NULL,_T("创建监听进程失败"),_T("错误"),0);
	}
	m_SerialPort.DataReceived=DataReceived;

	Context::InitializeContext(new StateBegin(pGraphic),pGraphic);

	
}

void GameManager::DataReceived(SerialPort* serialPort)
{
	UINT BytesInQue = serialPort->GetBytesInCOM();  
	UINT count=BytesInQue;
	UINT read;
	BYTE* bRecved=new BYTE(BytesInQue);
	do 
	{  
		read=serialPort->ReadByte(*bRecved,count);
	}while(count-=read);  
	Context::InitializeContext()->GetState()->console(bRecved,BytesInQue);
	delete[] bRecved;
}
Graphic* GameManager::GetGraphic()
{
	Graphic* graphicRet;
	if(gameManager!=0)
	{
		graphicRet= gameManager->pGraphic;
	}
	return graphicRet;
}
void GameManager::Frame()
{
	tNow = GetTickCount();
	if(tNow-tPre >= 50)        //当此次循环运行与上次绘图时间相差0.05秒时再进行重绘操作  
	{

		pGraphic->render(tNow-tPre);
		tPre=tNow;
	}
}

void GameManager::mouseEnters(void)
{
	 EnterCriticalSection(&g_csThreadCode);
    if (!d_mouseInWindow)
    {
        d_mouseInWindow = true;
        ShowCursor(false);
    }
	LeaveCriticalSection(&g_csThreadCode);
}

void GameManager::mouseLeaves(void)
{
	 EnterCriticalSection(&g_csThreadCode);
    if (d_mouseInWindow)
    {
        d_mouseInWindow = false;
        ShowCursor(true);
    }
	LeaveCriticalSection(&g_csThreadCode);
}


bool GameManager::winProc( HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam )
{
	 switch(message)
    {
    case WM_CHAR:
        CEGUI::System::getSingleton().injectChar((CEGUI::utf32)wParam);
        break;

    case WM_MOUSELEAVE:
        mouseLeaves();
        break;

    case WM_NCMOUSEMOVE:
        mouseLeaves();
        break;

    case WM_MOUSEMOVE:
        mouseEnters();
		///////////////////////
		TRACKMOUSEEVENT tme;
		tme.cbSize =sizeof( tme);
		tme.dwFlags =TME_LEAVE;
		tme.dwHoverTime =HOVER_DEFAULT /*HOVER_DEFAULT*/;
		tme.hwndTrack =hWnd;
		TrackMouseEvent( &tme);
		///////////////////////
        CEGUI::System::getSingleton().injectMousePosition((float)(LOWORD(lParam)), (float)(HIWORD(lParam)));
        break;

    case WM_LBUTTONDOWN:
        CEGUI::System::getSingleton().injectMouseButtonDown(CEGUI::LeftButton);
        break;

    case WM_LBUTTONUP:
        CEGUI::System::getSingleton().injectMouseButtonUp(CEGUI::LeftButton);
        break;

    case WM_RBUTTONDOWN:
        CEGUI::System::getSingleton().injectMouseButtonDown(CEGUI::RightButton);
        break;

    case WM_RBUTTONUP:
        CEGUI::System::getSingleton().injectMouseButtonUp(CEGUI::RightButton);
        break;

    case WM_MBUTTONDOWN:
        CEGUI::System::getSingleton().injectMouseButtonDown(CEGUI::MiddleButton);
        break;

    case WM_MBUTTONUP:
        CEGUI::System::getSingleton().injectMouseButtonUp(CEGUI::MiddleButton);
        break;
    case 0x020A: // WM_MOUSEWHEEL:
        CEGUI::System::getSingleton().injectMouseWheelChange(static_cast<float>((short)HIWORD(wParam)) / static_cast<float>(120));
        break;
    case WM_SIZE:
        {
            // get CEGUI::System as a pointer so we can detect if it's not
            // instantiated yet.
            CEGUI::System* cegui_system = CEGUI::System::getSingletonPtr();

            // only continue if CEGUI is up an running and window was not
            // minimised (else it's just a waste of time)
            if ((cegui_system != 0) && (wParam != SIZE_MINIMIZED))
            {
                // get renderer identification string
                CEGUI::Renderer* renderer = cegui_system->getRenderer();
                CEGUI::String id(renderer->getIdentifierString());

                // invoke correct function based on the renderer we have ID'd
#ifdef CEGUI_SAMPLES_USE_DIRECTX_9
                if (id.find("Official Direct3D 9") != id.npos)
                    DeviceReset_Direct3D9(hWnd, renderer);
#endif
#ifdef CEGUI_SAMPLES_USE_DIRECTX_10
                if (id.find("Official Direct3D 10") != id.npos)
                    DeviceReset_Direct3D10(hWnd, renderer);
#endif
#ifdef CEGUI_SAMPLES_USE_DIRECTX_8
                if (id.find("Official Direct3D 8.1") != id.npos)
                    DeviceReset_Direct3D81(hWnd, renderer);
#endif
            }
        }
        break;
    default:
		break;
	 }

ends:
	 return false;
}


void GameManager::upFra(UINT user,UINT mode)
{


}

void GameManager::bet(UINT user,UINT poker)
{



}
void GameManager::change(UINT user)
{

}
void GameManager::clearBet(UINT user)
{


}
GameManager* GameManager::GetGame()
{
	return gameManager;
}