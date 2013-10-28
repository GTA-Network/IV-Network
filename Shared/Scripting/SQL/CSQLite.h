//========= IV: Network - https://github.com/GTA-Network/IV-Network ============
//
// File: CSQLite.h
// Project: Client.Core
// Author: xForce <xf0rc3.11@gmail.com>
// License: See LICENSE in root directory
//
//==============================================================================

#ifndef CSQLite_h
#define CSQLite_h


#include <Sqlite/sqlite3.h>
#include <map>
#include <list>

class CSQLite {
private:
	sqlite3 * m_pSQLite;
	bool	  m_bIsOpen;
public:
	CSQLite();
	~CSQLite();

	bool Open(const char* szFileName);
	bool Query(const char* szSql, std::map<const char*, std::list<const char*>> &result);
	void Close();

	bool IsOpen() { return m_bIsOpen; }
};

#endif // CSQLite_h