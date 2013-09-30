//================= IV:Network - https://github.com/GTA-Network/IV-Network =================
//
// File: CTime.h
// Project: Client.Core
// Author: FRi <FRi.developing@gmail.com>
// License: See LICENSE in root directory
//
//==============================================================================

#ifndef CTime_h
#define CTime_h

class CTime {
public:
	static CTime				*m_pInstance;
	static const unsigned int	DEFAULT_MINUTE_DURATION;

private:
	unsigned long				m_ulTimeSet;
	unsigned char				m_ucHour;
	unsigned char				m_ucMinute;
	unsigned char				m_ucDayOfWeek;
	unsigned					m_uiMinuteDuration;

public:
								CTime();
								~CTime();

	static CTime				*GetInstance() { return m_pInstance; }

	void						SetTime(const unsigned char ucHour, const unsigned char ucMinute);
	void						GetTime(unsigned char * ucHour, unsigned char * ucMinute);

	void						SetMinuteDuration(const unsigned int uiMinuteDuration);
	unsigned int				GetMinuteDuration();

	void						SetDayOfWeek(const unsigned char ucDayOfWeek);
	unsigned char				GetDayOfWeek();

	void						Pulse();
};

#endif // CTime_h