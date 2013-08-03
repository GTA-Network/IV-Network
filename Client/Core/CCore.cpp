//================ IV:Multiplayer - https://github.com/XForce/ivmultiplayer ================
//
// File: CCore.cpp
// Project: Client.Core
// Author: FRi<FRi.developing@gmail.com>
// License: See LICENSE in root directory
//
//==========================================================================================

#include	"CCore.h"
#include	<Windows.h>

extern	CCore			* pCore;
bool					bDeviceLost = false;

DWORD WINAPI WaitForGame(LPVOID lpParam)
{
	return 1;
}

CCore::CCore(void)
{
	// Mark as not initialised
	m_bInitialised = false;

	// Mark the game as not loaded
	SetGameLoaded(false);

	// Reset instances
	m_pGame = NULL;
	m_pOffsets = NULL;
}

CCore::~CCore()
{
	//CLogFile::Printf( "CCore::~CCore" );
}

bool CCore::Initialise()
{
	// Are we already initialsed?
	if(m_bInitialised)
		return false;

	// Get the applicatin base address
	m_uiBaseAddress = (unsigned int)GetModuleHandle(NULL);

	// Subtract the image size from the base address
	m_uiBaseAddress -= 0x400000;

	// Create the game instance
	m_pGame = new CGame;

	// Create the offsets instance
	m_pOffsets = new COffsets;

	// Check if we have our offset instance
	if(m_pOffsets)
		m_pOffsets->Initialize(m_uiBaseAddress);

	//CLogFile::Printf("Done!");
	return true;
}

void CCore::OnGameLoad()
{
	// Is the game already loaded?
	if(IsGameLoaded())
		return;

	// Mark the game as loaded
	SetGameLoaded(true);
}

void CCore::OnGamePreLoad()
{
	// Is the game loaded?
	if(IsGameLoaded())
		return;

	// Create a thread to wait for the game
	CreateThread(0, 0, WaitForGame, 0, 0, 0); // Remove thread ? 
}

void CCore::OnDeviceCreate(IDirect3DDevice9 * pDevice, D3DPRESENT_PARAMETERS * pPresentationParameters)
{
	// Initialise the graphics module

	// Setup the chat

	// Create the gui instance
}

void CCore::OnDeviceLost(IDirect3DDevice9 * pDevice)
{
	// Let the graphics module know the device is lost

	// Release the saved stateblock

	// Mark as lost device
	bDeviceLost = true;
}

void CCore::OnDeviceReset(IDirect3DDevice9 * pDevice)
{
	// Let the graphics module know the device is reset

	// Mark as not lost device
	bDeviceLost = false;
}

void CCore::OnDevicePreRender()
{
	// Is the scripting manager active?
	if(true)
	{
		// Call the script event
		
	}
}

void CCore::OnDeviceRender()
{
	// Has the device been lost?
	if(bDeviceLost)
		return;

	// Render 
}

void CCore::OnGameProcess()
{
	// Is the network module instance valid?
	if(true)
	{
		// Pulse the network
	}

	// Is the timer manager instance valid?
	if(true)
	{
		// Pulse the timer manager
	}

	// Is the file transfer instance valid?
	if(true)
	{
		// Pulse the file transfer
	}


	// Is the scripting manager active?
	if(true)
	{
		// Call the script event
	}
}