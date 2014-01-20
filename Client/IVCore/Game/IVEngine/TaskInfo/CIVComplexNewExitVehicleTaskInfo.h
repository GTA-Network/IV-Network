#ifndef CIVComplexNewExitVehicleTaskInfo_h
#define CIVComplexNewExitVehicleTaskInfo_h

#include "CIVVehicleTaskInfo.h"

class IVComplexNewExitVehicleTaskInfo : public IVVehicleTaskInfo
{
public:
	virtual ~IVComplexNewExitVehicleTaskInfo();
};


class CIVComplexNewExitVehicleTaskInfo : public CIVVehicleTaskInfo
{
public:
	CIVComplexNewExitVehicleTaskInfo();
	~CIVComplexNewExitVehicleTaskInfo();

	bool Serialize(RakNet::BitStream * pBitStream);
	bool Deserialize(RakNet::BitStream * pBitStream);	
};

#endif // CIVComplexNewExitVehicleTaskInfo_h