/*
* Copyright (C) GTA-Network Team
*
* Redistribution and use in source and binary forms, with or without
* modification, are permitted provided that the following conditions are
* met:
*
*     * Redistributions of source code must retain the above copyright
* notice, this list of conditions and the following disclaimer.
*     * Redistributions in binary form must reproduce the above
* copyright notice, this list of conditions and the following disclaimer
* in the documentation and/or other materials provided with the
* distribution.
*     * Neither the name of GTA-Network nor the names of its
* contributors may be used to endorse or promote products derived from
* this software without specific prior written permission.
*
* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
* "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
* LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
* A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
* OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
* SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES INCLUDING, BUT NOT
* LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
* DATA, OR PROFITS; OR BUSINESS INTERRUPTION HOWEVER CAUSED AND ON ANY
* THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
* INCLUDING NEGLIGENCE OR OTHERWISE ARISING IN ANY WAY OUT OF THE USE
* OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#ifndef CTask_h
#define CTask_h

#include <Common.h>
#include "../GameCommon.h"

_GAME_BEGIN

class CPed;
class IPed;

class CTaskManager;

class IEvent
{
public:
	DWORD	m_field4;
	BYTE	m_field8;

	virtual ~IEvent();
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


class CEvent
{
private:
	IEvent * m_pEvent;

public:
	CEvent();
	CEvent(IEvent * pEvent);
	~CEvent();

	void      SetEvent(IEvent * pEvent) { m_pEvent = pEvent; };
	IEvent * GetEvent() { return m_pEvent; }
};


const char * GetTaskName(int iTaskType);

class ITask
{
public:
	ITask *        m_pParent;
	//PAD(IVTask, pad0, 0x104); // incorrect (probably the biggest task size possible?)
	// 0xE = pPed? // incorrect

	virtual			~ITask();
	virtual ITask* Clone();
	virtual bool	IsSimple();
	virtual int		GetType();
	virtual void	Function4();
	virtual bool	MakeAbortable(IPed * pPed, int iAbortPriority, IEvent * pEvent);
	virtual float	Function6(int a1);
	virtual int		Function7(int a1);
	virtual void	Function8(int a1);
	virtual int		Function9();
	virtual bool	Function10(); // *(this + 24) > 0.0;
	virtual int		Function11(); // get this+20
	virtual int		Function12();
	virtual bool	Function13(int a1, int a2);
	virtual int		Function14();
	virtual int		Function15();
	virtual int		Function16(int a2);
};
class ITaskSimple : public ITask
{
public:
	virtual ~ITaskSimple();
	virtual void ProcessPed(IPed * pPed);
	virtual void Function18();
	virtual void Function19();
};

class ITaskComplex : public ITask
{
public:
	ITask * m_pSubTask;
	virtual					~ITaskComplex();
	virtual void			SetSubTask(ITask* pTask);
	virtual ITask*			CreateNextSubTask(IPed* pPed);
	virtual ITask*			CreateFirstSubTask(IPed* pPed);
	virtual ITask*			ControlSubTask(IPed* pPed);
};

class CTask
{
private:
	ITask * m_pTask;

public:
	CTask();
	CTask(ITask * pTask);
	~CTask();

	void			SetTask(ITask * pTask);
	ITask *		GetTask();

	void			Create();
	void			Destroy();
	CTask *		GetParent();
	CTask *		Clone();
	bool			IsSimple();
	int				GetType();
	const char *	GetName();
	bool			MakeAbortable(CPed * pPed, int iAbortPriority, CEvent * pEvent = NULL);
	void			SetAsPedTask(CPed * pPed, int iTaskPriority, bool bForceNewTask = false);
	void			SetAsPedTaskSecondary(CPed * pPed, int iTaskPriority);
};

class CTaskSimple : public CTask
{
public:
	CTaskSimple() : CTask() {}
	CTaskSimple(ITaskSimple * pTask) : CTask(pTask) {}

	bool ProcessPed(CPed * pPed);
};

class CTaskComplex : public CTask
{
public:
	CTaskComplex() : CTask() {}
	CTaskComplex(ITaskComplex * pTask) : CTask(pTask) {}

	CTask * GetSubTask();
	void      SetSubTask(CTask * pSubTask);
	CTask * CreateNextSubTask(CPed * pPed);
	CTask * CreateFirstSubTask(CPed * pPed);
	CTask * ControlSubTask(CPed * pPed);
};

template <class T>
class CPool;
typedef CPool<ITask> CTaskPool;

_GAME_END

#endif // CTask_h
