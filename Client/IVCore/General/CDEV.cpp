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

void CDevelopment::DrawPedTasks(CIVPed* pPed, float xOff)
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

	g_pCore->GetGraphics()->DrawText(600.0f + xOff, 26.0f, D3DCOLOR_ARGB(255, 255, 255, 255), 1.0f, DT_NOCLIP, true, strTasks.Get());
}