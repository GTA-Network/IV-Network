#include <CCore.h>
#include "CGameMainScript.h"
#include "CIVScript.h"

extern	CCore				* g_pCore;

namespace EFLC
{

#define g_pActiveThread (*(GtaThread**) (g_pCore->GetBase()  + 0x16EAD50))

	LPVOID pMainFiber = nullptr;

	CGameMainScript::CGameMainScript() :
		GtaThread()
	{

	}

	CGameMainScript::~CGameMainScript()
	{

	}

#define createNetworkPools ((bool(__cdecl *)(bool unk))(((g_pCore->GetBase() + 0x4DF3A0))))
#define deleteNetworkPools ((int(__cdecl *)())(((g_pCore->GetBase() + 0x4DDF90))))

	//TASK INFO TEST - END

	bool reloaded = false;

	void CGameMainScript::RunScript()
	{
		unsigned int pid = 0;
		CIVScript::CreatePlayer(0, 756.774f, -214.403f, 4.8223f, &pid);

		//disable police
		CIVScript::SetMaxWantedLevel(0);
		CIVScript::SetWantedMultiplier(0.0f);

		createNetworkPools(true);

		g_pCore->OnGameLoad();

		while (m_Context.State != ThreadStateKilled)
		{
			g_pCore->OnGameUpdate();
			SwitchToFiber(pMainFiber);
		}
	}

	void __stdcall fiberstart(void* a1)
	{
		((CGameMainScript*)a1)->RunScript();
		SwitchToFiber(pMainFiber);
	}

	eThreadState CGameMainScript::Run(unsigned int opsToExecute)
	{
		GtaThread* oldThread = g_pActiveThread;
		g_pActiveThread = this;

		if (!pMainFiber)
		{
			pMainFiber = ConvertThreadToFiber(0);
		}

		if (!m_pFiber)
			m_pFiber = CreateFiber(0, fiberstart, this);

		if (m_pFiber)
			SwitchToFiber(m_pFiber);

		g_pActiveThread = oldThread;
		return ThreadStateRunning;
	}

};