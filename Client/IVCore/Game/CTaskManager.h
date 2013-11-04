//================= IV:Network - https://github.com/GTA-Network/IV-Network =================
//
// File: CTaskManager.h
// Project: Client.Core
// Author: FRi<FRi.developing@gmail.com>
// License: See LICENSE in root directory
//
//==========================================================================================

#ifndef CTaskManager_h
#define CTaskManager_h

#include <Game/IVEngine/CIVTask.h>

struct ClientTaskPair {
	IVTask * pGameTask;
	CIVTask * pClientTask;
};

class CTaskManager {
private:
	std::list< ClientTaskPair *>	m_taskList;

public:
									CTaskManager() { };
									~CTaskManager();

	bool							AddTask(CIVTask * pClientTask);
	bool							RemoveTask(CIVTask * pClientTask);
	IVTask							* GetGameTaskFromClientTask(CIVTask * pClientTask);
	CIVTask							* GetClientTaskFromGameTask(IVTask * pGameTask, bool bCreateIfNotExist = true);
	bool							HandleTaskDelete(IVTask * pGameTask);
};

#endif // CIVTaskManager_h