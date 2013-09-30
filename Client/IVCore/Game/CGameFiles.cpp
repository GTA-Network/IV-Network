//================= IV:Network - https://github.com/GTA-Network/IV-Network =================
//
// File: CGameFiles.cpp
// Project: Client.Core
// Author: FRi<FRi.developing@gmail.com>
// License: See LICENSE in root directory
//
//==========================================================================================

#include	"CGameFiles.h"
#include	<CRC.h>
#include	<zlib-1.2.5/zlib.h>
#include	<CZlib.h>

#ifdef _CLIENT
#include	<CCore.h>
extern	CCore				* g_pCore;
#endif

CString					CGameFiles::m_strError;
std::list< CString >	CGameFiles::m_deleteFiles;

struct GameFile
{
	unsigned			uiChecksum;
	const char			* szFile;
	bool				bCompressed;
	const char			* szOutput;
	bool				bDeleteAfterDecompress;
}

gameFiles [] =
{
	// multiplayer includes
	{0x1B8184BB, "multiplayer\\datafiles\\1.ivn", true, "multiplayer\\pc\\textures\\loadingscreens.wtd", true},
	{0x1B8184BB, "multiplayer\\datafiles\\2.ivn", true, "multiplayer\\common\\data\\loadingscreens_pc_eflc_v2.dat", true},
	{0x1B8184BB, "multiplayer\\datafiles\\3.ivn", true, "multiplayer\\pc\\textures\\radio_hud_noncolored.wtd", true},
	{0x1B8184BB, "multiplayer\\datafiles\\4.ivn", true, "multiplayer\\common\\data\\hud_eflc.dat", true},
};

bool CGameFiles::CheckFiles()
{
	// Loop through all files that need checking
	for (int i = 0; i < ARRAY_LENGTH(gameFiles); i++)
	{
		// Does the file not exist?
		if (!SharedUtility::Exists(gameFiles[i].szFile))
		{
			// Set the last error
			SetLastError(CString("Can't find the file '%s'.", gameFiles[i].szFile));

			return false;
		}

		// Create the file checksum
		CFileChecksum pFileChecksum;

		// Calculate the current file checksum
		pFileChecksum.Calculate(gameFiles[i].szFile);

		// Does the file checksum not match?
		if (pFileChecksum.GetChecksum() != gameFiles[i].uiChecksum)
		{
			// Set the last error
			SetLastError(CString("The file '%s' has been modified.", gameFiles[i].szFile));

			CLogFile::Printf("File Error: '%s', expected checksum 0x%p, got 0x%p", gameFiles[i].szFile, gameFiles[i].uiChecksum, pFileChecksum.GetChecksum());

			//return false;
		}

		// Does this file need decompressing?
		if (gameFiles[i].bCompressed)
		{
			// Decompress the file
			int iResult = CZlib::Decompress(gameFiles[i].szFile, gameFiles[i].szOutput);

			// Did the file fail to decompress?
			if (iResult != Z_OK)
			{
				// Set the last error
				SetLastError(CString("Failed to decompress the file %s. (Error: %d)", gameFiles[i].szFile, iResult));

				//return false;
			}

			// Should we delete this file?
			if (gameFiles[i].bDeleteAfterDecompress)
			{
				// Push the file onto the delete queue
				m_deleteFiles.push_back(gameFiles[i].szOutput);
			}
		}
	}

	return true;
}

void CGameFiles::CleanFiles()
{
	// Delete the queued items
	for (std::list< CString >::iterator iter = m_deleteFiles.begin(); iter != m_deleteFiles.end(); iter++)
	{
		// Delete the item
		DeleteFile((*iter).Get());
	}

	// Clear the queue
	m_deleteFiles.clear();
}

void CGameFiles::SetLastError(CString strError)
{
	m_strError = strError;
}

CString CGameFiles::GetLastError(void)
{
	return m_strError;
} 