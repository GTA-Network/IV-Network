//================= IV:Network - https://github.com/GTA-Network/IV-Network =================
//
// File: eGame.h
// Project: Shared
// Author: FRi<FRi.developing@gmail.com>
// License: See LICENSE in root directory
//
//==========================================================================================

#include "eGame.h"
#include <Common.h>
#include <Network/CBitStream.h>

bool CControlState::operator== (const CControlState& o) const
{
	// todo: alternative
	return ((!memcmp(this, &o, sizeof(CControlState))) != 0);
}

bool CControlState::operator!= (const CControlState& o) const
{
	// todo: alternative
	return (memcmp(this, &o, sizeof(CControlState)) != 0);
}

void CControlState::Serialize(CBitStream * pBitStream) const
{
	pBitStream->Write((char *)ucOnFootMove, sizeof(ucOnFootMove));
	pBitStream->Write((char *)ucInVehicleMove, sizeof(ucInVehicleMove));
	pBitStream->Write((char *)ucInVehicleTriggers, sizeof(ucInVehicleTriggers));
	pBitStream->WriteBits((unsigned char *)&keys, KEY_COUNT);
}

bool CControlState::Deserialize(CBitStream * pBitStream)
{
	if(!pBitStream->Read((char *)ucOnFootMove, sizeof(ucOnFootMove)))
		return false;

	if(!pBitStream->Read((char *)ucInVehicleMove, sizeof(ucInVehicleMove)))
		return false;

	if(!pBitStream->Read((char *)ucInVehicleTriggers, sizeof(ucInVehicleTriggers)))
		return false;

	if(!pBitStream->ReadBits((unsigned char *)&keys, KEY_COUNT))
		return false;

	return true;
}
