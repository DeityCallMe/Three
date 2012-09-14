#include "DInput.h"
#include "Header.h"
DInput* DInput::soleDInput=0;
DInput::DInput()
{

}
DInput::~DInput()
{
	m_keyboardDevice->Unacquire();
	m_keyboardDevice->Release();

	m_mouseDevice->Unacquire();
	m_mouseDevice->Release();

	m_directInput->Release();
}
DInput* DInput::InitializeDInput(HWND window)
{
	if(window==0)
		goto ends;
	if(soleDInput!=0)
		goto ends;

	soleDInput=new DInput();
	if(!soleDInput->initialize(window))
	{
		delete soleDInput;
		soleDInput=0;
	}
ends:
	return soleDInput;
}
bool DInput::initialize(HWND window)
{
	w=window;
	bool result=false;
	if (!SUCCEEDED(DirectInput8Create(GetModuleHandle(0), DIRECTINPUT_VERSION, IID_IDirectInput8, (LPVOID*)&m_directInput, 0)))
		goto ends;
	if (!SUCCEEDED(m_directInput->CreateDevice(GUID_SysKeyboard, &m_keyboardDevice, 0)))
		goto ends;
	if (!SUCCEEDED(m_keyboardDevice->SetDataFormat(&c_dfDIKeyboard)))
		goto ends;
	if (!SUCCEEDED(m_keyboardDevice->SetCooperativeLevel(window, DISCL_FOREGROUND|DISCL_NONEXCLUSIVE)))
		goto ends;

	if (!SUCCEEDED(m_directInput->CreateDevice(GUID_SysMouse, &m_mouseDevice, 0)))
		goto ends;
	if (!SUCCEEDED(m_mouseDevice->SetDataFormat(&c_dfDIMouse)))
		goto ends;
	if (!SUCCEEDED(m_mouseDevice->SetCooperativeLevel(window, DISCL_EXCLUSIVE | DISCL_FOREGROUND)))
		goto ends;
	//NoNexclusive();

	DIPROPDWORD     pro;

    pro.diph.dwSize = sizeof(DIPROPDWORD);
    pro.diph.dwHeaderSize = sizeof(DIPROPHEADER);
    pro.diph.dwObj = 0;
    pro.diph.dwHow = DIPH_DEVICE;
    pro.dwData = 16;

	if (!SUCCEEDED(m_mouseDevice->SetProperty(DIPROP_BUFFERSIZE, &pro.diph)))
		goto ends;

	DIPROPDWORD inputProp;
	// the header
	inputProp.diph.dwSize       = sizeof(DIPROPDWORD);
	inputProp.diph.dwHeaderSize = sizeof(DIPROPHEADER);
	inputProp.diph.dwObj        = 0;
	inputProp.diph.dwHow        = DIPH_DEVICE;
	inputProp.dwData            = 16;

	if (!SUCCEEDED(m_keyboardDevice->SetProperty(DIPROP_BUFFERSIZE, &inputProp.diph)))
			goto ends;

	m_keyboardDevice->Acquire();
	m_mouseDevice->Acquire();

	result=true;
ends:
	return result;
}
bool DInput::NoNexclusive()
{
	m_mouseDevice->Unacquire();
	bool result=false;
	if ( SUCCEEDED( m_mouseDevice->SetCooperativeLevel(w, DISCL_NONEXCLUSIVE | DISCL_FOREGROUND) ) )
		result= true;
	m_mouseDevice->Acquire();
	return result;
}
bool DInput::Nexclusive()
{
	bool result=false;
	m_mouseDevice->Unacquire();
	if ( SUCCEEDED( m_mouseDevice->SetCooperativeLevel(w, DISCL_EXCLUSIVE | DISCL_FOREGROUND) ) )
	{
		m_isNexclusive=true;
		result= true;
	}
	m_mouseDevice->Acquire();
	return result;
}