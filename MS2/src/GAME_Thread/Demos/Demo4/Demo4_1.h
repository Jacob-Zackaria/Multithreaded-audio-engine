#ifndef DEMO4_1_H
#define DEMO4_1_H

#include "Command.h"
#include "SoundManager.h"
#include "UserCallBack.h"

class Demo4_1 : public Command
{
public:
	Demo4_1() = default;
	~Demo4_1() = default;
	Demo4_1(const Demo4_1&) = delete;
	Demo4_1& operator = (const Demo4_1&) = delete;

	// Behold the demo
	virtual void Execute() override
	{
		// delay 0.5 sec
		std::this_thread::sleep_for(std::chrono::milliseconds(500));

		Trace::out("\n404 - Donkey: (3.5 sec)\n");
		Trace::out("*************** Sound start *************\n");
		
		// Play D

		Sounds* pSndD = nullptr;
		UserCallback* pCallback_D = new UserCallback();

		pSndD = SoundManager::Add(SndID::Donkey, pCallback_D, 200);
		assert(pSndD);

		// Vol & Pan
		assert(pSndD->SetVol(0.70f) == Handle::Status::SUCCESS);
		assert(pSndD->SetPan(-1.0f) == Handle::Status::SUCCESS);
		assert(pSndD->SetPitch(1.0f) == Handle::Status::SUCCESS);
		// Call the sound
		assert(pSndD->Play() == Handle::Status::SUCCESS);
	}

};

#endif