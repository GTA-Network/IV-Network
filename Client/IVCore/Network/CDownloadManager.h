#ifndef CDOWNLOADMANAGER_H
#define CDOWNLOADMANAGER_H

class CDownloadManager
{
private:
	RakNet::DirectoryDeltaTransfer* m_delta;
public:
	CDownloadManager(RakNet::DirectoryDeltaTransfer* pDelta);
	~CDownloadManager();

	void Process();
};

class TransferCB : public RakNet::FileListTransferCBInterface
{
public:
	bool OnFile(OnFileStruct *onFileStruct);
	void OnFileProgress(FileProgressStruct *fps);
	bool OnDownloadComplete(DownloadCompleteStruct *dcs);
};

#endif