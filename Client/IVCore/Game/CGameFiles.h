//================= IV:Network - https://github.com/GTA-Network/IV-Network =================
//
// File: CGameFiles.h
// Project: Client.Core
// Author: FRi<FRi.developing@gmail.com>
// License: See LICENSE in root directory
//
//==========================================================================================

#ifndef CGameFiles_h
#define CGameFiles_h

#include <Common.h>

#define		FILE_NOT_FOUND			1

class CGameFiles {
private:
	static	CString					m_strError;
	static	std::list< CString >	m_deleteFiles;

public:
	static	bool					DecompressFiles();
	static	bool					CheckFiles();

	static	void					CleanFiles();
	static	void					SetLastError(CString strError);
	static	CString					GetLastError();

};

#endif // CGameFiles_h