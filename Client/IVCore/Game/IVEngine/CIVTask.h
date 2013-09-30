//================= IV:Network - https://github.com/GTA-Network/IV-Network =================
//
// File: CIVTask.h
// Project: Client.Core
// Author: FRi<FRi.developing@gmail.com>
// License: See LICENSE in root directory
//
//==========================================================================================

#ifndef CIVTask_h
#define CIVTask_h

#include <Common.h>
#include <Math/CMaths.h>
#include <IV/IVCommon.h>
#include <Game/eGame.h>

class CIVPed;
class IVPed;

class CTaskManager;

class IVEvent
{
public:
	DWORD	m_field4;
	BYTE	m_field8;

	virtual ~IVEvent();
	virtual void Function1();
	virtual void Function2();
	virtual void Function3();
	virtual void Function4();
	virtual void Function5();
	virtual void Function6();
	virtual void Function7();
	virtual void Function8();
	virtual void Function9();
	virtual void Function10();
	virtual void Function11();
	virtual void Function12();
	virtual void Function13();
	virtual void Function14();
	virtual void Function15();
	virtual void Function16();
	virtual void Function17();
	virtual void Function18();
	virtual void Function19();
	virtual void Function20();
};


class CIVEvent
{
private:
	IVEvent * m_pEvent;

public:
	CIVEvent();
	CIVEvent(IVEvent * pEvent);
	~CIVEvent();

	void      SetEvent(IVEvent * pEvent) { m_pEvent = pEvent; };
	IVEvent * GetEvent() { return m_pEvent; }
};


static const char * GetTaskName(int iTaskType);

class IVTask
{
public:
	IVTask *        m_pParent;
	//PAD(IVTask, pad0, 0x104); // incorrect (probably the biggest task size possible?)
	// 0xE = pPed? // incorrect

	virtual                 ~IVTask();
	virtual IVTask* Clone();
	virtual bool    IsSimple();
	virtual int     GetType();
	virtual void    Function4();
	virtual bool    MakeAbortable(IVPed * pPed, int iAbortPriority, IVEvent * pEvent);
	virtual float   Function6(int a1);
	virtual int             Function7(int a1);
	virtual void    Function8(int a1);
	virtual int             Function9();
	virtual bool    Function10(); // *(this + 24) > 0.0;
	virtual int     Function11(); // get this+20
	virtual int     Function12();
	virtual bool    Function13(int a1, int a2);
	virtual int     Function14();
	virtual int     Function15();
	virtual int     Function16(int a2);
};
class IVTaskSimple : public IVTask
{
public:
	virtual ~IVTaskSimple();
	virtual void ProcessPed(IVPed * pPed);
	virtual void Function18();
	virtual void Function19();
};

class IVTaskComplex : public IVTask
{
public:
	IVTask * m_pSubTask;
	virtual                         ~IVTaskComplex();
	virtual void            SetSubTask(IVTask* pTask);
	virtual IVTask*         CreateNextSubTask(IVPed* pPed);
	virtual IVTask*         CreateFirstSubTask(IVPed* pPed);
	virtual IVTask*         ControlSubTask(IVPed* pPed);
};

static const char * GetTaskName(int iTaskType);

class CIVTask
{
private:
	IVTask * m_pTask;

public:
	CIVTask();
	CIVTask(IVTask * pTask);
	~CIVTask();

	void         SetTask(IVTask * pTask);
	IVTask *     GetTask();

	void         Create();
	void         Destroy();
	CIVTask *    GetParent();
	CIVTask *    Clone();
	bool         IsSimple();
	int          GetType();
	const char * GetName();
	bool         MakeAbortable(CIVPed * pPed, int iAbortPriority, CIVEvent * pEvent = NULL);
	void         SetAsPedTask(CIVPed * pPed, int iTaskPriority, bool bForceNewTask = false);
	void         SetAsPedTaskSecondary(CIVPed * pPed, int iTaskPriority);
};

class CIVTaskSimple : public CIVTask
{
public:
	CIVTaskSimple() : CIVTask() {}
	CIVTaskSimple(IVTaskSimple * pTask) : CIVTask(pTask) {}

	bool ProcessPed(CIVPed * pPed);
};

class CIVTaskComplex : public CIVTask
{
public:
	CIVTaskComplex() : CIVTask() {}
	CIVTaskComplex(IVTaskComplex * pTask) : CIVTask(pTask) {}

	CIVTask * GetSubTask();
	void      SetSubTask(CIVTask * pSubTask);
	CIVTask * CreateNextSubTask(CIVPed * pPed);
	CIVTask * CreateFirstSubTask(CIVPed * pPed);
	CIVTask * ControlSubTask(CIVPed * pPed);
};

#endif // CIVTask_h