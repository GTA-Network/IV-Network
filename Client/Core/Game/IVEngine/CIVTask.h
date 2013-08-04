//================ IV:Multiplayer - https://github.com/IVMultiplayer/IVMultiplayer ================
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
#include "CIVPed.h"

static const char * GetTaskName( int iTaskType );

class IVTaskVFTable
{
public:
	DWORD ScalarDeletingDestructor;
	DWORD Clone;
	DWORD IsSimple;
	DWORD GetType;
	DWORD m10;
	DWORD MakeAbortable;
	DWORD m18;
	DWORD m1C;
	DWORD m20;
	DWORD m24;
	DWORD m28;
	DWORD m2C;
	DWORD m30;
	DWORD m34;
	DWORD m38;
	DWORD m3C;
	DWORD m40;
};

class IVTaskSimpleVFTable : public IVTaskVFTable
{
public:
	DWORD ProcessPed;
	DWORD m48;
	DWORD m4C;
};

class IVTaskComplexVFTable : public IVTaskVFTable
{
public:
	DWORD SetSubTask;
	DWORD CreateNextSubTask;
	DWORD CreateFirstSubTask;
	DWORD ControlSubTask;
};

class IVTask
{
public:
	IVTaskVFTable * m_pVFTable;
	IVTask * m_pParent;
};

class IVTaskSimple : public IVTask
{
public:
};

class IVTaskComplex : public IVTask
{
public:
	IVTask * m_pSubTask;
};

class CIVTask
{

private:

	IVTask				* m_pTask;

public:

	CIVTask( );
	CIVTask( IVTask * pTask );
	~CIVTask( );

	void				SetTask( IVTask * pTask ) { m_pTask = pTask; }
	IVTask				* GetTask( ) { return m_pTask; }

	void				Create( );
	void				Destroy( );
	CIVTask				* GetParent( );
	CIVTask				* Clone( );
	bool				IsSimple( );
	int					GetType( );
	const char			* GetName( );
	bool				MakeAbortable( CIVPed * pPed, int iAbortPriority, void * pEvent = NULL );
	void				SetAsPedTask( CIVPed * pPed, int iTaskPriority, bool bForceNewTask = false );

};

class CIVTaskSimple : public CIVTask
{
public:
	CIVTaskSimple( ) : CIVTask( ) {}
	CIVTaskSimple( IVTaskSimple * pTask ) : CIVTask( pTask ) { }

	bool		ProcessPed( CIVPed * pPed );
};

class CIVTaskComplex : public CIVTask
{
public:
	CIVTaskComplex( ) : CIVTask( ) { }
	CIVTaskComplex( IVTaskComplex * pTask ) : CIVTask( pTask ) { }

	CIVTask			* GetSubTask( );
	void			SetSubTask( CIVTask * pTask );
	CIVTask			* CreateNextSubTask( CIVPed * pPed );
	CIVTask			* CreateFirstSubTask( CIVPed * pPed );
	CIVTask			* ControlSubTask( CIVPed * pPed );
};

#endif // CIVTask_h