#include "ImmediateData.h"
#include "Header.h"
ImmediateData* ImmediateData::immediateData=0;
ImmediateData::ImmediateData()
{
	realdata=RealData();
	m_hFile = CreateFile(_T("info"),     //�����ļ������ơ�
		GENERIC_WRITE|GENERIC_READ,          // д�Ͷ��ļ���
		0,                      // �������д��
		NULL,                   // ȱʡ��ȫ���ԡ�
		OPEN_ALWAYS,         
		FILE_ATTRIBUTE_NORMAL, // һ����ļ���       
		NULL);                 // ģ���ļ�Ϊ�ա�
	DWORD fileSize = 0;
	DWORD readSize=0;
	fileSize=GetFileSize(m_hFile,0);
	if(fileSize!=(sizeof(recordData)+sizeof(settingData)))
	{
		CloseHandle(m_hFile);
		m_hFile = CreateFile(_T("info"),     //�����ļ������ơ�
		GENERIC_WRITE|GENERIC_READ,          // д�Ͷ��ļ���
		0,                      // �������д��
		NULL,                   // ȱʡ��ȫ���ԡ�
		CREATE_ALWAYS,         
		FILE_ATTRIBUTE_NORMAL, // һ����ļ���       
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
