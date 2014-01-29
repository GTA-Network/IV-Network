#ifndef CGameMainScript_h
#define CGameMainScript_h

#include <Common.h>
#include "EFLC/CGameScript.h"

namespace EFLC
{

	class CGameMainScript : public GtaThread
	{
	private:
		LPVOID m_pFiber = nullptr;

	public:
		CGameMainScript();
		~CGameMainScript();

		eThreadState Run(unsigned int opsToExecute);

		void RunScript();
	};

};

#endif // CGameMainScript_h