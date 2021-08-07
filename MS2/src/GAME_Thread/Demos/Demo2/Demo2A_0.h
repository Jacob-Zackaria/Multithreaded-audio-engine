#ifndef DEMO2A_0_H
#define DEMO2A_0_H

#include "Command.h"
#include "SoundManager.h"

class Demo2A_0 : public Command
{
public:
	Demo2A_0() = default;
	~Demo2A_0() = default;
	Demo2A_0(const Demo2A_0&) = delete;
	Demo2A_0& operator = (const Demo2A_0&) = delete;

	// Behold the demo
	virtual void Execute() override
	{
		// create a sound call.
		Sounds* pSndA = SoundManager::Add(SndID::Intro_mono, nullptr, 200);

		// Vol, Pan & Pitch
		assert(pSndA->SetVol(0.8f) == Handle::Status::SUCCESS);
		assert(pSndA->SetPan(0.0f) == Handle::Status::SUCCESS);
		assert(pSndA->SetPitch(1.0f) == Handle::Status::SUCCESS);

		// Call the sound
		assert(pSndA->Play() == Handle::Status::SUCCESS);
	}
};


#endif