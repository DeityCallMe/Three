#include "Sound.h"
#include "Header.h"
Sound* Sound::soleSound=0;
bool Sound::m_isRun=false;
UINT Sound::m_currentMusic=0;
Sound* Sound::InitializeSound()
{
	if(soleSound!=0)
		goto ends;

	soleSound=new Sound();
	if(!soleSound->initialize())
	{
		delete soleSound;
		soleSound=0;
	}
ends:
	return soleSound;
}


Sound::Sound()
	:system(0),MusicChannel(0),MusicSound(0),channel(0)
{
	
}
Sound::~Sound()
{
	CloseHandle(m_thread);
}

DWORD Sound::PlayThread(LPVOID lpParamter)
{
	Sound* sound=(Sound*)lpParamter;

	ImmediateData* data=ImmediateData::immediateData;

	FMOD_RESULT musicResult;
	while(m_isRun)
	{
		if(data->settingData.backgroundMusic&& sound->MusicChannel)
		{
			bool         playing = 0;
			bool         paused = 0;
			musicResult = sound->MusicChannel->isPlaying(&playing);
			if(!playing)
			{
				if(data->settingData.musicMode==0)
				{
					sound->m_currentMusic++;
					if(sound->m_currentMusic>=data->realdata.numberOfMusic)
						sound->m_currentMusic=0;
					
				}
				else if(data->settingData.musicMode==1)
				{
					sound->m_currentMusic=rand()%data->realdata.numberOfMusic;
				}
				sound->MusicSound->release();
				sound->PlayMusic();
			}
		}
		Sleep(30);
	}
	return 0;
}
void Sound::PlayMusic()
{
	ImmediateData* data=ImmediateData::immediateData;
	if(m_currentMusic<data->realdata.numberOfMusic)
	{

		//m_currentMusic=1;
		TCHAR musicDir[MAX_PATH];
		GetCurrentDirectory(MAX_PATH,musicDir);   

		lstrcat(musicDir,_T("\\Music\\"));

		lstrcat(musicDir,data->realdata.music[m_currentMusic]);

		char* music;
#ifdef UNICODE

		UINT nNeedLenOfMultiStr=WideCharToMultiByte(CP_ACP,0,musicDir,-1,0,0,NULL,NULL);
		music=new char[nNeedLenOfMultiStr];
		WideCharToMultiByte(CP_ACP,0,musicDir,-1,music,nNeedLenOfMultiStr,NULL,NULL);
#else
		music=data->realdata.music[m_currentMusic];
#endif

		m_FmodResult = system->createSound(music, FMOD_DEFAULT, 0, &MusicSound);
		ERRCHECK(m_FmodResult);

		m_FmodResult = system->playSound(FMOD_CHANNEL_FREE, MusicSound, false, &MusicChannel);
		ERRCHECK(m_FmodResult);

#ifdef UNICODE
		delete[] music;
#endif
	}
}
bool Sound::initialize()
{
	bool result = false;

	ImmediateData* data=ImmediateData::immediateData;

	FMOD::System_Create(&system);
	system->getVersion(&version);
    if (version < FMOD_VERSION)
    {
		//
		goto ends;
    }

    m_FmodResult = system->init(32, FMOD_INIT_NORMAL, 0);
	ERRCHECK(m_FmodResult);
	//loadSound();
	loadMusicList();
	////
	initMusic();


	m_isRun=true;
	CreateThread(0,0,PlayThread,this,0,0);

	result=true;
ends:
	return result;
}

void Sound::initMusic()
{
	ImmediateData* data=ImmediateData::immediateData;

	if(data->settingData.backgroundMusic)
	{
		if(data->settingData.musicMode==0)
		{
			m_currentMusic=0;
		}
		else
		{
			m_currentMusic=rand()%data->realdata.numberOfMusic;
		}
		PlayMusic();
	}
}

void Sound::ERRCHECK(FMOD_RESULT result)
{
    if (result != FMOD_OK)
    {
        //FMOD error
		MessageBox(NULL,_T("FMOD error!"),_T("´íÎó"),MB_OK);
    }
}
void Sound::loadSound()
{
	char* path=new char[20];
	char t;
	int count=0;
	for(int i=0;i<10||count<COUNT;i++)
	{
		for(int j=0;j<10||count<COUNT;j++)
		{
			strcpy(path,"\\sound\\");
			if(i!=0)
			{
				t=i+'0';
				strcat(path,&t);
			}
			t=j+'0';
			strcat(path,&t);
			strcat(path,".wav");

			system->createSound(path, FMOD_HARDWARE, 0, &sound[count]);
			count++;
		}
	}
	delete[] path;
}
void Sound::playSound(int n)
{
	assert(n >= 0 && n < COUNT);
	system->playSound(FMOD_CHANNEL_FREE, sound[n], false, &channel);
	//system->update();
}
void Sound::loadMusicList()
{
	ImmediateData* data=ImmediateData::immediateData;

	WIN32_FIND_DATA ffd;

	TCHAR szDir[MAX_PATH];

	size_t length_of_arg;
	HANDLE hFind = INVALID_HANDLE_VALUE;
	DWORD dwError=0;

	GetCurrentDirectory(MAX_PATH,szDir);   

	lstrcat(szDir,_T("\\Music"));

	if(CreateDirectory(szDir,NULL))
	{
		goto ends;
	}

	lstrcat(szDir,_T("\\*"));

	hFind = FindFirstFile(szDir, &ffd);
	if (INVALID_HANDLE_VALUE == hFind) 
	{
		MessageBox(NULL,_T("¶ÁÈ¡ÒôÀÖ³ö´í!"),_T("´íÎó"),MB_OK);
		goto ends;
	} 

	do
	{
		if (!(ffd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)&&ffd.cFileName[0]!=_T('.'))
		{

			TCHAR* name=new TCHAR[lstrlen(ffd.cFileName)+1];
			lstrcpy(name,ffd.cFileName);
			data->realdata.music[data->realdata.numberOfMusic]=name;
			data->realdata.numberOfMusic++;
		}
	}
	while (FindNextFile(hFind, &ffd) != 0);

ends:
	return ;
}