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
#define MAXPLAY 10
class Sound
{
public:
	static Sound* InitializeSound();
	static void ReleaseSound();

	static int removeMusic(UINT);
	static int removeMusic(TCHAR*);
	static void setMusicVolume();
	static void setMusicVolume(float);
	static void playMusic(TCHAR*);
	static void playMusic(UINT);

	void loadMusicList();
	void playSound(int);
private:
	Sound();
	~Sound();

	//void ERRCHECK(FMOD_RESULT);
	void loadSound();


	bool initialize();
	void initMusic();

	
	void PlayMusic();

	static void ERRCHECK(FMOD_RESULT);
	static DWORD WINAPI PlayThread(LPVOID);
	static int getMusicIndex(TCHAR*);

	FMOD::System*    system;
    FMOD::Sound*     sound[COUNT];
	FMOD::Sound*	 MusicSound;
	FMOD::Channel*   MusicChannel;
    FMOD::Channel*   channel;
    FMOD_RESULT      m_FmodResult;
    //int               key;
	UINT m_willPlay[MAXPLAY];
	UINT m_cuPlay;
	UINT m_cuPos;

	static Sound* soleSound;

	CRITICAL_SECTION  m_csThreadCode;  
	HANDLE m_thread;
	bool m_isRun;
    unsigned int      version;
	static UINT m_currentMusic;
};
#endif