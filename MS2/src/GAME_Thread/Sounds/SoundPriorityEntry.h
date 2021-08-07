#ifndef SOUND_PRIORITY_ENTRY_H
#define SOUND_PRIORITY_ENTRY_H

#include "Handle.h"
#include "SndID.h"

class SoundPriorityEntry
{
public:
	SoundPriorityEntry();

	void Clear();

	// Data:
	Handle::ID	handleID;
	SndID		sndID;
	int			priority;
	Time		startTime;
};

#endif