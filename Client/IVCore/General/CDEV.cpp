//================= IV:Network - https://github.com/GTA-Network/IV-Network =================
//
// File: CDEV.cpp
// Project: Client.Core
// Author: FRi<FRi.developing@gmail.com>
// License: See LICENSE in root directory
//
//==========================================================================================

#include "CDEV.h"
#include <CCore.h>

extern CCore * g_pCore;

void CDevelopment::Pulse()
{

}

CString CDevelopment::MakeSubTaskString(CString strName, CIVTask* pTask)
{
	CString str;
	if(pTask)
	{
		str += strName;
		str += pTask->GetName();
		str += "\n";
		if(!pTask->IsSimple() && ((CIVTaskComplex*) pTask)->GetSubTask())
			str += MakeSubTaskString(strName + "    ", ((CIVTaskComplex*) pTask)->GetSubTask());
	}

	return str;
}

CString CDevelopment::MakeTaskString(CString strName, CIVTask* pTask)
{
	CString str;
	if(pTask)
	{
		str += strName;
		str += pTask->GetName();
		str += "\n";
		if(!pTask->IsSimple() && ((CIVTaskComplex*) pTask)->GetSubTask())
			str += MakeSubTaskString("    ", ((CIVTaskComplex*) pTask)->GetSubTask());
	}

	return str;
}

void CDevelopment::DrawPedTasks(CIVPed* pPed)
{
	CString strTasks;

	/** Prioritry Tasks **/
	strTasks += "Priority Tasks: \n";

	strTasks += MakeTaskString("PhysicalResponse: ", pPed->GetPedTaskManager()->GetTask(TASK_PRIORITY_PHYSICAL_RESPONSE));
	strTasks += MakeTaskString("EventResponseTemp: ", pPed->GetPedTaskManager()->GetTask(TASK_PRIORITY_EVENT_RESPONSE_TEMP));
	strTasks += MakeTaskString("EventResponseNonTemp: ", pPed->GetPedTaskManager()->GetTask(TASK_PRIORITY_EVENT_RESPONSE_NONTEMP));
	strTasks += MakeTaskString("Primary: ", pPed->GetPedTaskManager()->GetTask(TASK_PRIORITY_PRIMARY));
	strTasks += MakeTaskString("Default: ", pPed->GetPedTaskManager()->GetTask(TASK_PRIORITY_DEFAULT));
	strTasks += "\n";

	/**************************************************************************************************/

	strTasks += "Secondary Tasks: \n";
	strTasks += MakeTaskString("Attack: ", pPed->GetPedTaskManager()->GetTask(TASK_SECONDARY_ATTACK));
	strTasks += MakeTaskString("Duck: ", pPed->GetPedTaskManager()->GetTask(TASK_SECONDARY_DUCK));
	strTasks += MakeTaskString("Say: ", pPed->GetPedTaskManager()->GetTask(TASK_SECONDARY_SAY));
	strTasks += MakeTaskString("Facial Complex: ", pPed->GetPedTaskManager()->GetTask(TASK_SECONDARY_FACIAL_COMPLEX));
	strTasks += MakeTaskString("Partial Anim: ", pPed->GetPedTaskManager()->GetTask(TASK_SECONDARY_PARTIAL_ANIM));
	strTasks += MakeTaskString("IK: ", pPed->GetPedTaskManager()->GetTask(TASK_SECONDARY_IK));
	strTasks += "\n";

	/**************************************************************************************************/

	strTasks += "Movement Tasks: \n";
	strTasks += MakeTaskString("Movement 1: ", pPed->GetPedTaskManager()->GetTask(TASK_MOVEMENT_UNKNOWN0));
	strTasks += MakeTaskString("Movement 2: ", pPed->GetPedTaskManager()->GetTask(TASK_MOVEMENT_UNKNOWN1));
	strTasks += MakeTaskString("Movement 3: ", pPed->GetPedTaskManager()->GetTask(TASK_MOVEMENT_UNKNOWN2));

	g_pCore->GetGraphics()->DrawText(600.0f, 26.0f, D3DCOLOR_ARGB(255, 255, 255, 255), 1.0f, DT_NOCLIP, true, strTasks.Get());
}