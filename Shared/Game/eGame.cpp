/*
* Copyright C GTA-Network Team
*
* Redistribution and use in source and binary forms, with or without
* modification, are permitted provided that the following conditions are
* met:
*
*     * Redistributions of source code must retain the above copyright
* notice, this list of conditions and the following disclaimer.
*     * Redistributions in binary form must reproduce the above
* copyright notice, this list of conditions and the following disclaimer
* in the documentation and/or other materials provided with the
* distribution.
*     * Neither the name of GTA-Network nor the names of its
* contributors may be used to endorse or promote products derived from
* this software without specific prior written permission.
*
* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
* "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
* LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
* A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
* OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
* SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES INCLUDING, BUT NOT
* LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
* DATA, OR PROFITS; OR BUSINESS INTERRUPTION HOWEVER CAUSED AND ON ANY
* THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
* INCLUDING NEGLIGENCE OR OTHERWISE ARISING IN ANY WAY OUT OF THE USE
* OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

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
