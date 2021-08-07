//----------------------------------------------------------------------------
// Copyright 2020, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#ifndef SOUNDS_H
#define SOUNDS_H

#include "HandleManager.h"
#include "SndID.h"
#include "DLink.h"
#include "ASounds.h"
#include "SoundPriorityEntry.h"

typedef int SoundPriority;

// This class is only there for pretty UML
class Sounds_Link : public DLink
{
};

class Sounds : public Sounds_Link
{
public:

	// constants
	static const unsigned int SND_PRIORITY_TABLE_SIZE = 6;
	static const int SND_PRIORITY_TABLE_INVALID = -1;

	Sounds();
	Sounds(const Sounds&) = delete;
	const Sounds& operator=(const Sounds&) = delete;
	~Sounds();

	Handle::Status SetID(SndID snd_id);
	Handle::Status GetID(SndID& snd_id);

	Handle::Status Set(SndID snd_id, SoundPriority snd_priority);

	void Dump();
	void Wash();

	// --- COMMANDS -----------
	Handle::Status Play();
	Handle::Status Stop();
	Handle::Status Reset();
	Handle::Status SetVol(float vol);
	Handle::Status SetPan(float pan);
	Handle::Status SetPitch(float pitch);
	Handle::Status GetVol(float& newVol);
	Handle::Status GetPan(float& newPan);
	Handle::Status GetPitch(float& newPitch);
	Handle::Status GetTimeInMS(int& timeInMS);

	
	//----------------------------------------------------------------------
	// Sound Table
	//----------------------------------------------------------------------
	static void PrintPriorityTable();
	Handle::Status RemoveFromPriorityTable();
	static void StopPendingSounds();

	// Audio thread sets
	void SetASound(ASounds* p);
	void GetASound(ASounds*& p);
	//------- DEBUG -----------------
	unsigned int GetHandleID()
	{
		return this->handle.GetID();
	}
	unsigned int GetHandleIndex()
	{
		return this->handle.GetIndex();
	}

private:
	void privClear();
	bool privUseSlotInTable();
	void CheckPriority();

	SndID	sndID;
	ASounds* pASnd;

	float	vol;
	float   pan;
	float   pitch;
	SoundPriority priority;

	// Here's the magic: Create the handle variable.
	Handle handle;

public:
	// ------- STATIC ----------------
	static SoundPriorityEntry  sndPriorityTable[SND_PRIORITY_TABLE_SIZE];
	static Handle	         table_handle;
};

#endif


// End of File 

