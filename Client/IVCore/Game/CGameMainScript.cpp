#include <CCore.h>
#include "CGameMainScript.h"
#include "EFLC/CScript.h"

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


#ifdef TASKINFO_TEST
		if (!reloaded)
		{
			reloaded = true;

			EFLC::CNativeInvoke::Invoke<unsigned int>(EFLC::CScript::NATIVE_SHUTDOWN_AND_LAUNCH_SINGLE_PLAYER_GAME);
		}
#endif


		EFLC::CScript::CreatePlayer(0, 756.774f, -214.403f, 4.8223f, &pid);

#ifdef TASKINFO_TEST
		createNetworkPools(true);
#endif

		//disable police
		EFLC::CScript::SetMaxWantedLevel(0);
		EFLC::CScript::SetWantedMultiplier(0.0f);

		g_pCore->OnGameLoad();

		while (m_Context.State != ThreadStateKilled)
		{

#ifdef TASKINFO_TEST
			RakNet::BitStream bitStream;
			bitStream.Reset();
			if (g_pCore->GetGame()->GetLocalPlayer())
			{
				g_pCore->GetGame()->GetLocalPlayer()->SerializeTaskInfo(&bitStream);

				if (g_pCore->GetGame()->GetPlayerManager())
				if (g_pCore->GetGame()->GetPlayerManager()->GetAt(1))
					g_pCore->GetGame()->GetPlayerManager()->GetAt(1)->DeserializeTaskInfo(&bitStream);
			}
#endif		

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