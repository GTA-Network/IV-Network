#pragma once

#include "CTimer.h"
#include <list>

class CTimerManager : public std::list<CTimer *>
{
private:

public:
	CTimerManager();
	~CTimerManager();

	bool DoesExist(CTimer* pTimer);

	void Pulse();
};
