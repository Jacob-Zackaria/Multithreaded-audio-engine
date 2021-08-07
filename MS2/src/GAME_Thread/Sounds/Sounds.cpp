//----------------------------------------------------------------------------
// Copyright 2020, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#include "CircularData.h"
#include "SoundManager.h"
#include "Sounds.h"
#include "APlaySound.h"
#include "AStopSound.h"
#include "AVolSound.h"
#include "APanSound.h"
#include "APitchSound.h"
#include "AResetSound.h"
#include "APrempt.h"
#include "TimeEventManager.h"

// Static store
SoundPriorityEntry  Sounds::sndPriorityTable[Sounds::SND_PRIORITY_TABLE_SIZE];
Handle	          Sounds::table_handle;

Sounds::Sounds()
	: 
	sndID(SndID::Uninitialized),
	pASnd(nullptr),
	vol(0.7f),
	pan(0.0f),
	pitch(1.0f),
	priority(0),
	handle()
{
}

Handle::Status Sounds::SetID(SndID snd_id)
{
	Handle::Lock lock(this->handle);
	if (lock)
	{
		this->sndID = snd_id;
	}
	return lock;
}

Handle::Status Sounds::GetID(SndID& snd_id)
{
	Handle::Lock lock(this->handle);
	if (lock)
	{
		snd_id = this->sndID;
	}
	return lock;
}

void Sounds::Wash()
{
	// Wash - clear the entire hierarchy
	DLink::ClearLink();

	// Sub class clear
	this->privClear();
}

Handle::Status Sounds::RemoveFromPriorityTable()
{
	Handle::Lock lock(this->handle);
	if (lock)
	{
		bool status = false;

		for (unsigned int i = 0; i < Sounds::SND_PRIORITY_TABLE_SIZE; i++)
		{
			if (Sounds::sndPriorityTable[i].handleID == this->handle.GetID())
			{
				Sounds::sndPriorityTable[i].Clear();
				status = true;
				break;
			}
		}
	}
	else
	{
		assert(false);
	}
	return lock;
}

void Sounds::PrintPriorityTable()
{

	Trace::out("---------------------------------\n");
	Trace::out(" Snd Priority Table \n");
	Trace::out("---------------------------------\n");
	for (unsigned int i = 0; i < Sounds::SND_PRIORITY_TABLE_SIZE; i++)
	{
		if (Sounds::sndPriorityTable[i].priority != -1)
		{
			Time delta = (TimeEventManager::GetTimeCurrent()) - sndPriorityTable[i].startTime;

			Trace::out("handle: 0x%x SndID: %d priority:%4d  time: %d ms\n",
				sndPriorityTable[i].handleID,
				sndPriorityTable[i].sndID,
				sndPriorityTable[i].priority,
				Time::quotient(delta, Time(Duration::TIME_ONE_MILLISECOND)));
		}
		else
		{

			Trace::out("handle: 0x-------- SndID: --- priority: ---  time: --- \n");
		}
	}

	Trace::out("---------------------------------\n");
}

Handle::Status Sounds::Set(SndID snd_id, SoundPriority snd_priority)
{
	Handle::Lock lock(this->handle);
	if (lock)
	{
		this->sndID = snd_id;
		this->priority = snd_priority;
	}
	return lock;
}

void Sounds::privClear()
{
	this->sndID = SndID::Uninitialized;

}

void Sounds::Dump()
{
	SndID _id;
	this->GetID(_id);
	// Dump - Print contents to the debug output window
	Trace::out("   Name: %d (%p) \n", _id, this);
	Trace::out("   SndName: SndID:%d (%p) priority:%d vol:%f pan:%f pitch:%f\n", _id, this, this->priority, this->vol, this->pan, this->pitch);
}

Sounds::~Sounds()
{
	// Kill the Handle
	// Gets automagically killed by the ~Handle()

	// check "this" and input
	assert(Handle::ValidateHandle(this->handle) == Handle::Status::SUCCESS);
}


void Sounds::SetASound(ASounds* p)
{
	// OK to set it to nullptr in a end of sound
	this->pASnd = p;
}

void Sounds::GetASound(ASounds*& p)
{
	p = this->pASnd;	
}

Handle::Status Sounds::Play()
{
	Handle::Lock lock(this->handle);

	if (lock)
	{
		Handle::Lock tableLock(this->table_handle);
		if (tableLock)
		{
			if (this->privUseSlotInTable())
			{
				// Easy take a slot

				// Place the Play command in the queue to the Audio thread
				CircularData* pOut = SoundManager::GetG2A();
				assert(pOut);

				Command* pCmd = new APlaySound(this->sndID, this);
				assert(pCmd);

				pOut->PushBack(pCmd);
			}
			else
			{
				this->CheckPriority();
			}
		}
		else
		{
			assert(false);
		}
	}
	else
	{
		assert(false);
	}
	return lock;
}

void Sounds::CheckPriority()
{
	int maxNumber = this->priority;
	int index = -1;
	Time newTime;
	Time delta;
	for (unsigned int i = 0; i < Sounds::SND_PRIORITY_TABLE_SIZE; i++)
	{
		// find max priority in table
		if (sndPriorityTable[i].priority > maxNumber)
		{
			maxNumber = sndPriorityTable[i].priority;
			delta = (TimeEventManager::GetTimeCurrent()) - sndPriorityTable[i].startTime;
			newTime = delta;
			index = i;
		}	//if priority is equal compare time played and get oldest.
		else if (sndPriorityTable[i].priority == maxNumber)
		{
			delta = (TimeEventManager::GetTimeCurrent()) - sndPriorityTable[i].startTime;
			if (delta > newTime)
			{
				newTime = delta;
				index = i;
			}
		}
	}

	// Prempt the sound based on index.
	if (index != -1) 
	{
		Sounds* pSound = SoundManager::FindWithHandle(sndPriorityTable[index].handleID);
		assert(pSound != nullptr);
		// Place the Play command in the queue to the Audio thread
		CircularData* pOut = SoundManager::GetG2A();
		assert(pOut);

		Command* pCmd = new APrempt(this->sndID, this, pSound);
		assert(pCmd);

		pOut->PushBack(pCmd);
	}
	else
	{
		// Place the Play command in the queue to the Audio thread
		CircularData* pOut = SoundManager::GetG2A();
		assert(pOut);

		Command* pCmd = new AStopSound(this->sndID, this);
		assert(pCmd);

		pOut->PushBack(pCmd);

		// Print snd priority table
		Sounds::PrintPriorityTable();
	}
}

void Sounds::StopPendingSounds()
{
	for (unsigned int i = 0; i < Sounds::SND_PRIORITY_TABLE_SIZE; i++)
	{
		if (sndPriorityTable[i].priority != -1)
		{
			Sounds* pSound = SoundManager::FindWithHandle(sndPriorityTable[i].handleID);
			assert(pSound != nullptr);

			// Place the Play command in the queue to the Audio thread
			CircularData* pOut = SoundManager::GetG2A();
			assert(pOut);

			Command* pCmd = new AStopSound(pSound->sndID, pSound);
			assert(pCmd);

			pOut->PushBack(pCmd);
		}
	}
}

bool Sounds::privUseSlotInTable()
{
	bool status = false;

	// SLOPPY - HACK 

	// Find open slot?
	for (unsigned int i = 0; i < Sounds::SND_PRIORITY_TABLE_SIZE; i++)
	{
		if (sndPriorityTable[i].priority == -1)
		{
			sndPriorityTable[i].priority = this->priority;
			sndPriorityTable[i].sndID = this->sndID;
			sndPriorityTable[i].handleID = this->handle.GetID();
			sndPriorityTable[i].startTime = TimeEventManager::GetTimeCurrent();

			// Found one
			status = true;
			break;
		}
	}

	return status;
}

Handle::Status Sounds::Stop()
{
	Handle::Lock lock(this->handle);

	if (lock)
	{
		// Send a play command to the Audio thread
		CircularData* pOut = SoundManager::GetG2A();
		assert(pOut);

		Command* pCmd = new AStopSound(this->sndID, this);
		assert(pCmd);

		pOut->PushBack(pCmd);
	}
	else
	{
		assert(false);
	}

	return lock;
}

Handle::Status Sounds::Reset()
{
	Handle::Lock lock(this->handle);

	if (lock)
	{
		// Send a play command to the Audio thread
		CircularData* pOut = SoundManager::GetG2A();
		assert(pOut);

		Command* pCmd = new AResetSound(this->sndID, this);
		assert(pCmd);

		pOut->PushBack(pCmd);
	}

	return lock;
}

Handle::Status Sounds::SetVol(float snd_vol)
{
	Handle::Lock lock(this->handle);
	if (lock)
	{
		this->vol = snd_vol;

		// Place the Vol command in the queue to the Audio thread
		CircularData* pOut = SoundManager::GetG2A();
		assert(pOut);

		Command* pCmd = new AVolSound(this->sndID, this, this->vol);
		assert(pCmd);

		pOut->PushBack(pCmd);

	}
	return lock;
}

Handle::Status Sounds::SetPan(float snd_pan)
{
	Handle::Lock lock(this->handle);
	if (lock)
	{
		this->pan = snd_pan;

		// Place the Play command in the queue to the Audio thread
		CircularData* pOut = SoundManager::GetG2A();
		assert(pOut);

		Command* pCmd = new APanSound(this->sndID, this, this->pan);
		assert(pCmd);

		pOut->PushBack(pCmd);
	}
	return lock;
}

Handle::Status Sounds::SetPitch(float snd_pitch)
{
	Handle::Lock lock(this->handle);
	if (lock)
	{
		this->pitch = snd_pitch;

		// Place the Play command in the queue to the Audio thread
		CircularData* pOut = SoundManager::GetG2A();
		assert(pOut);

		Command* pCmd = new APitchSound(this->sndID, this, this->pitch);
		assert(pCmd);

		pOut->PushBack(pCmd);
	}
	return lock;
}

Handle::Status Sounds::GetVol(float& newVol)
{
	Handle::Lock lock(this->handle);
	if (lock)
	{
		newVol = this->vol;
	}
	return lock;
}

Handle::Status Sounds::GetPan(float& newPan)
{
	Handle::Lock lock(this->handle);
	if (lock)
	{
		newPan = this->pan;
	}
	return lock;
}

Handle::Status Sounds::GetPitch(float& newPitch)
{
	Handle::Lock lock(this->handle);
	if (lock)
	{
		newPitch = this->pitch;
	}
	return lock;
}
Handle::Status Sounds::GetTimeInMS(int& timeInMS)
{
	Handle::Lock lock(this->handle);

	if (lock)
	{
		// table lock
		Handle::Lock tableLock(this->table_handle);

		// Check Priority table
		if (tableLock)
		{
			bool status = false;
			for (unsigned int i = 0; i < Sounds::SND_PRIORITY_TABLE_SIZE; i++)
			{
				if (Sounds::sndPriorityTable[i].handleID == this->handle.GetID())
				{
					Time delta = (TimeEventManager::GetTimeCurrent()) - sndPriorityTable[i].startTime;

					timeInMS = Time::quotient(delta, Time(Duration::TIME_ONE_MILLISECOND));

					status = true;
					break;
				}
			}

			if (!status)
			{
				assert(false);
			}
		}
		else
		{
			assert(false);
		}
	}

	return lock;
}

// End of File 
