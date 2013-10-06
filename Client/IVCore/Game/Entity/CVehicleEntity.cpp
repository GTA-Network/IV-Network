//================= IV:Network - https://github.com/GTA-Network/IV-Network =================
//
// File: CVehicleEntity.cpp
// Project: Client.Core
// Author: FRi<FRi.developing@gmail.com>
// License: See LICENSE in root directory
//
//==============================================================================

#include "CVehicleEntity.h"
#include "CPlayerEntity.h"

#include <Game/IVEngine/CIVModelManager.h>
#include <Game/Entity/CVehicleEntity.h>
#include <IV/CIVScript.h>
#include <Game/CCharacterManager.h>

#include <CCore.h>
extern CCore * g_pCore;

CVehicleEntity::CVehicleEntity(int iVehicleModel, CVector3 vecPos, float fAngle, BYTE color1, BYTE color2, BYTE color3, BYTE color4) : CNetworkEntity()
{
	m_pVehicle = NULL;
	m_vehicleId = INVALID_ENTITY_ID;
	m_pDriver = NULL;
	m_bSpawned = false;
	m_pModelInfo = NULL;

	CNetworkEntity::SetType(VEHICLE_ENTITY);

	// Get the model hash from the model id
	DWORD dwModelHash = CIVModelManager::VehicleIdToModelHash(iVehicleModel);

	// Get the model index
	int iVehicleModelIndex = CIVModelManager::GetModelIndexFromHash(dwModelHash);

	if (iVehicleModelIndex == -1)
	{
		g_pCore->GetChat()->Output(CString("!!! 0x%X ModelHash has no model index !!!", dwModelHash).Get());
		return;
	}

	// Set the model info
	m_pModelInfo = g_pCore->GetGame()->GetModelInfo(iVehicleModelIndex);

	// Set the color
	m_byteColor[0] = color1;
	m_byteColor[1] = color2;
	m_byteColor[2] = color3;
	m_byteColor[3] = color4;

	// Set the interpolate variables
	m_interp.pos.ulFinishTime = 0;
	m_interp.rot.ulFinishTime = 0;

	// Set the rotation
	m_fSpawnAngle = fAngle;

	// Set the spawn position
	memcpy(&m_vecSpawnPosition,&vecPos,sizeof(CVector3));

}

#include <Game/IVEngine/CIVVehicleFactory.h>

CVehicleEntity::~CVehicleEntity()
{
	// Is the vehicle spawned?
	if(IsSpawned())
	{
		// Destroy the vehicle
		Destroy();
	}
}

bool CVehicleEntity::Create()
{
	if (m_pModelInfo == NULL)
		return false;

	// Is the vehicle already spawned?
	if(IsSpawned())
		return false;

	//m_pModelInfo->AddReference(true);

	CIVScript::RequestModel(m_pModelInfo->GetHash());

	while (!g_pCore->GetGame()->GetStreaming()->HasResourceLoaded(eResourceType::RESOURCE_TYPE_WDR, m_pModelInfo->GetIndex()))
	{
		CIVScript_NativeInvoke::Invoke<unsigned int, int>(CIVScript::NATIVE_LOAD_ALL_OBJECTS_NOW, 0);
		Sleep(0);
	}
	Sleep(10);
#if 0
	DWORD dwModelHash = m_pModelInfo->GetHash();
	CIVScript::CreateCar(dwModelHash, 0.0f, 0.0f, 0.0f, &m_uiVehicleHandle, false);
	
	// Create the vehicle instance
	m_pVehicle = new CIVVehicle(g_pCore->GetGame()->GetPools()->GetVehiclePool()->AtHandle(m_uiVehicleHandle));

	//if (*(DWORD*)(m_pVehicle->GetVehicle() + 0x1480))
	//{
	//	int v13 = *(DWORD*) (m_pVehicle->GetVehicle() + 0x1480);
	//	if (v13)
	//		(**(void(__stdcall ***)(DWORD))v13)(1);
	//}

	m_pVehicle->GetVehicle()->CreatePhysics();
#endif
#if 1
	IVVehicleFactory* pVehicleFactory = (IVVehicleFactory*)*(DWORD*) (g_pCore->GetBase() + 0x118A6D4);
	Matrix34 v125;
	((char(_cdecl *)(int, Matrix34*, int, int, int, int))(g_pCore->GetBase() + 0x9C6C00))(*(DWORD *) (*(DWORD *) &m_pModelInfo->GetModelInfo()->IVBaseModelInfo_pad0[4] + 236), &v125, 0, 168, 0, 0);
	//*(WORD*) (g_pCore->GetBase() + 0x4B48D5) = 0x9090;
	IVVehicle * pVehicle = pVehicleFactory->Create(m_pModelInfo->GetIndex(), 1, /*(int)&v125*/0, 1);
	if (pVehicle)
	{
		
#define CModelInfo__AddReference (g_pCore->GetBase() + 0x83F2E0)
		pVehicle->Function76(0);
		//pVehicle->field_41 = 2;
		pVehicle->m_byteFlags1 |= 4u;
		pVehicle->m_dwFlags1 |= 8u; // Fixed
		((int(_cdecl *)(IVVehicle*, char))(g_pCore->GetBase() + 0x86C0B0))(pVehicle, 0);
		pVehicle->CreateDoubleNode();
		pVehicle->Add();
		((void(__thiscall *)(IVVehicle*, char))(g_pCore->GetBase() + 0x9FD530))(pVehicle, 1);
		pVehicle->m_byteFlags10 |= 8u;
		double v83 = ((double(_cdecl*)(float, float))(g_pCore->GetBase() + 0x4AA400))(0.0, 1.0);
		((int(__thiscall *)(IVVehicle*, float))(g_pCore->GetBase() + 0x9F0C20))(pVehicle, v83);
		// Make visible
		// This maybe cause pool overflow if much vehicles are created and destroyed [NEED TEST]
		// If this cause overflow try to delete the create physics before call or disable the call in VehicleFactory::Create
		// Using this above *(WORD*) (g_pCore->GetBase() + 0x4B48D5) = 0x9090; before call to vehiclefactory
		if (*(DWORD*) pVehicle != COffsets::VAR_CBoat__VFTable)
		{
			pVehicle->CreatePhysics();
			pVehicle->ProcessInput();
		}
		
		if (pVehicle->Function79())
			pVehicle->Function80();
		((int(__thiscall *)(DWORD))(CModelInfo__AddReference))((DWORD) m_pModelInfo->GetModelInfo());
		/**(WORD *) &pVehicle->IVVehicle_pad14[7] = (signed int) floorf(1.5f);
		pVehicle->m_byteFlags13 |= 0x10u;
		pVehicle->m_byteColors[0] = 0;
		pVehicle->m_byteColors[1] = 0;
		pVehicle->m_byteColors[2] = 0;
		pVehicle->m_byteColors[3] = 0;*/
#define TYPE_DEF_THIS(ret, params, func) ((ret (__thiscall *)(params))func)

#define CModelInfo__AddReference (g_pCore->GetBase() + 0x83F2E0)

		// Livery stuff
		//((IVVehicle*(__thiscall *)(IVVehicle*))(g_pCore->GetBase() + 0x9EEF70))(pVehicle);

		// sets some flags
		
		
		

		

		// Something with driver at spawn
		//((int(_cdecl *)(IVVehicle*))(g_pCore->GetBase() + 0xA5F910))(pVehicle);

		((char(_cdecl *)(IVVehicle*, int))(g_pCore->GetBase() + 0x958940))(pVehicle, -1);
		((DWORD(_cdecl *)(IVVehicle*, char, DWORD, DWORD))(g_pCore->GetBase() + 0xC39CA0))(pVehicle, 1, 14, 0);
#if 0


		//((IVVehicle*(__thiscall *)(IVVehicle*))(g_pCore->GetBase() + 0x9EEF70))(pVehicle);
		//((void(__thiscall *)(IVVehicle*, char))(g_pCore->GetBase() + 0x9FD530))(pVehicle, 1);
		//((int(_cdecl *)(IVVehicle*, char))(g_pCore->GetBase() + 0x86C0B0))(pVehicle, 0);

		//((int(__thiscall *)(DWORD))(CModelInfo__AddReference))((DWORD)m_pModelInfo->GetModelInfo());

		int v81;
		DWORD v82;
		IVBaseModelInfo * v76 = m_pModelInfo->GetModelInfo();
		char v97 = 0;

		/**(WORD *) &pVehicle->IVVehicle_pad14[7] = (signed int) floorf(v110);
		*(DWORD *)&pVehicle->field_E34 = v120;
		v78 = v109;
		*(DWORD *)&pVehicle->field_E28[8] = v119;
		v79 = v104;
		*(DWORD *)&pVehicle->field_E28[4] = v118;
		v80 = v107;
		pVehicle->field_E28[84] = v107;
		pVehicle->field_E28[83] = v80;
		pVehicle->field_E28[82] = v80;
		v81 = *(DWORD*)pVehicle;
		*(WORD *)&pVehicle->field_E28[56] = v78;
		*(WORD *)&pVehicle->field_E28[58] = v79;
		v73 = v72;
		*(_DWORD *)&pVehicle->field_E8C[180] = LODWORD(v73);
		pVehicle->field_E8C[178] = v71;*/

		//(*(void(__thiscall **)(IVVehicle*, DWORD))(v81 + 304))(pVehicle, 0);
		/*if (sub_D0E5E7() < 16383
			&& (unsigned __int8) sub_8BDF40(pVehicle->m_wModelIndex))*/
		{
			pVehicle->m_byteFlags13 |= 0x10u;
			pVehicle->m_byteColors[0] = *(BYTE *) (v76 + 304);
			pVehicle->m_byteColors[1] = *(BYTE *) (v76 + 305);
			pVehicle->m_byteColors[2] = *(BYTE *) (v76 + 306);
			pVehicle->m_byteColors[3] = *(BYTE *) (v76 + 307);
		}
		/*else
		{
			pVehicle->m_byteFlags13 &= 0xEFu;
			sub_B51890(pVehicle, &v108, &v112, &v113, &v111);
			pVehicle->m_byteColors[0] = v108;
			pVehicle->m_byteColors[1] = v112;
			pVehicle->m_byteColors[2] = v113;
			pVehicle->m_byteColors[3] = v111;
		}*/
		
		((IVVehicle*(__thiscall *)(IVVehicle*))(g_pCore->GetBase() + 0x9EEF70))(pVehicle);
		((void(__thiscall *)(IVVehicle*, char))(g_pCore->GetBase() + 0x9FD530))(pVehicle, 1);

		/*if (pVehicle->field_1354 == 2)
			sub_9D8F50(pVehicle, 0xFFFFFFFFu, -1, -1);
		else
			sub_9DC030(dword_10C8610, dword_F13438, -1);*/
		((int(_cdecl *)(IVVehicle*, char))(g_pCore->GetBase() + 0x86C0B0))(pVehicle, 0);

		//pVehicle->Function71();
		//if (pVehicle->m_byteFlags13 & 0x10)
		//{
		//	((int(__thiscall *)(IVVehicle *, INT16))(g_pCore->GetBase() + 0x9FC930))(pVehicle, 512);
		//	//pVehicle->Repair();
		//}
		/*v84 = BYTE3(v105);
		if (BYTE3(v105))
			dword_10C85F4 = LODWORD(qword_116E35C);*/
		/*if (pVehicle->Function79())
			pVehicle->Function80();*/
		int v85 = (*(int(_cdecl **)(IVVehicle*))(g_pCore->GetBase() + 0xA5F910))(pVehicle);
		/*v86 = sub_C30A40(pVehicle->m_pDriver);
		if (v106 >= v86)
			v106 = sub_C30A40(pVehicle->m_pDriver);
		*(_BYTE *) (v85 + 39) = v106;*/
		((int(__thiscall *)(DWORD))(CModelInfo__AddReference))((DWORD) m_pModelInfo->GetModelInfo());
		//sub_A6DA90(&pVehicle->field_E8C[12], (void *) v85);
		/*
		v87 = *(DWORD *) &pVehicle->field_E28[8];
		v88 = *(DWORD *) &pVehicle->field_E28[4];
		*(DWORD *) &pVehicle->field_E28[16] = *(_DWORD *) &pVehicle->field_E28[12];
		v89 = *(WORD *) &pVehicle->field_E28[58];
		*(DWORD *) &pVehicle->field_E28[12] = v87;
		LOWORD(v87) = *(_WORD *) &pVehicle->field_E28[56];
		*(_DWORD *) &pVehicle->field_E28[8] = v88;
		LOBYTE(v88) = pVehicle->field_E28[84];
		*(_WORD *) &pVehicle->field_E28[60] = v89;
		LOBYTE(v89) = pVehicle->field_E28[83];
		*(WORD *) &pVehicle->field_E28[58] = v87;
		pVehicle->field_E28[85] = v88;
		pVehicle->field_E28[84] = v89;
		*/
		((DWORD(_cdecl *)(IVVehicle*, char, DWORD, DWORD))(g_pCore->GetBase() + 0xC39CA0))(pVehicle, 1, 14, 0);
		//double v90 = ((double(__cdecl *)(DWORD, DWORD))sub_C32CD0)((float) *(BYTE *) (v85 + 39), *(float *) &pVehicle->field_E8C[180]);
		//*(float *) &v104 = v90;
		//v91 = v90;
		((int(_cdecl *)(IVVehicle*))(g_pCore->GetBase() + 0xA5F910))(pVehicle);
		//*(float *) &v102 = sub_C3DA10(pVehicle, &pVehicle->field_E8C[12], v92, LODWORD(v91));
		//v93 = sub_A99E30(LODWORD(v129), LODWORD(v130));
		//v94 = v93;
		//sub_C366D0((int) pVehicle, v94, v104);
		//v95 = v93 * *(float *) &v104;
		//v96 = sub_4752A0(v102, LODWORD(v95));
		//*(float *) &v114 = v129 * v96;
		//v115 = v130 * v96;
		//v116 = v96 * v131;
		//sub_A7C040(&v114);
		((char(_cdecl *)(IVVehicle*, int))(g_pCore->GetBase() + 0x958940))(pVehicle, -1);
#endif

		m_pVehicle = new CIVVehicle(pVehicle);
		//CIVScript::SetCarCollision(GetScriptingHandle(), 0);
	}
#if 0
	// Load the model
	m_pModelInfo->AddReference(true);

	DWORD dwModelHash = m_pModelInfo->GetHash();



	CIVScript::CreateCar(dwModelHash, 0.0f, 0.0f, 0.0f, &m_uiVehicleHandle, false);
	
    // Create the vehicle instance
	m_pVehicle = new CIVVehicle(g_pCore->GetGame()->GetPools()->GetVehiclePool()->AtHandle(m_uiVehicleHandle));
	CIVScript::MarkModelAsNoLongerNeeded(m_pModelInfo->GetHash());
	m_pVehicle->SetColors(m_byteColor[0], m_byteColor[1], m_byteColor[2], m_byteColor[3]);

#endif
#endif

	// Mark as spawned
	m_bSpawned = true;

	CVector3 vecPos;
	GetPosition(vecPos);
	vecPos.fZ = ((double(__cdecl*)(int, int))(g_pCore->GetBase() + 0x9C69F0))(vecPos.fX, vecPos.fY);
	SetPosition(vecPos, true);
	// Reset the vehicle
	Reset();

	CLogFile::Printf("Created vehicle! (Id: %d, Handle: %d)", m_vehicleId, m_uiVehicleHandle);
	return true;
}

bool CVehicleEntity::Destroy()
{
	// Is the vehicle not spawned?
	if(!IsSpawned())
		return false;

	// Remove the vehicle from the world
	m_pVehicle->RemoveFromWorld();

	// Remove the vehicle reference
	m_pModelInfo->RemoveReference();

	// Release the entity
	m_pVehicle->GetEntity()->Remove();

	// Mark vehicle as no longer needed
	IVVehicle * pVehicle = m_pVehicle->GetVehicle();
	*(BYTE *)(pVehicle + 3949) |= 8u;
	*(BYTE *)(pVehicle + 4360) = 1; // Disable function call(some loops through arrays..)

	// Destroy the vehicle
	CIVScript::DeleteCar(&m_uiVehicleHandle);

	// Delete the vehicle instance
	SAFE_DELETE(m_pVehicle);

	// Mark as not spawned
	m_bSpawned = false;

	return true;
}

void CVehicleEntity::Reset()
{
	// Check vehicle iv ptr
	if(!m_pVehicle)
		return;

	// Turn the engine off
	SetEngineState(false);
	
	// Reset Indicators
	SetIndicatorState(false,false,false,false);

	// Disable damage
	//m_pVehicle->SetCarCanBeDamaged(false);
	//m_pVehicle->SetCanBeVisiblyDamaged(false);

}

bool CVehicleEntity::IsMoving()
{
    CVector3 vecMoveSpeed;
    GetMoveSpeed(vecMoveSpeed);

    if(!vecMoveSpeed.IsEmpty())
		return true;

    return false;
}

void CVehicleEntity::StopMoving()
{
	SetMoveSpeed(CVector3());
}

void CVehicleEntity::SoundHorn(int iDuration)
{
    if(IsSpawned())
		m_pVehicle->SoundHorn(iDuration);

    m_ulHornDurationEnd = (SharedUtility::GetTime() + iDuration);
}

unsigned int CVehicleEntity::GetScriptingHandle()
{
	if(IsSpawned())
		return g_pCore->GetGame()->GetPools()->GetVehiclePool()->HandleOf(m_pVehicle->GetVehicle());

	return 0;
}

void CVehicleEntity::SetModel(DWORD dwModelHash)
{
	// Get the model index from the model hash
	int iModelIndex = g_pCore->GetGame()->GetCharacterManager()->ModelHashToVehicleId(dwModelHash);

	// Do we have an invalid model index?
	if(iModelIndex == -1)
	{
		CLogFile::Printf("CClientVehicle::SetModel Failed (Invalid model hash)!");
		return;
	}

	// Has the model not changed?
	if(m_pModelInfo->GetIndex() == iModelIndex)
	{
		CLogFile::Printf("CClientVehicle::SetModel Failed (Model change not needed)!");
		return;
	}

	// Get the new model info
	CIVModelInfo * pNewModelInfo = g_pCore->GetGame()->GetModelInfo(iModelIndex);

	// Is the new model info valid?
	if(!pNewModelInfo || !pNewModelInfo->IsValid() || !pNewModelInfo->IsVehicle())
	{
		CLogFile::Printf("CClientVehicle::SetModel Failed (Invalid model)!");
		return;
	}

	if(IsSpawned())
	{
		// Stream ourselves out
		CLogFile::Printf("CClientVehicle::SetModel Stream Out Begin");
		Destroy();
		CLogFile::Printf("CClientVehicle::SetModel Stream Out Complete");
	}

	// Set the new model info
	m_pModelInfo = pNewModelInfo;

	// Stream ourselves back in
	CLogFile::Printf("CClientVehicle::SetModel Stream In Begin");
	Create();
	CLogFile::Printf("CClientVehicle::SetModel Stream In Complete");
}

void CVehicleEntity::SetColors(BYTE byteColor1, BYTE byteColor2, BYTE byteColor3, BYTE byteColor4)
{
	if(IsSpawned())
		m_pVehicle->SetColors(byteColor1, byteColor2, byteColor3, byteColor4);

	m_byteColor[0] = byteColor1;
	m_byteColor[1] = byteColor2;
	m_byteColor[2] = byteColor3;
	m_byteColor[3] = byteColor4;
}

void CVehicleEntity::GetColors(BYTE &byteColor1, BYTE &byteColor2, BYTE &byteColor3, BYTE &byteColor4)
{
	if(IsSpawned())
		m_pVehicle->GetColors(&byteColor1, &byteColor2, &byteColor3, &byteColor4);
	else
	{
		byteColor1 = m_byteColor[0];
		byteColor2 = m_byteColor[1];
		byteColor3 = m_byteColor[2];
		byteColor4 = m_byteColor[3];
	}
}

void CVehicleEntity::SetPosition(const CVector3& vecPosition, bool bDontCancelTasks, bool bResetInterpolation)
{
	if(IsSpawned())
	{
		if(!bDontCancelTasks)
			CIVScript::SetCarCoordinatesNoOffset(GetScriptingHandle(), vecPosition.fX, vecPosition.fY, vecPosition.fZ);
		else
		{
			//m_pVehicle->RemoveFromWorld();

			//// Set the position in the matrix
			////CIVScript::SetCarCoordinatesNoOffset(GetScriptingHandle(), vecPosition.fX, vecPosition.fY, vecPosition.fZ);
			//CVector3 vecPos = vecPosition;
			//vecPos.fZ = ((double(__cdecl*)(float, float))(g_pCore->GetBase() + 0x9C69F0))(vecPos.fX, vecPos.fY);
			//m_pVehicle->SetPosition(vecPos);


			//m_pVehicle->AddToWorld();
			//m_pVehicle->GetVehicle()->UpdatePhysicsMatrix(true);
			//m_pVehicle->GetVehicle()->ProcessInput();

			CIVScript::SetCarCoordinates(GetScriptingHandle(), vecPosition.fX, vecPosition.fY, vecPosition.fZ);
		}
	}

	m_vecPosition = vecPosition;

	// Reset interpolation if requested
	if(bResetInterpolation)
		RemoveTargetPosition();
}

void CVehicleEntity::GetPosition(CVector3& vecPosition)
{
	if(IsSpawned())
		m_pVehicle->GetPosition(vecPosition);
	else
		vecPosition = m_vecPosition;
}

CVector3 CVehicleEntity::GetPosition()
{
	CVector3 vecPosition;

	if(IsSpawned())
		m_pVehicle->GetPosition(vecPosition);
	else
		vecPosition = m_vecPosition;

	return vecPosition;
}

void CVehicleEntity::SetRotation(const CVector3& vecRotation, bool bResetInterpolation)
{
	if(IsSpawned())
	{
		// Get the vehicle matrix
		Matrix matMatrix;
		m_pVehicle->GetMatrix(matMatrix);

		// Convert the rotation from degrees to radians
		CVector3 vecNewRotation = Math::ConvertDegreesToRadians(vecRotation);

		// Apply the rotation to the vehicle matrix
		CGameFunction::ConvertEulerAnglesToRotationMatrix(vecNewRotation, matMatrix);

		// Set the new vehicle matrix
		m_pVehicle->SetMatrix(matMatrix);
	}

	m_vecRotation = vecRotation;

	// Reset interpolation if requested
	if(bResetInterpolation)
		RemoveTargetRotation();
}

void CVehicleEntity::GetRotation(CVector3& vecRotation)
{
	if(IsSpawned())
	{
		// Get the vehicle matrix
		Matrix matMatrix;
		m_pVehicle->GetMatrix(matMatrix);

		// Convert the matrix to euler angles
		CVector3 vecNewRotation;
		CGameFunction::ConvertRotationMatrixToEulerAngles(matMatrix, vecNewRotation);

		// Flip the rotation
		vecNewRotation.fX = ((2 * PI) - vecNewRotation.fX);
		vecNewRotation.fY = ((2 * PI) - vecNewRotation.fY);
		vecNewRotation.fZ = ((2 * PI) - vecNewRotation.fZ);

		// Convert the rotation from radians to degrees
		vecRotation = Math::ConvertRadiansToDegrees(vecNewRotation);
	}
	else
		vecRotation = m_vecRotation;
}

void CVehicleEntity::SetHealth(unsigned int uiHealth)
	{
	// Are we spawned?
	if(IsSpawned())
		m_pVehicle->SetEngineHealth((float)uiHealth);

	m_uiHealth = uiHealth;
}

unsigned int CVehicleEntity::GetHealth()
{
	// Are we spawned?
	if(IsSpawned())
		return (unsigned int)m_pVehicle->GetEngineHealth();

	return m_uiHealth;
}

void CVehicleEntity::SetPetrolTankHealth(float fHealth)
{
	// Are we spawned?
	if(IsSpawned())
		m_pVehicle->SetPetrolTankHealth((float)fHealth);

	m_fPetrolTankHealth = fHealth;
}

float CVehicleEntity::GetPetrolTankHealth()
{
	// Are we spawned?
	if(IsSpawned())
		return m_pVehicle->GetPetrolTankHealth();

	return m_fPetrolTankHealth;
}

void CVehicleEntity::SetQuaternion(float * quat)
{
	//if(IsSpawned())
		//Scripting::SetVehicleQuaternion(GetScriptingHandle(), quat[0], quat[1], quat[2], quat[3]);
}

void CVehicleEntity::GetQuaternion(float * quat)
{
	//if(IsSpawned())
		//Scripting::GetVehicleQuaternion(GetScriptingHandle(), &quat[0], &quat[1], &quat[2], &quat[3]);
}

void CVehicleEntity::SetMoveSpeed(const CVector3& vecMoveSpeed)
{
	// Are we spawned?
	if(IsSpawned())
		m_pVehicle->SetMoveSpeed(vecMoveSpeed);

	m_vecMoveSpeed = vecMoveSpeed;
}

void CVehicleEntity::GetMoveSpeed(CVector3& vecMoveSpeed)
{
	// Are we spawned?
	if(IsSpawned())
		m_pVehicle->GetMoveSpeed(vecMoveSpeed);
	else
	vecMoveSpeed = m_vecMoveSpeed;
}

void CVehicleEntity::SetTurnSpeed(const CVector3& vecTurnSpeed)
{
	// Are we spawned?
	if(IsSpawned())
		m_pVehicle->SetTurnSpeed(vecTurnSpeed);

	m_vecTurnSpeed = vecTurnSpeed;
}

void CVehicleEntity::GetTurnSpeed(CVector3& vecTurnSpeed)
{
	// Are we spawned?
	if(IsSpawned())
		m_pVehicle->GetTurnSpeed(vecTurnSpeed);
	else
		vecTurnSpeed = m_vecTurnSpeed;
}

void CVehicleEntity::SetSirenState(bool bSirenState)
{
	// Are we spawned?
	if(IsSpawned())
		m_pVehicle->SetSirenState(bSirenState);

	m_bSirenState = bSirenState;
}

bool CVehicleEntity::GetSirenState()
{
	// Are we spawned?
	if(IsSpawned())
		return m_pVehicle->GetSirenState();

	return m_bSirenState;
}

void CVehicleEntity::SetDirtLevel(float fDirtLevel)
{
	// Are we spawned?
	if(IsSpawned())
		m_pVehicle->SetDirtLevel(fDirtLevel);

	m_fDirtLevel = fDirtLevel;
}

float CVehicleEntity::GetDirtLevel()
{
	// Are we spawned?
	if(IsSpawned())
		return m_pVehicle->GetDirtLevel();

	return m_fDirtLevel;
}

BYTE CVehicleEntity::GetMaxPassengers()
{
	// Are we spawned?
	if(IsSpawned())
		return m_pVehicle->GetMaxPasssengers();

	return 0;
}

void CVehicleEntity::SetDoorLockState(DWORD dwDoorLockState)
{
	// Get the actual lock state
	DWORD dwState = 0;

	switch(dwDoorLockState)
	{
		case 0:
			dwState = 0;
			break;
		case 1:
			dwState = 3;
			break;
		case 2:
			dwState = 7;
			break;
		default:
		return;
	}

	m_dwDoorLockState = dwState;

	// Are we spawned?
	if(IsSpawned())
		CIVScript::LockCarDoor(GetScriptingHandle(), m_dwDoorLockState);
}

DWORD CVehicleEntity::GetDoorLockState()
{
	DWORD dwState = m_dwDoorLockState;

	// Are we spawned?
	if(IsSpawned())
		dwState = m_pVehicle->GetDoorLockState();

	switch(dwState)
	{
	case 0:
		return 0;
	case 3:
		return 1;
	case 7:
		return 2;
	default:
		CLogFile::Printf("Unknown vehicle %d door state %d", m_vehicleId, m_pVehicle->GetDoorLockState()); 
	}
	return dwState;
}

void CVehicleEntity::Process()
{
	Interpolate();

	CNetworkEntity::Pulse(this);
}

void CVehicleEntity::UpdateTargetPosition()
{
    // Do we have a target position?
    if(HasTargetPosition())
    {
        // Get our position
        CVector3 vecCurrentPosition;
        GetPosition(vecCurrentPosition);

        // Get the factor of time spent from the interpolation start
        // to the current time.
        unsigned long ulCurrentTime = SharedUtility::GetTime();
        float fAlpha = Math::Unlerp(m_interp.pos.ulStartTime, ulCurrentTime, m_interp.pos.ulFinishTime);

        // Don't let it overcompensate the error too much
        fAlpha = Math::Clamp(0.0f, fAlpha, 1.5f);

        // Get the current error portion to compensate
        float fCurrentAlpha = (fAlpha - m_interp.pos.fLastAlpha);
        m_interp.pos.fLastAlpha = fAlpha;

        // Apply the error compensation
        CVector3 vecCompensation = Math::Lerp(CVector3(), fCurrentAlpha, m_interp.pos.vecError);

        // If we finished compensating the error, finish it for the next pulse
        if(fAlpha == 1.5f)
                m_interp.pos.ulFinishTime = 0;

        // Calculate the new position
        CVector3 vecNewPosition = (vecCurrentPosition + vecCompensation);

        // Check if the distance to interpolate is too far
        if((vecCurrentPosition - m_interp.pos.vecTarget).Length() > 20)
        {
            // Abort position interpolation
            m_interp.pos.ulFinishTime = 0;
            vecNewPosition = m_interp.pos.vecTarget;

            // Abort target interpolation
            if(HasTargetRotation())
            {
                SetRotation(m_interp.rot.vecTarget);
                m_interp.rot.ulFinishTime = 0;
            }
        }

        // Set our new position
        SetPosition(vecNewPosition, true, false);
    }
}

void CVehicleEntity::UpdateTargetRotation()
{
	// Do we have a target rotation?
    if(HasTargetRotation())
    {
        // Get our current rotation
        CVector3 vecCurrentRotation;
        GetRotation(vecCurrentRotation);

        // Get the factor of time spent from the interpolation start
        // to the current time.
        unsigned long ulCurrentTime = SharedUtility::GetTime();
        float fAlpha = Math::Unlerp(m_interp.rot.ulStartTime, ulCurrentTime, m_interp.rot.ulFinishTime);

        // Don't let it to overcompensate the error
        fAlpha = Math::Clamp(0.0f, fAlpha, 1.0f);

        // Get the current error portion to compensate
        float fCurrentAlpha = (fAlpha - m_interp.rot.fLastAlpha);
        m_interp.rot.fLastAlpha = fAlpha;

        // Compensate the error
        CVector3 vecCompensation = Math::Lerp(CVector3(), fCurrentAlpha, m_interp.rot.vecError);

        // If we finished compensating the error, finish it for the next pulse
        if(fAlpha == 1.0f)
            m_interp.rot.ulFinishTime = 0;

        // Set the new rotation
        SetRotation((vecCurrentRotation + vecCompensation), false);
    }
}

void CVehicleEntity::Interpolate()
{
	// Do we have a driver?
	if(GetDriver())
	{
		// Update our target position
		UpdateTargetPosition();

		// Update our target rotation
		UpdateTargetRotation();

		// Update our interior
		UpdateInterior(true);
	}
	else
	{
		// Update our interior
		UpdateInterior(false);

		// Remove our target position
		RemoveTargetPosition();

		// Remove our target rotation
		RemoveTargetRotation();
	}
}

void CVehicleEntity::SetTargetPosition(const CVector3& vecPosition, unsigned long ulDelay)
{
    // Are we spawned?
    if(IsSpawned())
    {
        // Update our target position
        UpdateTargetPosition();

        // Get the current time
        unsigned long ulTime = SharedUtility::GetTime();

        // Get our local position
        CVector3 vecLocalPosition;
        GetPosition(vecLocalPosition);

        // Set the target position
        m_interp.pos.vecTarget = vecPosition;

        // Calculate the relative error
        m_interp.pos.vecError = (vecPosition - vecLocalPosition);

        // Apply the error over 400ms (i.e. 1/4 per 100ms)
        m_interp.pos.vecError *= Math::Lerp<const float>(0.25f, Math::UnlerpClamped(100, ulDelay, 400), 1.0f);

        // Get the interpolation interval
        m_interp.pos.ulStartTime = ulTime;
        m_interp.pos.ulFinishTime = (ulTime + ulDelay);

        // Initialize the interpolation
        m_interp.pos.fLastAlpha = 0.0f;
    }

    // Set our position straight
    m_vecPosition = vecPosition;
}

void CVehicleEntity::SetTargetRotation(const CVector3& vecRotation, unsigned long ulDelay)
{
    // Are we spawned?
    if(IsSpawned())
	{
        // Update our target rotation
        UpdateTargetRotation();

        // Get the current time
        unsigned long ulTime = SharedUtility::GetTime();

        // Get our local rotation
        CVector3 vecLocalRotation;
        GetRotation(vecLocalRotation);

        // Set the target rotation
        m_interp.rot.vecTarget = vecRotation;

        // Get the error
        m_interp.rot.vecError = Math::GetOffsetDegrees(vecLocalRotation, vecRotation);

        // Get the interpolation interval
        m_interp.rot.ulStartTime = ulTime;
        m_interp.rot.ulFinishTime = (ulTime + ulDelay);

        // Initialize the interpolation
        m_interp.rot.fLastAlpha = 0.0f;
    }

    // Set our rotation straight
    m_vecRotation = vecRotation;
}

void CVehicleEntity::RemoveTargetPosition()
{
    m_interp.pos.ulFinishTime = 0;
}

void CVehicleEntity::RemoveTargetRotation()
{
    m_interp.rot.ulFinishTime = 0;
}

void CVehicleEntity::ResetInterpolation()
{
    if(HasTargetPosition())
        SetPosition(m_interp.pos.vecTarget, true);

    if(HasTargetRotation())
        SetRotation(m_interp.rot.vecTarget);

    RemoveTargetPosition();
    RemoveTargetRotation();
}

void CVehicleEntity::UpdateInterior(bool bHasDriver)
{
}

void CVehicleEntity::SetInterior(unsigned int uiInterior)
{

}

unsigned CVehicleEntity::GetInterior()
{
	return 0;
}

void CVehicleEntity::SetIndicatorState(bool bFrontLeft, bool bFrontRight, bool bBackLeft, bool bBackRight)
{
    m_bIndicatorState[0] = bFrontLeft;
    m_bIndicatorState[1] = bFrontRight;
    m_bIndicatorState[2] = bBackLeft;
    m_bIndicatorState[3] = bBackRight;
        
    if(m_pVehicle)
    {
        IVVehicle* pVehicle = m_pVehicle->GetVehicle();
        if(pVehicle)
        {
            pVehicle->indicators[0] = !bFrontLeft;
            pVehicle->indicators[1] = !bFrontRight;
            pVehicle->indicators[2] = !bBackLeft;
            pVehicle->indicators[3] = !bBackRight;
        }
	}
}

bool CVehicleEntity::GetIndicatorState(unsigned char ucSlot)
{
    if(ucSlot >= 0 && ucSlot <= 3)
    {
        return m_bIndicatorState[ucSlot];
    }

    return false;
}

void CVehicleEntity::SetComponentState(unsigned char ucSlot, bool bComponent)
{
    if(ucSlot <= 8)
    {
        m_bComponents[ucSlot] = bComponent;

        // Are we spawned?
        if(IsSpawned())
            m_pVehicle->SetComponentState((ucSlot + 1), bComponent);
    }
}

bool CVehicleEntity::GetComponentState(unsigned char ucSlot)
{
    if(ucSlot <= 8)
        return m_bComponents[ucSlot];

    return false;
}

void CVehicleEntity::SetVariation(unsigned char ucVariation)
{
    // Are we spawned?
    if(IsSpawned())
    {
        if(m_pVehicle->GetTextureVariationCount() != 255)
        {
            //m_pVehicle->SetTextureVariation(ucVariation);
            CIVScript::SetCarLivery(GetScriptingHandle(), (int)ucVariation);
            m_ucVariation = ucVariation;
		}
        else
            m_ucVariation = 0;
    }
    else
        m_ucVariation = ucVariation;
}

unsigned char CVehicleEntity::GetVariation()
{
    // Are we spawned?
    if(IsSpawned())
	{
        if(m_pVehicle->GetTextureVariationCount() != 255)
        {
            //return (unsigned char)m_pVehicle->GetTextureVariation();
            int iVariation = 0;
            CIVScript::GetCarLivery(GetScriptingHandle(), &iVariation);
            return iVariation;
        }
        else
            return 0;
    }
    else
        return m_ucVariation;
}

bool CVehicleEntity::IsOnScreen()
{
    // Are we spawned?
    if(IsSpawned())
    {
        CVector3 vecPos;
        m_pVehicle->GetPosition(vecPos);
        return g_pCore->GetGame()->GetCamera()->IsOnScreen(vecPos);
    }

    return false;
}

void CVehicleEntity::SetTaxiLightsState(bool bState)
{
    // Are we spawned?
    if(IsSpawned())
        CIVScript::SetTaxiLights(GetScriptingHandle(),bState);

    m_bTaxiLights = bState;
}

bool CVehicleEntity::GetTaxiLightsState()
{
    // Are we spawned?
    if(IsSpawned())
        return m_bTaxiLights;

    return false;
}

void CVehicleEntity::SetCarDoorAngle(int iDoor,bool bClose, float fAngle)
{
    // Are we spawned?
    if(IsSpawned())
    {
        if(fAngle > 1.9f && fAngle < 350.0f)
                CIVScript::ControlCarDoor(GetScriptingHandle(),(CIVScript::eVehicleDoor)iDoor,bClose,fAngle);
        else if(fAngle >= 350.0f)
                CIVScript::OpenCarDoor(GetScriptingHandle(),(CIVScript::eVehicleDoor)iDoor);
        else if(fAngle < 2.0f)
                CIVScript::ShutCarDoor(GetScriptingHandle(),(CIVScript::eVehicleDoor)iDoor);
    }

    // Apply changes
    m_fDoor[iDoor] = fAngle;
}

float CVehicleEntity::GetCarDoorAngle(int iDoor)
{
    // Are we spawned?
    if(IsSpawned())
        return m_fDoor[iDoor];

    return 0.0f;
}

void CVehicleEntity::SetLightsState(bool bLights)
{
    // Are we spawned?
    if(IsSpawned())
    {
        if(bLights)
                CIVScript::ForceCarLights(GetScriptingHandle(),2);
        else if(!bLights)
                CIVScript::ForceCarLights(GetScriptingHandle(),1);

        m_bLights = bLights;
    }
}

bool CVehicleEntity::GetLightsState()
{
	return false;
}

bool CVehicleEntity::GetWindowState(int iWindow)
{
	return false;
}

void CVehicleEntity::SetWindowState(int iWindow, bool bBroken)
{
}

void CVehicleEntity::SetDamageable(bool bToggle)
{

}

void CVehicleEntity::SetSteeringAngle(float fSteeringAngle)
{
    // Are we spawned?
    if(IsSpawned())
        m_pVehicle->SetSteeringAngle(fSteeringAngle);
}

float CVehicleEntity::GetSteeringAngle()
{
    // Are we spawned?
    if(IsSpawned())
        m_pVehicle->GetSteeringAngle();

    return 0.0f;
}

void CVehicleEntity::SetEngineState(bool bState)
{
    // Are we spawned?
    if(IsSpawned()) {
        m_pVehicle->SetEngineStatus(bState, 1);
        m_bEngineStatus = bState;
    }
	else
		 m_bEngineStatus = bState;
}

bool CVehicleEntity::GetEngineState()
{
    // Are we spawned?
    if(IsSpawned())
        return m_bEngineStatus;

    return false;
}

CVector3 CVehicleEntity::GetDeformation(CVector3 vecPosition)
{
	return CVector3(0.0f, 0.0f, 0.0f);
}

void CVehicleEntity::SetVehicleGPSState(bool bState)
{
    if(IsSpawned())
		m_pVehicle->SetGPSState(bState);
}

bool CVehicleEntity::GetVehicleGPSState()
{
	return false;
}

void CVehicleEntity::Fix()
{

}

void CVehicleEntity::SetOccupant(BYTE byteSeatId, CPlayerEntity * pOccupant)
{
	if(byteSeatId == 0)
		SetDriver(pOccupant);
	//else
		//SetPassenger((byteSeatId - 1), pOccupant);
}

CPlayerEntity * CVehicleEntity::GetOccupant(BYTE byteSeatId)
{
	if(byteSeatId == 0)
		return GetDriver();

	return new CPlayerEntity(); //GetPassenger(byteSeatId - 1);
}