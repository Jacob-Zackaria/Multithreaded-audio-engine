//----------------------------------------------------------------------------
// Copyright 2020, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#ifndef DEMO5_0_H
#define DEMO5_0_H

#include "Command.h"
#include "FileManager.h"
#include "SoundManager.h"
#include "FileUserCallBack.h"

class Demo5_0 : public Command
{
public:
	Demo5_0() = default;
	~Demo5_0() = default;
	Demo5_0(const Demo5_0 &) = delete;
	Demo5_0 & operator = (const Demo5_0 &) = delete;

	// Behold the demo
	virtual void Execute() override
	{
		Trace::out("\n-- (0 sec) --\n");
		Trace::out("\n501 - Electro:\n");
		Trace::out("*************** Sound start *************\n");
		Trace::out(" Vol : 0.3f | Pan : Left |\n Pitch : 1.0f | Priority : 200 |\n");
		Trace::out("\n502 - Alarm:\n");
		Trace::out("*************** Sound start *************\n");
		Trace::out(" Vol : 0.3f | Pan : Left |\n Pitch : 1.0f | Priority : 200 |\n");

		// Play 501
		Sounds* pSndA = SoundManager::Add(SndID::Electro, nullptr, 200);
		assert(pSndA);

		// Vol & Pan
		assert(pSndA->SetVol(0.30f) == Handle::Status::SUCCESS);
		assert(pSndA->SetPan(-1.0f) == Handle::Status::SUCCESS);
		assert(pSndA->SetPitch(1.0f) == Handle::Status::SUCCESS);
		// Call the sound
		assert(pSndA->Play() == Handle::Status::SUCCESS);
		

		// Initiate 503 Beethoven load.
		FileUserCallback *pFileCB = new FileUserCallback();
		assert(pFileCB);

		// Set the sound to play once finished loading
		pFileCB->Set(SndID::Beethoven);

		// Start the load
		FileManager::Add("../../MS2_AudioFiles/Beethoven_stereo.wav", Wave::ID::Beethoven, pFileCB);

		// Play 502
		Sounds* pSndB = SoundManager::Add(SndID::Alarm, nullptr, 200);
		assert(pSndB);

		// Vol & Pan
		assert(pSndB->SetVol(0.30f) == Handle::Status::SUCCESS);
		assert(pSndB->SetPan(-1.0f) == Handle::Status::SUCCESS);
		assert(pSndB->SetPitch(1.0f) == Handle::Status::SUCCESS);
		// Call the sound
		assert(pSndB->Play() == Handle::Status::SUCCESS);
	}

};

#endif

// --- End of File ---
