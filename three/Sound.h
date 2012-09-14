#ifndef _SOUND_H
#define _SOUND_H
#include <fmod.hpp>
#include <assert.h>
#include <fmod_errors.h>
#include <windows.h>
#include <process.h>  
#include <iostream>  
#include "ImmediateData.h"

#pragma comment (lib,"fmodex_vc.lib")
#define COUNT 25

class Sound
{
public:
	static Sound* InitializeSound();
	static void ReleaseSound();

	void loadMusicList();
	void playSound(int);
private:
	Sound();
	~Sound();

	//void ERRCHECK(FMOD_RESULT);
	void loadSound();


	bool initialize();
	void initMusic();
	void ERRCHECK(FMOD_RESULT);

	void PlayMusic();

	static DWORD WINAPI PlayThread(LPVOID);
	

	FMOD::System*    system;
    FMOD::Sound*     sound[COUNT];
	FMOD::Sound*	 MusicSound;
	FMOD::Channel*   MusicChannel;
    FMOD::Channel*   channel;
    FMOD_RESULT      m_FmodResult;
    //int               key;



	static Sound* soleSound;


	HANDLE m_thread;
	static bool m_isRun;
    unsigned int      version;
	static UINT m_currentMusic;
};
#endif