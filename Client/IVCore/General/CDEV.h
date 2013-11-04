//================= IV:Network - https://github.com/GTA-Network/IV-Network =================
//
// File: CDEV.h
// Project: Client.Core
// Author: FRi<FRi.developing@gmail.com>
// License: See LICENSE in root directory
//
//==========================================================================================

#ifndef CDEV_H
#define CDEV_H
#include <CString.h>
#include <IVCore/Game/IVEngine/CIVTask.h>

class CDevelopment {
private:
	static CString			MakeSubTaskString(CString strName, CIVTask* pTask);
	static CString			MakeTaskString(CString strName, CIVTask* pTask);
public:
	static void				Pulse();
	static void				DrawPedTasks(CIVPed* pPed);
};

#endif