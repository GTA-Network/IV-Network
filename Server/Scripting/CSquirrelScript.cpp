//========== IV:Multiplayer - https://github.com/IVMultiplayer/IVMultiplayer ==========
//
// File: CSquirrelScript.cpp
// Project: Client.Core
// Author: xForce <xf0rc3.11@gmail.com>
// License: See LICENSE in root directory
//
//==============================================================================

#include "CSquirrelScript.h"
#include <assert.h>
#include <Squirrel/sqstdio.h>
#include <Squirrel/sqstdaux.h>
#include <Squirrel/sqstdblob.h>
#include <Squirrel/sqstdio.h>
#include <Squirrel/sqstdsystem.h>
#include <Squirrel/sqstdmath.h>
#include <Squirrel/sqstdstring.h>
#include <Squirrel/sqstate.h>

CSquirrelScript::CSquirrelScript()
	: CScript()
{
	
}

CSquirrelScript::~CSquirrelScript()
{

}


bool CSquirrelScript::Load(CString strName, CString strPath)
{
	m_pVM = sq_open(1024);

	// Register the default error handlers
	sqstd_seterrorhandlers(m_pVM);

	sq_seterrorhandler(m_pVM);

	// Push the root table onto the stack
	sq_pushroottable(m_pVM);

	// Register the blob library
	sqstd_register_bloblib(m_pVM);

	// Register the math library
	sqstd_register_mathlib(m_pVM);

	// Register the string library
	sqstd_register_stringlib(m_pVM);

	return true;
}

void CSquirrelScript::Unload()
{
	// Pop the root table from the stack
	sq_pop(m_pVM, 1);

	// Close the squirrel VM
	sq_close(m_pVM);

	m_pVM = NULL;
}

bool CSquirrelScript::Execute()
{	
	// Add the script name constant
	RegisterConstant("SCRIPT_NAME", GetName());

	// Add the script path constant
	RegisterConstant("SCRIPT_PATH", GetName());

	// Load and compile the script
	if(SQ_FAILED(sqstd_dofile(m_pVM, GetName().Get(), SQFalse, SQTrue)))
		return false;

	return true;
}



void CSquirrelScript::RegisterConstant(CString strConstantName, CSquirrelScriptArgument value)
{
	// Push the constant name onto the stack
	sq_pushstring(m_pVM, strConstantName.Get(), -1);

	// Push the constant value onto the stack
	value.push(m_pVM);

	// Create a new slot
	sq_createslot(m_pVM, -3);
}