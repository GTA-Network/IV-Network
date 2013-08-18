//================ IV:Multiplayer - https://github.com/IVMultiplayer/IVMultiplayer ================
//
// File: CGameFiles.cpp
// Project: Client.Core
// Author: FRi<FRi.developing@gmail.com>
// License: See LICENSE in root directory
//
//==========================================================================================

#if 0
#include	"CGameFiles.h"
#include	<CRC.h>
#include	<zlib-1.2.5/zlib.h>
#include	<CZlib.h>
#include	<CCore.h>

extern	CCore				* g_pCore;

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
	{0x1B8184BB, "multiplayer\\datafiles\\1.ivmp", true, "multiplayer\\common\\data\\carcols.dat", true},
	{0x7D1B7010, "multiplayer\\datafiles\\2.ivmp", true, "multiplayer\\common\\data\\cargrp.dat", true},
	{0x2B2524F3, "multiplayer\\datafiles\\3.ivmp", true, "multiplayer\\common\\data\\default.dat", true},
	{0xAE2D4AF2, "multiplayer\\datafiles\\4.ivmp", true, "multiplayer\\common\\data\\gta.dat", true},
	{0xAE2D4AF2, "multiplayer\\datafiles\\5.ivmp", true, "multiplayer\\common\\data\\handling.dat", true},
	{0xAE2D4AF2, "multiplayer\\datafiles\\6.ivmp", true, "multiplayer\\common\\data\\handlingeflc.dat", true},
	{0xAE2D4AF2, "multiplayer\\datafiles\\7.ivmp", true, "multiplayer\\common\\data\\hud.dat", true},
	{0xAE2D4AF2, "multiplayer\\datafiles\\8.ivmp", true, "multiplayer\\common\\data\\hudColor.dat", true},
	{0xAE2D4AF2, "multiplayer\\datafiles\\9.ivmp", true, "multiplayer\\common\\data\\images.txt", true},
	{0xAE2D4AF2, "multiplayer\\datafiles\\10.ivmp", true, "multiplayer\\common\\data\\vehicles.ide", true},
	{0xAE2D4AF2, "multiplayer\\datafiles\\11.ivmp", true, "multiplayer\\common\\data\\vehicleseflc.ide", true},
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
#endif // 0
