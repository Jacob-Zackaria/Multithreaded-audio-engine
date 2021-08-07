//----------------------------------------------------------------------------
// Copyright 2020, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#ifndef DEMO3_2_H
#define DEMO3_2_H

#include "Command.h"
#include "SoundManager.h"
class Demo3_2 : public Command
{
public:
	Demo3_2() = default;
	~Demo3_2() = default;
	Demo3_2(const Demo3_2 &) = delete;
	Demo3_2 & operator = (const Demo3_2 &) = delete;

	// Behold the demo
	virtual void Execute() override
	{
		Trace::out("\n-- (2 sec) --\n");
		Trace::out("Priority : 75\n");
		// Play A

		Sounds *pSndA = SoundManager::Add(SndID::Coma, nullptr, 75);
		assert(pSndA);

		// Vol & Pan
		assert(pSndA->SetVol(0.10f) == Handle::Status::SUCCESS);
		assert(pSndA->SetPan(0.0f) == Handle::Status::SUCCESS);
		assert(pSndA->SetPitch(1.0f) == Handle::Status::SUCCESS);
		// Call the sound
		assert(pSndA->Play() == Handle::Status::SUCCESS);

		// Print snd priority table
		Sounds::PrintPriorityTable();

	}

};

#endif

// --- End of File ---
