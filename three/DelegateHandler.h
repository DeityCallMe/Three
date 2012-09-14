#ifndef _D_H
#define _D_H
#include"Graphic.h"



class Graphic;
///*定义函数原型,返回值须为空,参数根据需要可改变*/
//typedef void (* Handler)(int,Graphic*);
#define TFUNC(t,a) void (t::*a)(int,Graphic*)
#define VFUNC(a) void (*a)(int,Graphic*)

//typedef  void (*VFunc)(int,Graphic*);
//typedef  void (*TFunc)(int,Graphic*);
class IDelegateHandler {
 
public:
    virtual ~IDelegateHandler() { }
    virtual void Invoke(int,Graphic*) = 0;
};
template<typename T>
class DelegateHandler :
	public IDelegateHandler 
{
public:
    DelegateHandler(T* pT,TFUNC(T,pFunc))
        : m_pT(pT), m_pFunc(pFunc) { }
 
    void Invoke(int i,Graphic* g) 
	{
        (m_pT->*m_pFunc)(i,g);
    }
 
private:
    T* m_pT;
	//void (T::*m_pFunc)(int,Graphic*);
    TFUNC(T,m_pFunc);
};
template<>
class DelegateHandler<void> : 
	public IDelegateHandler 
{
public:
	DelegateHandler(VFUNC(pFunc))
		: m_pFunc(pFunc) { }

	void Invoke(int i,Graphic* g) 
	{
		(*m_pFunc)(i,g);
	}

private:
	//void (*m_pFunc)(int,Graphic*);
	VFUNC(m_pFunc);
};
#endif