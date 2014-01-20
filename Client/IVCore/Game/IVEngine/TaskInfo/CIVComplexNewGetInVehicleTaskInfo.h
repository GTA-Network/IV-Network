#ifndef CIVComplexNewGetInVehicleTaskInfo_h
#define CIVComplexNewGetInVehicleTaskInfo_h

#include "CIVVehicleTaskInfo.h"

class IVComplexNewGetInVehicleTaskInfo : public IVVehicleTaskInfo
{
public:
	virtual ~IVComplexNewGetInVehicleTaskInfo();	
};

class CIVComplexNewGetInVehicleTaskInfo : public CIVVehicleTaskInfo
{
public:
	CIVComplexNewGetInVehicleTaskInfo();
	~CIVComplexNewGetInVehicleTaskInfo();

	bool Serialize(RakNet::BitStream * pBitStream);
	bool Deserialize(RakNet::BitStream * pBitStream);	
};

#endif // CIVComplexNewGetInVehicleTaskInfo_h