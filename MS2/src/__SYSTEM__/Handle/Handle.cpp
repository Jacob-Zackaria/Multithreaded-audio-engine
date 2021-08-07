//----------------------------------------------------------------------------
// Copyright 2020, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#include "HandleManager.h"
#include "Handle.h"

// --------------------------------------------------
// Handle
// --------------------------------------------------

Handle::Handle()
{
	//Activate
	const Status status = HandleManager::ActivateHandle(this->id, this->index);
	assert(status == Status::SUCCESS);
}

Handle::~Handle()
{
	// Invalidate handle;
	HandleManager::InvalidateHandle(*this);
}

Handle::ID Handle::GetID() const
{
	return this->id;
}

Handle::Index Handle::GetIndex() const
{
	return this->index;
}

//---------------------------------------------------------------
// Tunneling... I only want handle.h to be used
//---------------------------------------------------------------
Handle::Status Handle::ValidateHandle(const Handle& handle)
{
	return HandleManager::ValidateHandle(handle);
}

Handle::Status Handle::InvalidateHandle(Handle& handle)
{
	return HandleManager::InvalidateHandle(handle);
}

Handle::Status Handle::AquireResource(const Handle& handle)
{
	return HandleManager::AquireResource(handle);
}

Handle::Status Handle::ReleaseResource(const Handle& handle)
{
	return HandleManager::ReleaseResource(handle);
}


// ---  End of File ---------------
