//----------------------------------------------------------------------------
// Copyright 2020, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#ifndef HANDLE_MANAGER_H
#define HANDLE_MANAGER_H

#include "Handle.h"
#include <mutex>
#include <atomic>

class HandleManager
{
private:

	// constants
	static const unsigned int HANDLE_TABLE_SIZE = 12000;
	static const unsigned int HANDLE_INVALID_STATE = 0x0;
	static const unsigned int HANDLE_STARTING_ID = 0xAAAA0000;

	// Nested class
	class HandleTableEntry
	{
	public:
		HandleTableEntry() = default;
		HandleTableEntry(const HandleTableEntry&) = delete;
		HandleTableEntry& operator = (const HandleTableEntry&) = delete;
		~HandleTableEntry() = default;

	public:
		std::atomic<unsigned int> id;
		std::mutex				  mtx;
	};

public:
	HandleManager();
	~HandleManager();

	//-----------------------------------------------------
	// You cannot copy the singleton
	//-----------------------------------------------------
	HandleManager(const HandleManager&) = delete;
	const HandleManager& operator = (const HandleManager&) = delete;

	//-----------------------------------------------------
	// Being strategic on what is expose or not
	//-----------------------------------------------------
	static Handle::Status ActivateHandle(Handle::ID& id, Handle::Index& index);

	static Handle::Status InvalidateHandle(Handle& handle);
	static Handle::Status ValidateHandle(const Handle& handle);

	static Handle::Status AquireResource(const Handle& handle);
	static Handle::Status ReleaseResource(const Handle& handle);

	//-----------------------------------------------------
	// Only for our DEBUG - remove for application
	//-----------------------------------------------------
	static void PrintTable();

private:
	//-----------------------------------------------------
	// Keeping internals... private
	//-----------------------------------------------------
	static HandleManager* privInstance();

	// methods on an instance of the HandleMan
	Handle::ID privGetNewID();
	bool privFindNextAvailable(Handle::Index& index);
	Handle::Status privIsHandleValid(const Handle& handle);
	Handle::Status privIsHandleAndRangeValid(const Handle& handle);

	//-----------------------------------------------------
	// Raw data
	//-----------------------------------------------------
	HandleTableEntry	table[HANDLE_TABLE_SIZE];
	Handle::ID			srcID;
};

#endif

// ---  End of File ---------------
