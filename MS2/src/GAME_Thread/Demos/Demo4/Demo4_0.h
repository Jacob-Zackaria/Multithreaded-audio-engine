//----------------------------------------------------------------------------
// Copyright 2020, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#ifndef DEMO4_0_H
#define DEMO4_0_H

#include "Command.h"
#include "SoundManager.h"
#include "UserCallBack.h"

class Demo4_0 : public Command
{
public:
	Demo4_0() = default;
	~Demo4_0() = default;
	Demo4_0(const Demo4_0 &) = delete;
	Demo4_0 & operator = (const Demo4_0 &) = delete;

	// Behold the demo
	virtual void Execute() override
	{
		Trace::out("\n401 - Dial: (0 sec)\n");
		Trace::out("*************** Sound start *************\n");
		Trace::out("\n402 - MoonPatrol: (0 sec)\n");
		Trace::out("*************** Sound start *************\n");
		Trace::out("\n403 - Sequence: (0 sec)\n");
		Trace::out("*************** Sound start *************\n");

		// Play A

		Sounds *pSndA = nullptr;
		UserCallback *pCallback_A = new UserCallback();

		pSndA = SoundManager::Add(SndID::Dial, pCallback_A , 200);
		assert(pSndA);

		// Vol & Pan
		assert(pSndA->SetVol(0.70f) == Handle::Status::SUCCESS);
		assert(pSndA->SetPan(-1.0f) == Handle::Status::SUCCESS);
		assert(pSndA->SetPitch(1.0f) == Handle::Status::SUCCESS);
		// Call the sound
		assert(pSndA->Play() == Handle::Status::SUCCESS);

		// Play B

		Sounds *pSndB = nullptr;
		UserCallback *pCallback_B = new UserCallback();

		pSndB = SoundManager::Add(SndID::MoonPatrol, pCallback_B, 200);
		assert(pSndB);

		// Vol & Pan
		assert(pSndB->SetVol(0.70f) == Handle::Status::SUCCESS);
		assert(pSndB->SetPan(1.0f) == Handle::Status::SUCCESS);
		assert(pSndB->SetPitch(1.0f) == Handle::Status::SUCCESS);
		// Call the sound
		assert(pSndB->Play() == Handle::Status::SUCCESS);

		//// Play C

		Sounds *pSndC = nullptr;
		UserCallback *pCallback_C = new UserCallback();

		pSndC = SoundManager::Add(SndID::Sequence, pCallback_C, 200);
		assert(pSndC);

		// Vol & Pan
		assert(pSndC->SetVol(0.70f) == Handle::Status::SUCCESS);
		assert(pSndC->SetPan(-1.0f) == Handle::Status::SUCCESS);
		assert(pSndC->SetPitch(1.0f) == Handle::Status::SUCCESS);
		// Call the sound
		assert(pSndC->Play() == Handle::Status::SUCCESS);

	}

};

#endif

// --- End of File ---
