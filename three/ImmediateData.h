#ifndef _IMMEDIATE_H
#define _IMMEDIATE_H
#include <Windows.h>
#include <tchar.h>



#define MAXMUSIC 300

#define LISTREPEAT  0
#define RANDOM      1
#define TRACKREPEAT 2

struct RealData
{
	BYTE currentRecord[100];

	int bureauTimes;

	int prizeGold;

	int countdown;
	int spade;
	int heart;
	int club;
	int diamond;
	int joker;

	int view;

	int betFraction[8];

	TCHAR* music[MAXMUSIC];
	UINT numberOfMusic;
};
struct RecordData
{
	RecordData()
	{
		EntireRefresh();
		wheelTimes=0;
	}
	~RecordData()
	{

	}
	void EntireRefresh()
	{
		for(int i=0;i<100;i++)
			Refresh(i);
	}
	void Refresh(UINT s)
	{
		for(int i=0;i<100;i++)
		{
			record[s][i]=rand()%4;
		}
		for(int i=0;i<4;i++)
		{
			record[s][rand()%100]=4;
		}
	}
	BYTE record[100][100];
	int wheelTimes;
	int userFraction[8];
};
struct SettingData
{
	SettingData()
	{
		 spadeAmends = 38;
		 heartAmends = 38;
		 clubAmends = 40;
		 diamondAmends = 40;
		 jokerAmends = 18;
		 smallGold = 100;
		 lagerGold = 10000;
		 jokerAstrict = 300;
		 designAstrict = 1000;
		 leastFraction = 10;
		 detainTime = 15;
		 intervalTime = 30;
		 threeTest = 0;
		 backgroundMusic = 1;
		 colorGlodTimes = 1;
		 spadeAstrict = 5000;
		 heartAstrict = 5000;
		 clubAstrict = 5000;
		 diamondAstrict = 5000;
		 beginWash = 20;
		 lockFraction = 50000;
		 difficulty = 0;
		 print = 0;
		 volume=0.0f;

		 memcpy(phone,_T("13416407888"),12*sizeof(TCHAR));
		 memcpy(password,_T("123456789"),10*sizeof(TCHAR));
		 ZeroMemory(lastPlay,30);
		 //ZeroMemory(password,10);
		// password[10]="";
		 beginWay = 0;
		 isK2 = 0;

		 musicMode=LISTREPEAT;
	}
	int spadeAmends;
	int heartAmends;
	int clubAmends;
	int diamondAmends;
	int jokerAmends;
	int smallGold;
	int lagerGold;
	int jokerAstrict;
	int designAstrict;
	int leastFraction;
	int detainTime;
	int intervalTime;
	int threeTest;

	int colorGlodTimes;
	int spadeAstrict;
	int heartAstrict;
	int clubAstrict;
	int diamondAstrict;
	int beginWash;
	int lockFraction;
	int difficulty;
	int print;
	TCHAR phone[12];
	TCHAR password[10];
	int beginWay;
	int isK2;

	int backgroundMusic;
	int musicMode;
	float volume;

	TCHAR lastPlay[50];
};
class ImmediateData
{
public:
	ImmediateData();
	~ImmediateData();
	RealData realdata;
	RecordData recordData;
	SettingData settingData;
	void SaveRecord();
	void SaveSetting();
	static ImmediateData* immediateData;
private:
	HANDLE m_hFile;
};
#endif