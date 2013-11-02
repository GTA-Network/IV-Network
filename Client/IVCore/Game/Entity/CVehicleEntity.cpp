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
#include <Game/IVEngine/CIVVehicleFactory.h>
#include <Game/Entity/CVehicleEntity.h>
#include <IV/CIVScript.h>
#include <Game/CCharacterManager.h>

#include <CCore.h>
extern CCore * g_pCore;

CVehicleEntity::CVehicleEntity(int iVehicleModel, CVector3 vecPos, float fAngle, DWORD color1, DWORD color2, DWORD color3, DWORD color4, DWORD color5) :
	CNetworkEntity()
{
	m_pVehicle = NULL;
	m_vehicleId = INVALID_ENTITY_ID;
	m_pDriver = NULL;
	m_bSpawned = false;
	m_pModelInfo = NULL;

	CNetworkEntity::SetType(VEHICLE_ENTITY);

	if (iVehicleModel == 124 || iVehicleModel == 125 || iVehicleModel == 126)
	{
		g_pCore->GetChat()->Print(CString("!!! This vehicle is disabled, because makes big FPS drop and invisible (%i) !!!", iVehicleModel).Get());
		return;
	}

	if (iVehicleModel == 157 || iVehicleModel == 158 || iVehicleModel == 159)
	{
		g_pCore->GetChat()->Print(CString("!!! This vehicle is disabled, because makes crash we will fix it (%i) (disabled boat in TBoGT) !!!", iVehicleModel).Get());
		return;
	}

	// Get the model hash from the model id
	DWORD dwModelHash = CIVModelManager::VehicleIdToModelHash(iVehicleModel);

	// Get the model index
	int iVehicleModelIndex = CIVModelManager::GetModelIndexFromHash(dwModelHash);

	if (iVehicleModelIndex == -1)
	{
		g_pCore->GetChat()->Print(CString("!!! 0x%X ModelHash has no model index !!!", dwModelHash).Get());
		return;
	}

	// Set the model info
	m_pModelInfo = g_pCore->GetGame()->GetModelInfo(iVehicleModelIndex);

	// Set the color
	m_dwColor[0] = color1;
	m_dwColor[1] = color2;
	m_dwColor[2] = color3;
	m_dwColor[3] = color4;
	m_dwColor[4] = color5;

	// Set the interpolate variables
	m_interp.pos.ulFinishTime = 0;
	m_interp.rot.ulFinishTime = 0;

	// Set the rotation
	m_fSpawnAngle = fAngle;

	// Set the spawn position
	memcpy(&m_vecSpawnPosition,&vecPos,sizeof(CVector3));

}

CVehicleEntity::~CVehicleEntity()
{
	// Is the vehicle spawned?
	if(IsSpawned())
	{
		// Destroy the vehicle
		Destroy();
	}
}

#define CVehicleModelInfo__AddReference ((int(__thiscall *)(IVBaseModelInfo *))(g_pCore->GetBase() + 0x83F2E0))
#define CWorld__GetGroundZ ((float (__cdecl*)(float, float))(g_pCore->GetBase() + 0x9C69F0))
#define CWorld__AddEntity ((int(_cdecl *)(IVVehicle*, bool bDontAdd))(g_pCore->GetBase() + 0x86C0B0))
// Seems to be setup audio or something like that
#define CVehicle__TurnEngineOn ((void(__thiscall *)(IVVehicle*, bool))(g_pCore->GetBase() + 0x9FD530))
#define sub_B40B30 ((void(__thiscall *)(IVVehicle*, char, char))(g_pCore->GetBase() + 0xB40B30))
#define pIVVehicleFactory (*(IVVehicleFactory**)(g_pCore->GetBase() + 0x118A6D4))

bool CVehicleEntity::Create()
{
	if (m_pModelInfo == NULL)
		return false;

	// Is the vehicle already spawned?
	if(IsSpawned())
		return false;

	CIVScript::RequestModel(m_pModelInfo->GetHash());

	while (!CIVScript::HasModelLoaded(m_pModelInfo->GetHash()))
		CIVScript::LoadAllObjectsNow(false);

	IVVehicle * pVehicle = pIVVehicleFactory->Create(m_pModelInfo->GetIndex(), 1, 0, 0);
	if (pVehicle)
	{
		pVehicle->Function76(0);
		pVehicle->m_byteFlags1 |= 4u;
		pVehicle->m_dwFlags1 |= 8u; // set fixed wait for collision/

		CWorld__AddEntity(pVehicle, false);
		CVehicleModelInfo__AddReference(m_pModelInfo->GetModelInfo());
		// we dont want to turn on the engine
		// CVehicle__TurnEngineOn(pVehicle, true);
		pVehicle->m_byteFlags10 |= 8u;

		// This maybe cause pool overflow if much vehicles are created and destroyed [NEED TEST]
		// If this cause overflow try to delete the create physics before call or disable the call in VehicleFactory::Create
		// Using this above *(WORD*) (g_pCore->GetBase() + 0x4B48D5) = 0x9090; before call to vehiclefactory [TESTED => crash]
		// Can someone confirm if this cause pool overflow or not
		if (*(DWORD*) pVehicle != COffsets::VAR_CBoat__VFTable) // Otherwise client crash if boat is on ground (not in water)
		{
			pVehicle->CreatePhysics();
			pVehicle->ProcessInput();
		}
		
		CIVScript::MarkModelAsNoLongerNeeded(m_pModelInfo->GetHash());

		m_pVehicle = new CIVVehicle(pVehicle);

		//set the vehicle's color
		SetColors(m_dwColor[0], m_dwColor[1], m_dwColor[2], m_dwColor[3], m_dwColor[4]);

		//fix: no more random components
		for (int i = 0; i < 9; ++i)
			SetComponentState(i, false);

		// Mark as spawned
		m_bSpawned = true;

		// Reset the vehicle
		Reset();

		SetPosition(m_vecSpawnPosition, true);

		CLogFile::Printf("Created vehicle! (Id: %d, Handle: %X)", m_vehicleId, g_pCore->GetGame()->GetPools()->GetVehiclePool()->HandleOf(pVehicle));
		return true;
	}
	else
	{
		CLogFile::Printf("Created vehicle failed!");
		return false;
	}
}

bool CVehicleEntity::Destroy()
{
	// Is the vehicle not spawned?
	if(!IsSpawned())
		return false;

	unsigned int handle = g_pCore->GetGame()->GetPools()->GetVehiclePool()->HandleOf(m_pVehicle->GetVehicle());
	CIVScript::MarkCarAsNoLongerNeeded(&handle);
	pIVVehicleFactory->Delete(m_pVehicle->GetVehicle());

	// Remove the vehicle model reference
	m_pModelInfo->RemoveReference();

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

#pragma pack(push, 1)
class ColorStuff
{
public:
	float red;
	float green;
	float blue;
	DWORD color;
};

class IVVehicleColors
{
public:
	unsigned char pad_0[16];
	ColorStuff field_10;
	ColorStuff field_20;
	ColorStuff field_30;
	ColorStuff field_40;
	ColorStuff field_50;
	ColorStuff field_60;
};

#pragma pack(pop)

#define getRed(color) (float) (((color >> 16) & 0xFF) / 255)
#define getGreen(color) (float) (((color >> 8) & 0xFF) / 255)
#define getBlue(color) (float) ((color & 0xFF) / 255)

void CVehicleEntity::SetColors(DWORD dwColor1, DWORD dwColor2, DWORD dwColor3, DWORD dwColor4, DWORD dwColor5)
{
	if (!GetGameVehicle())
		return;

	IVVehicleColors* VehicleColors = *(IVVehicleColors**) (GetGameVehicle()->GetVehicle()->m_pLivery + 4);

	VehicleColors->field_10.red = getRed(dwColor1);
	VehicleColors->field_10.green = getGreen(dwColor1);
	VehicleColors->field_10.blue = getBlue(dwColor1);
	VehicleColors->field_10.color = dwColor4;

	VehicleColors->field_20.red = getRed(dwColor2);
	VehicleColors->field_20.green = getGreen(dwColor2);
	VehicleColors->field_20.blue = getBlue(dwColor2);
	VehicleColors->field_20.color = dwColor4;

	VehicleColors->field_30.red = getRed(dwColor3);
	VehicleColors->field_30.green = getGreen(dwColor3);
	VehicleColors->field_30.blue = getBlue(dwColor3);
	VehicleColors->field_30.color = dwColor4;

	VehicleColors->field_40.red = getRed(dwColor4);
	VehicleColors->field_40.green = getGreen(dwColor4);
	VehicleColors->field_40.blue = getBlue(dwColor4);
	VehicleColors->field_40.color = dwColor4;

	VehicleColors->field_50.red = getRed(dwColor5);
	VehicleColors->field_50.green = getGreen(dwColor5);
	VehicleColors->field_50.blue = getBlue(dwColor5);
	VehicleColors->field_50.color = dwColor4;

	VehicleColors->field_60.red = getRed(dwColor3);
	VehicleColors->field_60.green = getGreen(dwColor3);
	VehicleColors->field_60.blue = getBlue(dwColor3);
	VehicleColors->field_60.color = dwColor4;
}

void CVehicleEntity::GetColors(DWORD &dwColor1, DWORD &dwColor2, DWORD &dwColor3, DWORD &dwColor4, DWORD &dwColor5)
{
	{
		dwColor1 = m_dwColor[0];
		dwColor2 = m_dwColor[1];
		dwColor3 = m_dwColor[2];
		dwColor4 = m_dwColor[3];
		dwColor5 = m_dwColor[4];
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

void CVehicleEntity::SetHealth(float uiHealth)
	{
	// Are we spawned?
	if(IsSpawned())
		m_pVehicle->SetEngineHealth(uiHealth);

	m_uiHealth = uiHealth;
}

float CVehicleEntity::GetHealth()
{
	// Are we spawned?
	if(IsSpawned())
		return m_pVehicle->GetEngineHealth();

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

void CVehicleEntity::Pulse()
{
	Interpolate();
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
			if (HasTargetPosition())
            {
                SetPosition(m_interp.pos.vecTarget);
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
	if (m_pVehicle)
	{
		IVVehicle* pVehicle = m_pVehicle->GetVehicle();
		if (pVehicle)
		{
			pVehicle->Repair();
		}
	}
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