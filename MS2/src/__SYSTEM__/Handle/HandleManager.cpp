//----------------------------------------------------------------------------
// Copyright 2020, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#include "HandleManager.h"

// --------------------------------------------------------------------
//   No Mutex protection
// --------------------------------------------------------------------

HandleManager::HandleManager()
{
	this->srcID = HANDLE_STARTING_ID;

	for (int i = 0; i < HANDLE_TABLE_SIZE; i++)
	{
		this->table[i].id.store(HANDLE_INVALID_STATE);
	}
}

HandleManager::~HandleManager()
{
	// safety - nuke it again
	this->srcID = HANDLE_STARTING_ID;

	for (int i = 0; i < HANDLE_TABLE_SIZE; i++)
	{
		this->table[i].id.store(HANDLE_INVALID_STATE);
	}
}

Handle::ID HandleManager::privGetNewID()
{
	// Increment
	this->srcID++;

	return this->srcID;
}

// --------------------------------------------------------------------
//   Mutex protection
// --------------------------------------------------------------------

Handle::Status HandleManager::InvalidateHandle(Handle& handle)
{
	HandleManager* pMan = HandleManager::privInstance();
	assert(pMan);

	// Is Range and ID valid?
	Handle::Status status = pMan->privIsHandleAndRangeValid(handle);

	if (status == Handle::Status::SUCCESS)
	{
		// Protect access to resource: acquire
		bool lockStatus = pMan->table[handle.GetIndex()].mtx.try_lock();

		// ---------------------------------------------------------------------
		// Race condition:
		// What happens if the ID is invalidated between the test and the lock?
		// ---------------------------------------------------------------------

		if (lockStatus)
		{
			// Is ID valid?
			status = pMan->privIsHandleValid(handle);

			if (status == Handle::Status::SUCCESS)
			{
				// nuke it
				pMan->table[handle.GetIndex()].id.store(HANDLE_INVALID_STATE);

				// release the mtx
				pMan->table[handle.GetIndex()].mtx.unlock();
			}
			else
			{
				// race condition... handle is invalid - status is ERROR

				// release the mtx
				pMan->table[handle.GetIndex()].mtx.unlock();
			}
		}
		else
		{
			// Do nothing since mtx was never aquired
			// Fall through - error
			status = Handle::Status::HANDLE_ERROR;
		}
	}
	else
	{
		// fall through - status is error
	}

	return status;
}

Handle::Status HandleManager::ValidateHandle(const Handle& handle)
{
	HandleManager* pMan = HandleManager::privInstance();
	assert(pMan);

	// is it valid?
	Handle::Status status = pMan->privIsHandleAndRangeValid(handle);

	// Trap for Debug - (leave next line uncommented)
	assert(status == Handle::Status::SUCCESS);


	return status;
}

Handle::Status HandleManager::AquireResource(const Handle& handle)
{
	HandleManager* pMan = HandleManager::privInstance();
	assert(pMan);

	// Is Range and ID valid?
	Handle::Status status = pMan->privIsHandleAndRangeValid(handle);

	if (status == Handle::Status::SUCCESS)
	{
		// Protect access to resource: acquire
		bool lockStatus = pMan->table[handle.GetIndex()].mtx.try_lock();

		// ---------------------------------------------------------------------
		// Race condition:
		// What happens if the ID is invalidated between the test and the lock?
		// ---------------------------------------------------------------------

		if (lockStatus)
		{
			// Is ID valid?
			status = pMan->privIsHandleValid(handle);

			if (status == Handle::Status::SUCCESS)
			{
				// OK - Our mtx lock grab was Good
				//      leave the method
			}
			else
			{
				// race condition... handle is invalid - status is error
				// release the mtx
				pMan->table[handle.GetIndex()].mtx.unlock();
			}
		}
		else
		{
			// Do nothing since mtx was never aquired
			// fall through - error

			status = Handle::Status::HANDLE_ERROR;
		}
	}
	else
	{
		// fall through - status is error
	}

	return status;
}

Handle::Status HandleManager::ReleaseResource(const Handle& handle)
{
	HandleManager* pMan = HandleManager::privInstance();
	assert(pMan);

	// Is Range and ID valid?
	Handle::Status status = pMan->privIsHandleAndRangeValid(handle);

	if (status == Handle::Status::SUCCESS)
	{
		// Protect access to resource: release
		pMan->table[handle.GetIndex()].mtx.unlock();
	}
	else
	{
		// fall through - status is error
	}

	return status;
}

Handle::Status HandleManager::ActivateHandle(Handle::ID& new_id, Handle::Index& index)
{
	HandleManager* pMan = HandleManager::privInstance();
	assert(pMan);

	Handle::Status 	status = Handle::Status::HANDLE_ERROR;

	if (pMan->privFindNextAvailable(index))
	{
		// Protect access to resource: acquire
		bool lockStatus = pMan->table[index].mtx.try_lock();

		// ---------------------------------------------------------------------
		// Race condition:
		// What happens if the ID is invalidated between the test and the lock?
		// ---------------------------------------------------------------------
		if (pMan->table[index].id.load() != HANDLE_INVALID_STATE)
		{
			if (lockStatus)
			{
				// unlock
				pMan->table[index].mtx.unlock();
				lockStatus = false;
				// bail and fall through
			}
		}

		if (lockStatus)
		{
			status = Handle::Status::SUCCESS;

			// Set it - atomic!
			new_id = pMan->privGetNewID();
			pMan->table[index].id.store(new_id);

			// unlock
			pMan->table[index].mtx.unlock();
		}
		else
		{
			// Do nothing since mtx was never aquired
			// fall through - error

			status = Handle::Status::HANDLE_ERROR;
		}
	}
	else
	{
		status = Handle::Status::INSUFFIENT_SPACE;

		// trap for Debug
		assert(status == Handle::Status::SUCCESS);
	}

	return status;
}

// --------------------------------------------------------------------
//   No Mutex protection
// --------------------------------------------------------------------

bool HandleManager::privFindNextAvailable(Handle::Index& index)
{
	bool status = false;

	for (Handle::Index i = 0; i < HANDLE_TABLE_SIZE; i++)
	{
		if (this->table[i].id.load() == HANDLE_INVALID_STATE)
		{
			// found one
			index = i;
			status = true;
			break;
		}
	}

	return status;
}

Handle::Status HandleManager::privIsHandleValid(const Handle& handle)
{
	Handle::Status status = Handle::Status::HANDLE_ERROR;

	if (this->table[handle.GetIndex()].id.load() == handle.GetID())
	{
		status = Handle::Status::SUCCESS;
	}
	else
	{
		status = Handle::Status::HANDLE_ERROR;
	}

	return status;
}

Handle::Status HandleManager::privIsHandleAndRangeValid(const Handle& handle)
{
	Handle::Status status = Handle::Status::HANDLE_ERROR;

	if (handle.GetIndex() >= 0 && handle.GetIndex() < HANDLE_TABLE_SIZE)
	{
		if (this->table[handle.GetIndex()].id.load() == handle.GetID())
		{
			status = Handle::Status::SUCCESS;
		}
		else
		{
			status = Handle::Status::HANDLE_ERROR;
		}
	}
	else
	{
		status = Handle::Status::HANDLE_ERROR;
	}

	return status;
}

HandleManager* HandleManager::privInstance()
{
	// Here's the singleton
	static HandleManager instance;

	return &instance;
}

void HandleManager::PrintTable()
{
	HandleManager* pMan = HandleManager::privInstance();
	assert(pMan);

	Trace::out("\n");

	// No protection.... Just printing

	for (int i = 0; i < HANDLE_TABLE_SIZE; i++)
	{
		Trace::out("[%d]: %x \n", i, pMan->table[i].id.load());
	}

}

// ---  End of File ---------------
