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
	/*添加函数引用(指针)*/
	template<typename T>
	void AddFunction(T* pT,TFUNC(T,pFunc))
	{
		DelegateHandler<T>* fn=new DelegateHandler<T>(pT,pFunc);
		NativePtr kSecond;
		memcpy(&kSecond,&pFunc,sizeof(NativePtr));
		AddMap((NativePtr)pT,kSecond,fn);
	} 

	/*添加函数引用(指针)*/
	void AddFunction(VFUNC(pFunc));    



	/*删除函数引用(指针)*/
	template<typename T>
	void RemoveFunction(T* pT,TFUNC(T,pFunc))
	{
		NativePtr kSecond;
		memcpy(&kSecond,&pFunc,sizeof(NativePtr));
		RemoveMap((NativePtr)pT,kSecond);
	}


	void RemoveFunction(VFUNC(pFunc));



	/*调用例程:最重要的部分,实现对列表中的函数逐个调用*/

	int Invoke(int,Graphic*);



	/*运算符重载AddFunction方法*/

	void operator += (VFUNC(ftn));

	/*运算符重载RemoveFunction方法*/

	void operator -= (VFUNC(ftn));

	/*运算符重载Invoke方法*/

	int operator ()(int,Graphic*);


};
#endif