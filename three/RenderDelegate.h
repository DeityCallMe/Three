#ifndef _R_H
#define _R_H
#include "DelegateHandler.h"
#include <Windows.h>


//#include "Header.h"
class Graphic;
struct ImageInfo;


typedef unsigned int NativePtr;
struct MapList
{
	MapList(NativePtr tt,NativePtr ft,IDelegateHandler* ih)
		:typeT(tt),funcT(ft),phandler(ih),_next(0)
	{

	}
	~MapList()
	{
		delete phandler;
	}
	NativePtr	typeT;
	NativePtr	funcT;

	IDelegateHandler* phandler;

	MapList* _next;
};

class RenderDelegate
{

private:
	MapList* firstNope;


	void AddMap(NativePtr,NativePtr,IDelegateHandler*);
	void RemoveMap(NativePtr,NativePtr);

public:
	RenderDelegate();
	~RenderDelegate();
	void clearUp();
	/*��Ӻ�������(ָ��)*/
	template<typename T>
	void AddFunction(T* pT,TFUNC(T,pFunc))
	{
		DelegateHandler<T>* fn=new DelegateHandler<T>(pT,pFunc);
		NativePtr kSecond;
		memcpy(&kSecond,&pFunc,sizeof(NativePtr));
		AddMap((NativePtr)pT,kSecond,fn);
	} 

	/*��Ӻ�������(ָ��)*/
	void AddFunction(VFUNC(pFunc));    



	/*ɾ����������(ָ��)*/
	template<typename T>
	void RemoveFunction(T* pT,TFUNC(T,pFunc))
	{
		NativePtr kSecond;
		memcpy(&kSecond,&pFunc,sizeof(NativePtr));
		RemoveMap((NativePtr)pT,kSecond);
	}


	void RemoveFunction(VFUNC(pFunc));



	/*��������:����Ҫ�Ĳ���,ʵ�ֶ��б��еĺ����������*/

	int Invoke(int,Graphic*);



	/*���������AddFunction����*/

	void operator += (VFUNC(ftn));

	/*���������RemoveFunction����*/

	void operator -= (VFUNC(ftn));

	/*���������Invoke����*/

	int operator ()(int,Graphic*);


};
#endif