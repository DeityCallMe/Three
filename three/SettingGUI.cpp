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



	ToUTF8(_T("����������"),buff);

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
	ToUTF8(_T("ȷ��"),buff);


	enBt->setText((utf8*)buff);

	enBt->subscribeEvent(ButtonBase::EventMouseClick,Event::Subscriber(&SettingGUI::setting,this));


	ButtonBase* exBt = static_cast<ButtonBase*>(
		wmgr.createWindow( "OgreTray/Button", "exit" ));
	fWnd->addChildWindow( exBt );
	exBt->setPosition( UVector2( UDim( 0.6f, 0 ), UDim( 0.7f, 0 ) ) );

	exBt->setSize( UVector2( UDim( 0.3f, 0 ), UDim( 0.2f, 0 ) ) );
	ToUTF8(_T("�˳�"),buff);


	exBt->setText((utf8*)buff);

	exBt->subscribeEvent(ButtonBase::EventMouseClick,Event::Subscriber(&SettingGUI::exit,this));

	DefaultWindow* erText = static_cast<DefaultWindow*>(
		wmgr.createWindow( "OgreTray/StaticText", "passwordError" ));
	fWnd->addChildWindow( erText );
	erText->setPosition( UVector2( UDim( 0.32f, 0 ), UDim( 0.07f, 0 ) ) );

	erText->setSize( UVector2( UDim( 0.36f, 0 ), UDim( 0.22f, 0 ) ) );
	ToUTF8(_T("�������"),buff);
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
	// ָ������ṹ�Ĵ�С�����ֽ�Ϊ��λ�� 
	// Windows 95/98��Windows NT 4.0������ΪWindows 95/98��Windows NT 4.0��������WINVER��_WIN32_WINNT >= 0x0500����ʱ�� 
	//  Ϊ�����Աʹ��OPENFILENAME_SIZE_VERSION_400�� 
	// Windows 2000�����߰汾���������ʹ��sizeof (OPENFILENAME) �� 
	ofn.hwndOwner =GetForegroundWindow();// ��OR�����ļ��Ի���ĸ����� 
	//ofn.hwndOwner =NULL;
	ofn.lpstrFilter = TEXT("Music\0*.MP3;*.wav\0");  
	//������ ���Ϊ NULL ��ʹ�ù����� 
	//�����÷�������  ע�� /0 
	//lstrcpy(szPathName, TEXT("")); 

	ofn.lpstrFile = szPathName; 
	ofn.hInstance = (HMODULE)GetCurrentProcess();
	ofn.nMaxFile = 256*256;//����û�ѡ���ļ��� ·�����ļ��� ������ 
	ofn.lpstrTitle = TEXT("ѡ���ļ�");//ѡ���ļ��Ի������ 

	ofn.lpstrInitialDir=szCurDir;//���öԻ�����ʾ�ĳ�ʼĿ¼ 
	ofn.Flags = OFN_EXPLORER |OFN_ALLOWMULTISELECT| OFN_FILEMUSTEXIST;//�����Ҫѡ�����ļ� ��������  OFN_ALLOWMULTISELECT��־ 


	BOOL bOk = GetOpenFileName(&ofn);//���öԻ�����ļ� 

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
