#include <CCore.h>
#include <RakNet/FileListTransferCBInterface.h>

#include "CDownloadManager.h"

extern CCore * g_pCore;

CDownloadManager::CDownloadManager(RakNet::DirectoryDeltaTransfer * pDelta) :
	m_delta(pDelta)
{

}

CDownloadManager::~CDownloadManager()
{

}

void CDownloadManager::Process()
{
	m_delta->DownloadFromSubdirectory("client_files", SharedUtility::GetAbsolutePath(CString("client_resources/%s", SharedUtility::ConvertStringToPath(CString("%s:%i", g_pCore->GetHost().Get(), g_pCore->GetPort())).Get())).Get(), false, g_pCore->GetNetworkManager()->GetServerAddress(), new TransferCB, HIGH_PRIORITY, 0, NULL);
	g_pCore->GetResourceManager()->SetResourceDirectory(CString("client_resources/%s", SharedUtility::ConvertStringToPath(CString("%s:%i", g_pCore->GetHost().Get(), g_pCore->GetPort())).Get()));
}

bool TransferCB::OnFile(OnFileStruct *onFileStruct)
{
	assert(onFileStruct->byteLengthOfThisFile >= onFileStruct->bytesDownloadedForThisFile);
	CLogFile::Printf("%i. (100%%) %i/%i %s %ib / %ib\n", onFileStruct->setID, onFileStruct->fileIndex + 1, onFileStruct->numberOfFilesInThisSet, onFileStruct->fileName, onFileStruct->byteLengthOfThisFile, onFileStruct->byteLengthOfThisSet);

	// Return true to have RakNet delete the memory allocated to hold this file.
	// False if you hold onto the memory, and plan to delete it yourself later
	return true;
}

void TransferCB::OnFileProgress(FileProgressStruct *fps)
{
	assert(fps->onFileStruct->byteLengthOfThisFile >= fps->onFileStruct->bytesDownloadedForThisFile);
	CLogFile::Printf("%i (%i%%) %i/%i %s %ib / %ib\n", fps->onFileStruct->setID, (int) (100.0*(double) fps->partCount / (double) fps->partTotal),
		fps->onFileStruct->fileIndex + 1,
		fps->onFileStruct->numberOfFilesInThisSet,
		fps->onFileStruct->fileName,
		fps->onFileStruct->byteLengthOfThisFile,
		fps->onFileStruct->byteLengthOfThisSet,
		fps->firstDataChunk);
}

bool TransferCB::OnDownloadComplete(DownloadCompleteStruct *dcs)
{
	CLogFile::Printf("Download complete.\n");

	// Send to the server
	RakNet::BitStream pBitStream;

	// Write the player nickname
	pBitStream.Write(RakNet::RakString(g_pCore->GetNick().Get()));

	// Write the player serial
	pBitStream.Write(RakNet::RakString(SharedUtility::GetSerialHash().Get()));

	g_pCore->GetNetworkManager()->Call(GET_RPC_CODEX(RPC_DOWNLOAD_FINISH), NULL, HIGH_PRIORITY, RELIABLE_ORDERED, true);
	return false;
}