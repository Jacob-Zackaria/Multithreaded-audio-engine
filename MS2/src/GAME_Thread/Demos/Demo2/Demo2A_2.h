#ifndef DEMO2A_2_H
#define DEMO2A_2_H

#include "Command.h"
#include "SoundManager.h"
#include "TimeEventManager.h"

class Demo2A_2 : public Command
{
public:
	Demo2A_2(int time) : newTime(time) {}
	~Demo2A_2() = default;
	Demo2A_2(const Demo2A_2&) = delete;
	Demo2A_2& operator = (const Demo2A_2&) = delete;

	// Behold the demo
	virtual void Execute() override
	{
		Trace::out("\n-- (%d sec) --\n", this->newTime);
		// create a sound call.
		Sounds* pSndA = SoundManager::Find(SndID::Intro_mono);
		Trace::out(" Vol : 0.8f | Pan : Right |\n Pitch : 1.0f | Priority : 200 |\n");

		// Vol, Pan & Pitch
		assert(pSndA->SetVol(0.8f) == Handle::Status::SUCCESS);
		assert(pSndA->SetPan(1.0f) == Handle::Status::SUCCESS);
		assert(pSndA->SetPitch(1.0f) == Handle::Status::SUCCESS);
	}
private:
	int newTime;
};


#endif