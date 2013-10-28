//========= IV: Network - https://github.com/GTA-Network/IV-Network ============
//
// File: CSQLite.cpp
// Project: Shared
// Author: xForce <xf0rc3.11@gmail.com>
// License: See LICENSE in root directory
//
//==============================================================================

#include "CSQLite.h"


CSQLite::CSQLite()
	: m_pSQLite(0),
	m_bIsOpen(false)
{
	
}

bool CSQLite::Open(const char* szFileName)
{
	if(sqlite3_open(szFileName, &m_pSQLite) != SQLITE_OK)
	{
		printf(sqlite3_errmsg(m_pSQLite));
		return false;
	}
	m_bIsOpen = true;
	return true;
}

bool CSQLite::Query(const char * szSql, std::map<const char*, std::list<const char*>> &result)
{
	if(!m_bIsOpen)
	{
		printf("Database is not open");
		return 0;
	}

	sqlite3_exec(m_pSQLite, szSql, 
		[] (void *NotUsed, int argc, char **argv, char **azColName) -> int
		{
			std::map<const char*, std::list<const char*>> *result = (std::map<const char*, std::list<const char*>>*)NotUsed;
			int columnCount = argc;
			for(int n = 0; n < columnCount; ++n)
			{
				int valueLength = strlen(argv[n]);
				int nameLength = strlen(azColName[n]);

				char* columnName = new char[nameLength+1];
				memcpy(columnName, azColName[n], nameLength);
				columnName[nameLength] = 0;

				char* columnValue = new char[valueLength+1];
				memcpy(columnValue, argv[n], valueLength);
				columnValue[valueLength] = 0;
				
				auto column = result->find(columnName);
				if(column == result->end())
				{
					result->insert(std::pair<const char*, std::list<const char*>>(columnName, std::list<const char*>()));
				}

				column->second.push_back(columnValue);
			}
			return 1;
		}
		, &result, 0);

		return 0;
}


void CSQLite::Close()
{
	m_bIsOpen = false;
	sqlite3_close(m_pSQLite);
}