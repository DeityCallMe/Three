#include "ImmediateData.h"
#include "Header.h"
ImmediateData* ImmediateData::immediateData=0;
ImmediateData::ImmediateData()
{
	realdata=RealData();
	m_hFile = CreateFile(_T("info"),     //创建文件的名称。
		GENERIC_WRITE|GENERIC_READ,          // 写和读文件。
		0,                      // 不共享读写。
		NULL,                   // 缺省安全属性。
		OPEN_ALWAYS,         
		FILE_ATTRIBUTE_NORMAL, // 一般的文件。       
		NULL);                 // 模板文件为空。
	DWORD fileSize = 0;
	DWORD readSize=0;
	fileSize=GetFileSize(m_hFile,0);
	if(fileSize!=(sizeof(recordData)+sizeof(settingData)))
	{
		CloseHandle(m_hFile);
		m_hFile = CreateFile(_T("info"),     //创建文件的名称。
		GENERIC_WRITE|GENERIC_READ,          // 写和读文件。
		0,                      // 不共享读写。
		NULL,                   // 缺省安全属性。
		CREATE_ALWAYS,         
		FILE_ATTRIBUTE_NORMAL, // 一般的文件。       
		NULL);

		recordData=RecordData();
		settingData=SettingData();

		SaveRecord();
		SaveSetting();
	}
	else
	{
		ReadFile(m_hFile,&recordData,sizeof(recordData),&readSize,NULL);
		SetFilePointer(m_hFile,sizeof(recordData),0,FILE_BEGIN);
		ReadFile(m_hFile,&settingData,sizeof(settingData),&readSize,NULL);
	}

}
ImmediateData::~ImmediateData()
{
	CloseHandle(m_hFile);
}
void ImmediateData::SaveRecord()
{
	DWORD writenSize=0;
	SetFilePointer(m_hFile,0,0,FILE_BEGIN);
	WriteFile(m_hFile,&recordData,sizeof(recordData),&writenSize,NULL);
	FlushFileBuffers(m_hFile);
}
void ImmediateData::SaveSetting()
{
	DWORD writenSize=0;
	SetFilePointer(m_hFile,sizeof(recordData),0,FILE_BEGIN);
	WriteFile(m_hFile,&settingData,sizeof(settingData),&writenSize,NULL);
	FlushFileBuffers(m_hFile);
}
