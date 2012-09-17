#include "SettingGUI.h"
#include "Header.h"
using namespace CEGUI;


SettingGUI::SettingGUI(LPDIRECT3DDEVICE9 d3ddevice)
	:gCall(0),m_thread(0),m_nameConut(0)
{


	initEnter();
}
SettingGUI::~SettingGUI()
{
	delete gCall;
	WindowManager& wmgr = WindowManager::getSingleton();
	wmgr.destroyAllWindows();

	if(m_thread)
		CloseHandle(m_thread);
}
void SettingGUI::initEnter()
{
	WindowManager& wmgr = WindowManager::getSingleton();

	Window* myRoot = wmgr.createWindow( "DefaultWindow", "root" );
	System::getSingleton().setGUISheet( myRoot );

	SchemeManager::getSingleton().create("Me.scheme");


	System::getSingleton().setDefaultMouseCursor("OgreTrayImages", "MouseArrow");

	FrameWindow* fWnd = static_cast<FrameWindow*>(
		wmgr.createWindow( "OgreTray/FrameWindow", "testWindow" ));

	myRoot->addChildWindow( fWnd );



	ToUTF8(_T("请输入密码"),buff);

	fWnd->setPosition( UVector2( UDim( 0.25f, 0 ), UDim( 0.25f, 0 ) ) );

	fWnd->setSize( UVector2( UDim( 0.5f, 0 ), UDim( 0.5f, 0 ) ) );
	fWnd->setText((utf8*)buff);

	
	Editbox* pwBox = static_cast<Editbox*>(
		wmgr.createWindow( "OgreTray/Editbox", "passwordBox" ));
	fWnd->addChildWindow( pwBox );
	pwBox->setPosition( UVector2( UDim( 0.1f, 0 ), UDim( 0.35f, 0 ) ) );

	pwBox->setSize( UVector2( UDim( 0.8f, 0 ), UDim( 0.2f, 0 ) ) );
	pwBox->setText("password");
	pwBox->setTextMasked(true);
	pwBox->setMaxTextLength(9);
	pwBox->setCaratIndex(5);
	pwBox->setValidationString("[0-9]*");

	ButtonBase* enBt = static_cast<ButtonBase*>(
	wmgr.createWindow( "OgreTray/Button", "enter" ));
	fWnd->addChildWindow( enBt );
	enBt->setPosition( UVector2( UDim( 0.1f, 0 ), UDim( 0.7f, 0 ) ) );

	enBt->setSize( UVector2( UDim( 0.3f, 0 ), UDim( 0.2f, 0 ) ) );
	ToUTF8(_T("确定"),buff);


	enBt->setText((utf8*)buff);

	enBt->subscribeEvent(ButtonBase::EventMouseClick,Event::Subscriber(&SettingGUI::setting,this));


	ButtonBase* exBt = static_cast<ButtonBase*>(
		wmgr.createWindow( "OgreTray/Button", "exit" ));
	fWnd->addChildWindow( exBt );
	exBt->setPosition( UVector2( UDim( 0.6f, 0 ), UDim( 0.7f, 0 ) ) );

	exBt->setSize( UVector2( UDim( 0.3f, 0 ), UDim( 0.2f, 0 ) ) );
	ToUTF8(_T("退出"),buff);


	exBt->setText((utf8*)buff);

	exBt->subscribeEvent(ButtonBase::EventMouseClick,Event::Subscriber(&SettingGUI::exit,this));

	DefaultWindow* erText = static_cast<DefaultWindow*>(
		wmgr.createWindow( "OgreTray/StaticText", "passwordError" ));
	fWnd->addChildWindow( erText );
	erText->setPosition( UVector2( UDim( 0.32f, 0 ), UDim( 0.07f, 0 ) ) );

	erText->setSize( UVector2( UDim( 0.36f, 0 ), UDim( 0.22f, 0 ) ) );
	ToUTF8(_T("密码错误"),buff);
	erText->setText((utf8*)buff);
	erText->setVisible(false);

	//delete[] buff;


}

void SettingGUI::ToUTF8(TCHAR* bec,char* buff)
{
#ifdef UNICODE
	//UINT nNeedLenOfMultiStr=WideCharToMultiByte( CP_UTF8, 0, bec, -1, 0, 0, 0, 0);
	//buff=new char[nNeedLenOfMultiStr];
	WideCharToMultiByte( CP_UTF8, 0, bec, -1, buff, 128, 0, 0);
#else
	///
	warning
#endif

}
void SettingGUI::musicToList(TCHAR* music)
{
	WindowManager& wmgr = WindowManager::getSingleton();
	

	//char name[11]="MusicItem0";
	ItemListbox* list1=static_cast<ItemListbox*>(wmgr.getWindow("MusicList"));
	ToUTF8(music,buff);
	ItemEntry* item=static_cast<ItemEntry*>(wmgr.createWindow( "OgreTray/ListboxItem",buff));
	list1->addItem(item);

	item->setText((utf8*)buff);
		//item->setFont();
}

bool SettingGUI::setting(const CEGUI::EventArgs& args)
{
	ImmediateData* data=ImmediateData::immediateData;
	WindowManager& wmgr = WindowManager::getSingleton();
	if(!strcmp(data->settingData.password,wmgr.getWindow("passwordBox")->getText().c_str()))
	{
		wmgr.destroyAllWindows();
		System::getSingleton().setGUISheet(wmgr.loadWindowLayout("MyLayout.layout"));
		//ItemListbox* list1=static_cast<ItemListbox*>(wmgr.getWindow("list1"));
		//ItemEntry* item=static_cast<ItemEntry*>(wmgr.createWindow( "OgreTray/ListboxItem", "123456" ));
		//list1->addItem(item);
		//item->setText("123456789");

		//item=static_cast<ItemEntry*>(wmgr.createWindow( "OgreTray/ListboxItem", "000" ));
		//list1->addItem(item);
		//item->setText("00000");

		//item=static_cast<ItemEntry*>(wmgr.createWindow( "OgreTray/ListboxItem", "111" ));
		//list1->addItem(item);
		//item->setText("111111");

		initSetting();
		
	}
	else
	{
		wmgr.getWindow("passwordError")->setVisible(true);
	}
	return true;
}
void SettingGUI::initSetting()
{
	ImmediateData* data=ImmediateData::immediateData;

	WindowManager& wmgr = WindowManager::getSingleton();
	Combobox* modeList=static_cast<Combobox*>(wmgr.getWindow("Mode"));

	ItemListbox* list1=static_cast<ItemListbox*>(wmgr.getWindow("MusicList"));
	//list1->setProperty("MultiSelect","True");

	

	//char name[11]="MusicItem0";
	for(UINT i=0;i<data->realdata.numberOfMusic;i++)
	{
		//name[10]=i+'0';
	
		//ToUTF8(data->realdata.music[i],buff);
		//ItemEntry* item=static_cast<ItemEntry*>(wmgr.createWindow( "OgreTray/ListboxItem",buff));
		//list1->addItem(item);

		//item->setText((utf8*)buff);
		musicToList(data->realdata.music[i]);
		//item->setFont();
	}



	ButtonBase* adBt = static_cast<ButtonBase*>(wmgr.getWindow("AddMusic"));

	adBt->subscribeEvent(ButtonBase::EventMouseClick,Event::Subscriber(&SettingGUI::AddMusic,this));

	ButtonBase* reBt = static_cast<ButtonBase*>(wmgr.getWindow("RemoveMusic"));

	reBt->subscribeEvent(ButtonBase::EventMouseClick,Event::Subscriber(&SettingGUI::RemoveMusic,this));
}
bool SettingGUI::RemoveMusic(const CEGUI::EventArgs& args)
{
	TCHAR szCurDir[MAX_PATH]; 
	GetCurrentDirectory(sizeof(szCurDir),szCurDir); 
	lstrcat(szCurDir,_T("\\Music\\"));
	WindowManager& wmgr = WindowManager::getSingleton();
	ItemListbox* list1=static_cast<ItemListbox*>(wmgr.getWindow("MusicList"));

	ItemEntry* item=list1->getNextSelectedItem();

	UINT strLen=lstrlen(szCurDir);
	wchar_t	buff[128];

	while(item)
	{
		list1->removeItem(item);
#ifdef UNICODE
		//const char* a=item->getText().c_str();
		MultiByteToWideChar( CP_UTF8, 0,item->getText().c_str(), -1, buff, 128);

		lstrcat(szCurDir,buff);
		Sound::removeMusic(buff);
#else
		Sound::removeMusic(item->getName().c_str());
		lstrcat(szCurDir,item->getName().c_str());
#endif
		DeleteFile(szCurDir);
		szCurDir[strLen]='\0';
		item=list1->getNextSelectedItem();
	}
	return true;
}
bool SettingGUI::AddMusic(const CEGUI::EventArgs& args)
{
	ImmediateData* data=ImmediateData::immediateData;
	//DInput* input=DInput::InitializeDInput();
	////input->m_mouseDevice->Release();
	//input->m_mouseDevice->Unacquire();
	//input->NoNexclusive();
	//WindowManager& wmgr = WindowManager::getSingleton();
	
	ShowCursor(true);
	TCHAR* szPathName=new TCHAR[256*256]; 
	TCHAR szCurDir[MAX_PATH]; 
	GetCurrentDirectory(sizeof(szCurDir),szCurDir); 

	ZeroMemory(szPathName,sizeof(TCHAR)*256*256);

	OPENFILENAME ofn = { OPENFILENAME_SIZE_VERSION_400 };//or  {sizeof (OPENFILENAME)} 
	// lStructSize 
	// 指定这个结构的大小，以字节为单位。 
	// Windows 95/98和Windows NT 4.0：特意为Windows 95/98或Windows NT 4.0，及带有WINVER和_WIN32_WINNT >= 0x0500编译时， 
	//  为这个成员使用OPENFILENAME_SIZE_VERSION_400。 
	// Windows 2000及更高版本：这个参数使用sizeof (OPENFILENAME) 。 
	ofn.hwndOwner =GetForegroundWindow();// 打开OR保存文件对话框的父窗口 
	//ofn.hwndOwner =NULL;
	ofn.lpstrFilter = TEXT("Music\0*.MP3;*.wav\0");  
	//过滤器 如果为 NULL 不使用过滤器 
	//具体用法看上面  注意 /0 
	//lstrcpy(szPathName, TEXT("")); 

	ofn.lpstrFile = szPathName; 
	ofn.hInstance = (HMODULE)GetCurrentProcess();
	ofn.nMaxFile = 256*256;//存放用户选择文件的 路径及文件名 缓冲区 
	ofn.lpstrTitle = TEXT("选择文件");//选择文件对话框标题 

	ofn.lpstrInitialDir=szCurDir;//设置对话框显示的初始目录 
	ofn.Flags = OFN_EXPLORER |OFN_ALLOWMULTISELECT| OFN_FILEMUSTEXIST;//如果需要选择多个文件 则必须带有  OFN_ALLOWMULTISELECT标志 


	BOOL bOk = GetOpenFileName(&ofn);//调用对话框打开文件 

	SetCurrentDirectory(szCurDir);
	lstrcat(szCurDir,TEXT("\\Music\\"));
	TCHAR* p=szPathName;
	if(*(p+ofn.nFileOffset-1)!=TEXT('\0'))
	{
		lstrcat(szCurDir,p+ofn.nFileOffset);
		if(CopyFile(p,szCurDir,false))
		{
			TCHAR* music=new TCHAR[lstrlen(p+ofn.nFileOffset)];
			lstrcpy(music,p+ofn.nFileOffset);
			musicToList(music);

			data->realdata.music[data->realdata.numberOfMusic]=music;
			data->realdata.numberOfMusic++;
		}
		delete[] szPathName;

	/*	Sound* sound=Sound::InitializeSound();
		sound->loadMusicList();*/
	}
	else
	{
		CreateThread(0,0,CopyThread,szPathName,0,0);
	}


	ShowCursor(false);

	return true;
}
DWORD WINAPI SettingGUI::CopyThread(LPVOID lpParamter)
{
	ImmediateData* data=ImmediateData::immediateData;

	TCHAR* str=(TCHAR*)lpParamter;

	TCHAR szCurDir[MAX_PATH]; 

	GetCurrentDirectory(sizeof(szCurDir),szCurDir); 
	lstrcat(szCurDir,TEXT("\\Music\\"));

	TCHAR filePath[MAX_PATH]; 

	lstrcpy(filePath,str);
	lstrcat(filePath,TEXT("\\"));

	int srDirLen=lstrlen(filePath);
	int curDirLen=lstrlen(szCurDir);

	str+=srDirLen;

	//char name[11]="MusicItem0";
	WindowManager& wmgr = WindowManager::getSingleton();
	ItemListbox* list1=static_cast<ItemListbox*>(wmgr.getWindow("MusicList"));

	char buff[128] = "";

	do
	{
		lstrcat(filePath,str);
		//MessageBox(0,ttt,_T(""),0);
		lstrcat(szCurDir,str);

		if(CopyFile(filePath,szCurDir,false))
		{
			TCHAR* music=new TCHAR[lstrlen(str)];
			lstrcpy(music,str);


			ToUTF8(music,buff);
			ItemEntry* item=static_cast<ItemEntry*>(wmgr.createWindow( "OgreTray/ListboxItem",buff));

			list1->addItem(item);
			item->setText((utf8*)buff);

			data->realdata.music[data->realdata.numberOfMusic]=music;
			data->realdata.numberOfMusic++;

		}
		szCurDir[curDirLen]=TEXT('\0');
		filePath[srDirLen]=TEXT('\0');

		str+=lstrlen(str)+1;
	}while(*str);

	//Sound* sound=Sound::InitializeSound();
	//sound->loadMusicList();

	delete[] lpParamter;
	return 0;
}

bool SettingGUI::exit(const CEGUI::EventArgs& args)
{
	if(gCall)
		gCall->Invoke();
	return true;
}
