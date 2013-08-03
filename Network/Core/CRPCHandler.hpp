//================ IV:Multiplayer - https://github.com/XForce/ivmultiplayer ================
//
// File: CRPCHandler.hpp
// Project: Network.Core
// Author: CrackHD
// License: See LICENSE in root directory
//
//==============================================================================

#ifndef CRPCHandler_hpp
#define CRPCHandler_hpp

#include "NetCommon.h"
#include <list>

typedef void (* RPCFunction_t)(CBitStream * pBitStream, CNetPlayerSocket * pSenderSocket);

// Structure used for rpc functions
struct RPCFunction
{
	eRPCIdentifier rpcId;
	RPCFunction_t rpcFunction;
};

class CRPCHandler
{
private:
	std::list<RPCFunction *> m_rpcFunctionList;

public:
	~CRPCHandler()
	{
		// Remove any iters in list

		for(std::list<RPCFunction *>::iterator i = m_rpcFunctionList.begin(); i != m_rpcFunctionList.end(); i++)
			delete (*i);
	}

	bool AddFunction(RPCIdentifier rpcId, RPCFunction_t rpcFunction)
	{
		// Make sure it isn't already added
		RPCFunction * pFunction = GetFunctionFromIdentifier(rpcId);

		// We do not allow several functions per rpc
		if(pFunction)
			return false;

		// Create the rpc function
		pFunction = new RPCFunction;
		pFunction->rpcId = rpcId;
		pFunction->rpcFunction = rpcFunction;
	
		// Add it to the rpc function list
		m_rpcFunctionList.push_back(pFunction);
		return true;
	}

	// Remove function
	void RemoveFunction(RPCIdentifier rpcId)
	{
		// Get the function
		RPCFunction * pFunction = GetFunctionFromIdentifier(rpcId);

		// Remove it from the rpc function list
		while(pFunction)
		{
			m_rpcFunctionList.remove(pFunction);
			delete pFunction;

			pFunction = GetFunctionFromIdentifier(rpcId);
		}
	}

	// Get function pointer from specified RPC
	RPCFunction * GetFunctionFromIdentifier(RPCIdentifier rpcId)
	{
		// Iterate through all rpc functions
		std::list<RPCFunction *>::iterator iter;
		for(iter = m_rpcFunctionList.begin(); iter != m_rpcFunctionList.end(); iter++)
		{
			// Is this the function we're after?
			if((*iter)->rpcId == rpcId)
				return (*iter);
		}

		// Function not found
		return NULL;
	}

	// Handle packet with this RPC handler
	bool HandlePacket(NetPacket * pPacket)
	{
		// Is it an rpc packet?
		if(pPacket->id == PACKET_RPC)
		{
			// Construct the bit stream
			CBitStream bitStream(pPacket->data, pPacket->dataSize, false);
			RPCIdentifier rpcId;

			// Read the rpc id
			if(bitStream.Read(rpcId))
			{
				RPCFunction * pFunction = GetFunctionFromIdentifier(rpcId);

				// Does the function exist?
				if(pFunction)
				{
					// Call the function
					pFunction->rpcFunction(&bitStream, pPacket->pPlayerSocket);
					return true;
				}
			}
		}

		// Not handled
		return false;
	}
};


#endif // CRPCHandler_hpp
