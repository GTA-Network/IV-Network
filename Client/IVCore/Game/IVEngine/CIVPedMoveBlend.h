//================= IV:Network - https://github.com/GTA-Network/IV-Network =================
//
// File: CIVPedMoveBlend.h
// Project: Client.Core
// Author: FRi<FRi.developing@gmail.com>
// License: See LICENSE in root directory
//
//==========================================================================================

#ifndef CIVPedMoveBlend_h
#define CIVPedMoveBlend_h

#include <IV/IVCommon.h>

class IVPedMoveBlendBase {
public:
	virtual ~IVPedMoveBlendBase();
	virtual void Function1();
	virtual void Function2(); // sets flag
	virtual void Function3();
	virtual void Function4();
	virtual void Function5();
	virtual void Function6();
	virtual void Function7();
	virtual void Function8();
	virtual void Function9();
	virtual void Function10();
	virtual void Function11();
	virtual void Function12();
	virtual void Function13();
	virtual void Function14();
	virtual void Function15();
	virtual void Function16();
	virtual void Function17();
	virtual void Function18();
	virtual void Function19();
	virtual void Function20();
	virtual void Function21();
	virtual void Function22();
	virtual void Function23();
	virtual void Function24();
	virtual void Function25();

};

class IVPedMoveBlendOnFoot : public IVPedMoveBlendBase
{

};

class CIVPedMoveBlendOnFoot
{
public:
	CIVPedMoveBlendOnFoot();
	~CIVPedMoveBlendOnFoot();
};

#endif // CIVPedMoveBlend_h
