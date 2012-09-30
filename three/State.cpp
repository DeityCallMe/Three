#include "State.h"

#include "Header.h"
BackgroundAnimation* MainState::_background=0;
State::State()
{
}
State::~State()
{
	
}

ImmediateData* MainState::data=ImmediateData::immediateData;
MainState::MainState(Graphic* graphic)
	:m_LastClickTime(0),elapseTime(0)
{
	if(_background==NULL)
		_background=new BackgroundAnimation(graphic);
}
MainState::~MainState()
{

}
void MainState::upFra(UINT user,UINT index)
{
	int fraction=data->settingData.beginWash;
	if (index == 0)
		fraction /=10;
	data->recordData.userFraction[user]+=fraction;
}
UINT MainState::getDigit(UINT n)
{
	UINT i = 0;
	for (; n >= 1; i++)
	{
		n = n / 10;
	}
	return i;
}
void MainState::downFra(UINT user)
{
	int currentFra=data->recordData.userFraction[user]-data->realdata.betFraction[user];
	if (currentFra> 0)
	{
		int i = getDigit(currentFra);
		if ((int)(currentFra/ pow(10.0f, i -1)) == 10 && currentFra >= 10)
		{
			i--;
		}
		int t = (int)(pow(10.0f, i - 1));
		data->recordData.userFraction[user] -= t;
		//myUser[user].downFraction += t;
		//Game1.data.alldown[user] += t;
		//smallDown += t;
	}

}
void MainState::GeneralConsole(BYTE* data,UINT bytes)
{
	GameManager* game=GameManager::GetGame();
	if(bytes!=8||!game)
		goto ret;
	UINT user=data[1];
	if (user > 8)
		goto ret;

	switch (data[4])
	{ //取消
	case 0xEF:
		{
			game->clearBet(user);
			break;
		}

	case 0xF7:
		{
			//转换
			if(data[3]==0xFF)
			{
				game->change(user);
			}
			//出币键
			else if(data[3]==0xFE)
			{

			}
			break;
		}
		//上分线2
	case 0x7F:
		{
			upFra(user,0);

			break;
		}
	case 0xFF:
		{
			//上分线1
			if (data[3] == 0xFE)
			{
				upFra(user,1);
			}
			//下分线
			else if (data[3] == 0xFD)
			{
				downFra(user);
			}
			break;
		}
	}

ret:
	return;
}
void MainState::GeneralRender(Context* context ,int time,Graphic* graphic)
{
	_background->Render(time,graphic);
	DInput* input=DInput::InitializeDInput();
	if(input!=0)
	{
		DIDEVICEOBJECTDATA  didod;  // Receives buffered data
		DWORD               dwElements=1;
		HRESULT             hr;

		while(dwElements)
		{
			dwElements = 1;                     // 每次从缓冲区中读一个数据
			hr = input->m_mouseDevice->GetDeviceData(sizeof(DIDEVICEOBJECTDATA), &didod, &dwElements, 0);

			if FAILED(hr)
			{
				// 发生了一个错误
				if(hr == DIERR_INPUTLOST||hr==DIERR_NOTACQUIRED)
				{
					hr = input->m_mouseDevice->Acquire();    // 试图重新取回设备
					if FAILED(hr)
					{
						break;         // 失败
					}
				}
				else
				{
					break; 
				}
			}
			else if(dwElements == 1)
			{
				switch(didod.dwOfs)
				{
				case DIMOFS_X:              // X 轴偏移量
					// didod.dwData 里是具体偏移相对值，单位为像素
					break;
				case DIMOFS_Y:              // Y 轴偏移量
					// didod.dwData 里是具体偏移相对值，单位为像素
					break;
				case DIMOFS_BUTTON0:        // 0 号键（左键）状态
					// didod.dwData 里是具体状态值
					// 低字节最高位为 1 则表示按下
					// 低字节最高位为 0 表示未按下
					if((didod.dwTimeStamp-m_LastClickTime)<=300&&(didod.dwData&0x80))
					{
						input->m_mouseDevice->Unacquire();
						input->NoNexclusive();
						context->changeState(new StateSetting(graphic),SAVE);
						SetCursorPos(480,350);
					}
					m_LastClickTime=didod.dwTimeStamp;
					break;
				case DIMOFS_BUTTON1:        // 1 号键（右键）状态
					// 同上
					break;
				case DIMOFS_BUTTON2:        // 2 号键（中键）状态
					// 同上
					break;
				case DIMOFS_BUTTON3:        // 3 号键状态
					// 同上
					break;
				}
			}
		}
	}
}
StateBegin::StateBegin(Graphic* graphic)
	:MainState(graphic)
{
	ImmediateData* data=ImmediateData::immediateData;
	data->realdata.view=0;
	data->realdata.bureauTimes=0;
	memcpy(data->realdata.currentRecord,data->recordData.record[data->recordData.wheelTimes],100);
	data->recordData.wheelTimes++;
}
StateBegin::~StateBegin()
{

}
void StateBegin::frame(Context* context,int time,Graphic* graphic)
{
	GeneralRender(context,time,graphic);
	ImmediateData* data=ImmediateData::immediateData;
	elapseTime+=time;
	if(elapseTime>=1000)
	{
		data->realdata.countdown++;
		if(data->realdata.countdown>=data->settingData.intervalTime)
		{
			context->changeState(new StateBetDown(graphic));
			data->realdata.countdown=0;
		}
		elapseTime-=1000;
	}
}
void StateBegin::console(BYTE* data,UINT bytes)
{
	GameManager* game=GameManager::GetGame();
	if(bytes!=8||!game)
		goto ret;

	UINT user=data[1];
	if (user <= 8)
	{	//快速开始游戏
		if(data[4]==0x87)
		{

		}
	}
	MainState::GeneralConsole(data,bytes);
ret:
	return;
}
StateBetDown::StateBetDown(Graphic* graphic )
	:MainState(graphic)
{
	ImmediateData* data=ImmediateData::immediateData;
	data->realdata.bureauTimes++;
}

StateBetDown::~StateBetDown()
{

}
void StateBetDown::frame(Context* context,int time,Graphic* graphic)
{
	GeneralRender(context,time,graphic);
	ImmediateData* data=ImmediateData::immediateData;
	elapseTime+=time;
	if(elapseTime>=1000)
	{
		data->realdata.prizeGold=rand()%(data->settingData.lagerGold-data->settingData.smallGold)+data->settingData.smallGold;
		data->realdata.countdown++;
		if(data->realdata.countdown>=data->settingData.detainTime)
		{
			context->changeState(new StateView(graphic));
			data->realdata.countdown=0;
		}
		elapseTime-=1000;
	}
}
void StateBetDown::console(BYTE* data,UINT bytes)
{



}
StateView::StateView(Graphic* graphic )
	:MainState(graphic)
{

	ImmediateData* data=ImmediateData::immediateData;
	//data->realdata.bureauTimes++;
	int view=data->realdata.view;
	UINT design=data->realdata.currentRecord[view];
	
	if(design<4)
	{
		_background->SetPoker(rand()%13,POKER);
	}
	else
	{
		_background->SetPoker(rand()%2,POKER);
	}

	_background->DrawPoker=FRONT;
	_background->SetPoker(design,DESIGN);


}
StateView::~StateView()
{
	ImmediateData* data=ImmediateData::immediateData;
	data->realdata.view++;
	_background->DrawPoker=BACKSIDE;
	_background->SetPoker(rand()%20,BACKSIDE);
}
void StateView::console(BYTE* data,UINT bytes)
{

}
void StateView::frame(Context* context,int time,Graphic* graphic)
{
	GeneralRender(context,time,graphic);
	ImmediateData* data=ImmediateData::immediateData;
	elapseTime+=time;
	if(elapseTime>=1000)
	{
		data->realdata.countdown++;
		if(data->realdata.countdown>=data->settingData.detainTime)
		{
			if(data->realdata.bureauTimes<100)
			{
				context->changeState(new StateBetDown(graphic));
				
			}
			else
			{
				context->changeState(new StateBegin(graphic));
			}
			data->realdata.countdown=0;
		}
		elapseTime-=1000;
	}
}

StateSetting::StateSetting(Graphic* graphic)
{
	m_gui=new SettingGUI(graphic->g_pd3dDevice);
	m_gui->onExitCall(&StateSetting::exitSetting,this);
}
StateSetting::~StateSetting()
{
	delete m_gui;
	Graphic::InitializeGraphic()->defaultState();
	DInput::InitializeDInput()->Nexclusive();
	//DInput::InitializeDInput()->m_mouseDevice->Acquire();
}
void StateSetting::exitSetting()
{
	State* oldState;
	Context* context=Context::InitializeContext();
	context->popState(&oldState);
	context->changeState(oldState);
}
void StateSetting::console(BYTE* data,UINT bytes)
{

}
void StateSetting::frame(Context* context,int time,Graphic* graphic)
{
	GUI::InitializeGUI()->renderGUI();
	DInput* input=DInput::InitializeDInput();
	if(input!=0)
	{
		DIDEVICEOBJECTDATA devDat;
		DWORD itemCount = 1;

		HRESULT res = input->m_keyboardDevice->GetDeviceData(sizeof(DIDEVICEOBJECTDATA), &devDat, &itemCount, 0);

		if (SUCCEEDED(res))
		{
			if (itemCount > 0)
			{
				if (LOBYTE(devDat.dwData) & 0x80)
				{
					// force quit on ESCAPE key
					if (devDat.dwOfs == CEGUI::Key::Escape)
					{
						//PostQuitMessage(0);
						exitSetting();
					}
					else
					{
						CEGUI::System::getSingleton().injectKeyDown(devDat.dwOfs);
					}

				}
				else
				{
					CEGUI::System::getSingleton().injectKeyUp(devDat.dwOfs);
				}

			}
		}
		else
		{
			// try to re-acquire device if that was the cause of the error.
			if ((res == DIERR_NOTACQUIRED) || (res == DIERR_INPUTLOST))
			{
				//input->Nexclusive();
				input->m_keyboardDevice->Acquire();

				//int a=0;
			}

		}
	}
}