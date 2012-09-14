#include "Graphic.h"
#include "GameManager.h"
#include "BackgroundAnimation.h"
#include <CEGUI.h>
//#include <crtdbg.h>
#include <windows.h>
#include <d3dx9.h>

#include "Header.h"

#pragma comment (lib,"d3d9.lib")
#pragma comment (lib,"d3dx9.lib")
#pragma comment (lib,"winmm.lib")

GameManager* manager;

HINSTANCE   g_hInst = NULL;
HWND        g_hWnd = NULL;


HRESULT InitWindow( HINSTANCE hInstance, int nCmdShow );
LRESULT CALLBACK    WndProc( HWND, UINT, WPARAM, LPARAM );
void Exit();
//--------------------------------------------------------------------------------------
// Entry point to the program. Initializes everything and goes into a message processing 
// loop. Idle time is used to render the scene.
//--------------------------------------------------------------------------------------
int WINAPI wWinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow )
{
	//_CrtSetDbgFlag ( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );
	//atexit(Exit);

    UNREFERENCED_PARAMETER( hPrevInstance );
    UNREFERENCED_PARAMETER( lpCmdLine );

    if( FAILED( InitWindow( hInstance, nCmdShow ) ) )
        return 0;

	ShowWindow( g_hWnd, nCmdShow );
	UpdateWindow( g_hWnd );


	manager=GameManager::initManager(g_hWnd);
	/////////////
	// Main message loop
	MSG msg;
	ZeroMemory( &msg, sizeof( msg ) );
	while(msg.message!=WM_QUIT)
	{
		if(PeekMessage( &msg, NULL, 0U, 0U, PM_REMOVE ) )
		{
			TranslateMessage( &msg );
			DispatchMessage( &msg );
		}
		else
		{
			manager->Frame();
		}
		//_CrtDumpMemoryLeaks();
	}

	return 0;
}

template<class T> void Release(T t)
{
	if(t!=0)
	{
		delete t;
		t=0;
	}
}
void Exit()
{
    int i = _CrtDumpMemoryLeaks();//有内存泄露时返回true
    assert( i == 0);
}
//--------------------------------------------------------------------------------------
// Register class and create window
//--------------------------------------------------------------------------------------
HRESULT InitWindow( HINSTANCE hInstance, int nCmdShow )
{
    // Register class
    WNDCLASSEX wcex;
    wcex.cbSize = sizeof( WNDCLASSEX );
    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = WndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = LoadIcon( hInstance, 0);
    wcex.hCursor = LoadCursor( NULL, IDC_ARROW );
    wcex.hbrBackground = ( HBRUSH )( COLOR_WINDOW + 1 );
    wcex.lpszMenuName = NULL;
    wcex.lpszClassName = L"TutorialWindowClass";
    wcex.hIconSm = LoadIcon( wcex.hInstance, 0);
    if( !RegisterClassEx( &wcex ) )
        return E_FAIL;

    // Create window
    g_hInst = hInstance;
   // RECT rc = { 0, 0, 640, 480 };
   // AdjustWindowRect( &rc, WS_OVERLAPPEDWINDOW, FALSE );
    g_hWnd = CreateWindow( L"TutorialWindowClass", L"Welcome", WS_POPUP,
                           CW_USEDEFAULT, CW_USEDEFAULT, 1000,600, NULL, NULL, hInstance,
                           NULL );
    if( !g_hWnd )
        return E_FAIL;



    return S_OK;
}

//--------------------------------------------------------------------------------------
// Called every time the application receives a message
//--------------------------------------------------------------------------------------
LRESULT CALLBACK WndProc( HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam )
{
	if(manager)
	{
		if(manager->winProc(  hWnd,  message,  wParam,  lParam))
			goto ends;
	}

	switch( message )
	{
		/* case WM_PAINT:
		break;*/
	case   WM_CREATE: 

		break;
	case WM_DESTROY:
		VOID Cleanup();
		PostQuitMessage( 0 );
		break;
	default:
		return DefWindowProc( hWnd, message, wParam, lParam );
	}

ends:
	return 0;
}
