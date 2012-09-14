#include "RenderDelegate.h"

#include "Header.h"
RenderDelegate::RenderDelegate()
{
	firstNope=0;
}
RenderDelegate::~RenderDelegate()
{
	clearUp();
}
void RenderDelegate::clearUp()
{
	MapList* keyTemp; 
	while(firstNope!=0)
	{
		keyTemp=firstNope->_next;
		delete firstNope;
	}
}
void RenderDelegate::AddMap(NativePtr tt,NativePtr pt,IDelegateHandler* ih)
{
	MapList* keyTemp=firstNope; 
	if(firstNope==0)
	{
		firstNope=new MapList(tt,pt,ih);
	}
	else
	{
		while(keyTemp->_next!=0)
		{
			keyTemp=keyTemp->_next;
		}
		keyTemp->_next=new MapList(tt,pt,ih);
	}

}
void RenderDelegate::RemoveMap(NativePtr tt,NativePtr pt)
{

	if(firstNope==0)
		goto ends;


	MapList* keyPre=firstNope; 
	MapList* keyCurrent=firstNope->_next;

	if(firstNope->typeT==tt&&firstNope->funcT==pt)
	{
		firstNope=firstNope->_next;
		delete keyPre;
		goto ends;
	}

	while(keyCurrent!=NULL)
	{
		if(keyCurrent->typeT==tt&&keyCurrent->funcT==pt)
		{
			keyPre->_next=keyCurrent->_next;
			delete keyCurrent;
		}
		else
		{
			keyPre=keyCurrent;
		}
		keyCurrent=keyPre->_next;
	}
ends:
	return;
}

//

void RenderDelegate::AddFunction(VFUNC(pFunc))
{
		DelegateHandler<void>* fn=new DelegateHandler<void>(pFunc);
		AddMap(0,(NativePtr)pFunc,fn);
}
//

void RenderDelegate::RemoveFunction(VFUNC(pFunc))
{
	RemoveMap(0,(NativePtr)pFunc);
}
void RenderDelegate::operator += (VFUNC(ftn))
{

       this->AddFunction(ftn);

}
void RenderDelegate::operator -= (VFUNC(ftn))
{
       this->RemoveFunction(ftn);

}
int RenderDelegate::Invoke(int pch,Graphic* idd)
{
	MapList* keyTemp=firstNope; 
	try
	{
		while(keyTemp!=0)
		{
			keyTemp->phandler->Invoke(pch,idd);
			keyTemp=keyTemp->_next;
		}

	}
	catch (char)
	{
		  return 0;
	}
    return 1;
}
int RenderDelegate::operator ()(int pch,Graphic* idd)

{

       return Invoke(pch,idd);
}
