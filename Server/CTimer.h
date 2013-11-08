
#ifndef CTimer_h
#define CTimer_h

#include <Scripting/CScriptClass.h>

class CScriptTimer;

class CTimer
{
private:
	stScriptFunction	m_callback;
	unsigned int		m_uiInterval;
	int					m_iRepeatings;
	bool				m_bPaused;
	bool				m_bRunning;
	unsigned int		m_uiLastPulse;
	CScriptTimer		*m_pScriptTimer;

public:
	CTimer(stScriptFunction function, int interval, int repeatings);
	~CTimer();

	void Start() { m_bRunning = true; };
	void Stop() { m_bRunning = false; /* TODO: remove timer from manager and free its memory*/ }


	void Pause() { m_bPaused = true; }
	void Resume() { m_bPaused = false; }

	bool IsPaused() { return m_bPaused; }
	bool IsRunning() { return m_bRunning; };

	void SetScriptTimer(CScriptTimer* pTimer) { m_pScriptTimer = pTimer; }
	CScriptTimer* GetScriptTimer() { return m_pScriptTimer; }

	bool Pulse();
};

class CScriptTimer
{
private:
	CTimer		*m_pTimer;

public:
	CScriptTimer() { }
	~CScriptTimer() { }

	CTimer* GetTimer() { return m_pTimer; }
	void	SetTimer(CTimer* pTimer) { m_pTimer = pTimer; }

	void Start() { GetTimer()->Start(); };
	void Stop() { GetTimer()->Stop(); /* TODO: remove timer from manager and free its memory*/ }

	void Pause() { GetTimer()->Pause(); }
	void Resume() { GetTimer()->Resume(); }

	bool IsPaused() { return GetTimer()->IsPaused(); }
	bool IsRunning() { return GetTimer()->IsRunning(); };
};

#endif