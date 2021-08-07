//----------------------------------------------------------------------------
// Copyright 2020, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#ifndef DEMO3_0_H
#define DEMO3_0_H

#include "Command.h"
#include "SoundManager.h"

class Demo3_0 : public Command
{
public:
	Demo3_0() = default;
	~Demo3_0() = default;
	Demo3_0(const Demo3_0 &) = delete;
	Demo3_0 & operator = (const Demo3_0 &) = delete;

	// Behold the demo
	virtual void Execute() override
	{
		Trace::out("\n-- (0 sec) --\n");
		Trace::out("Priority : 10, 50, 150\n");
		// Play A

			Sounds *pSndA = SoundManager::Add(SndID::Coma, nullptr, 10);
			assert(pSndA);

			// Vol & Pan
			assert(pSndA->SetVol(0.10f) == Handle::Status::SUCCESS);
			assert(pSndA->SetPan(0.0f) == Handle::Status::SUCCESS);
			assert(pSndA->SetPitch(1.0f) == Handle::Status::SUCCESS);
			// Call the sound
			assert(pSndA->Play() == Handle::Status::SUCCESS);

		// Play B

			Sounds *pSndB = SoundManager::Add(SndID::Coma, nullptr, 50);
			assert(pSndB);

			// Vol & Pan
			assert(pSndB->SetVol(0.10f) == Handle::Status::SUCCESS);
			assert(pSndB->SetPan(0.0f) == Handle::Status::SUCCESS);
			assert(pSndB->SetPitch(1.0f) == Handle::Status::SUCCESS);
			// Call the sound
			assert(pSndB->Play() == Handle::Status::SUCCESS);

		// Play C

			Sounds *pSndC = SoundManager::Add(SndID::Coma, nullptr, 150);
			assert(pSndC);

			// Vol & Pan
			assert(pSndC->SetVol(0.10f) == Handle::Status::SUCCESS);
			assert(pSndC->SetPan(0.0f) == Handle::Status::SUCCESS);
			assert(pSndC->SetPitch(1.0f) == Handle::Status::SUCCESS);
			// Call the sound
			assert(pSndC->Play() == Handle::Status::SUCCESS);

			// Print snd priority table
			Sounds::PrintPriorityTable();

	}

};

#endif

// --- End of File ---

