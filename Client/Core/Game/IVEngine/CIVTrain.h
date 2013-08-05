//================ IV:Multiplayer - https://github.com/IVMultiplayer/IVMultiplayer ================
//
// File: CIVTrain.h
// Project: Client.Core
// Author: FRi<FRi.developing@gmail.com>
// License: See LICENSE in root directory
//
//==========================================================================================

#ifndef CIVTrain_h
#define CIVTrain_h

#include <Common.h>
#include <Game/CGame.h>
#include <CLogFile.h>

// Not sure.. 
class IVTrain
{
public:
	PAD(IVTrain,pad0,4);			// 00-03
	DWORD dwHandle;					// 04-07
    CVector3 vecPosition;			// 08-19
    PAD(IVTrain,pad2,19);			// 20-38
    DWORD dwUnkown1;				// 39-43
    BYTE byteState;                 // 44
    BYTE byteUnkown2;				// 45
	PAD(IVTrain,pad3,2);			// 46-78
    DWORD dwHashValue;				// 48-52
    PAD(IVTrain,pad4,347);			// 53-399
    BYTE byteIsDriving;             // 400-401
    PAD(IVTrain,pad5,205);          // 402-607
    DWORD dwScriptingHandle;        // 608-612
};

class CIVTrain
{
private:
	IVTrain *	m_pTrain;
	DWORD		m_dwPointer;
	EntityId	m_trainId;
	CString		m_strTrainName;
public:
	CIVTrain(EntityId trainId, DWORD dwTrainPointer, CString strTrainName);
	~CIVTrain();

	void				SetTrainOffsetsAndCreate(EntityId trainRegisterId);

	unsigned int		GetTrainHandle();
	DWORD				GetTrainPointer();
};

#endif // CIVTrain_h