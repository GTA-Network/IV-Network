
// TODO: rename this file
#ifndef CDownloadManager_h
#define CDownloadManager_h

class TransferCB : public RakNet::FileListTransferCBInterface
{
public:
	bool OnFile(OnFileStruct *onFileStruct);
	void OnFileProgress(FileProgressStruct *fps);
	bool OnDownloadComplete(DownloadCompleteStruct *dcs);
};

#endif // CDownloadManager_h