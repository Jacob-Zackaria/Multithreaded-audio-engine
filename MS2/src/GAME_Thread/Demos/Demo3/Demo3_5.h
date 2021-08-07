#ifndef DEMO3_5_H
#define DEMO3_5_H

#include "Command.h"
#include "SoundManager.h"
class Demo3_5 : public Command
{
public:
	Demo3_5(int time) : newTime(time) {}
	~Demo3_5() = default;
	Demo3_5(const Demo3_5&) = delete;
	Demo3_5& operator = (const Demo3_5&) = delete;

	// Behold the demo
	virtual void Execute() override
	{
		Trace::out("\n-- (%d sec) --\n", this->newTime);
		Trace::out("Priority : 75\n");
		// Play A

		Sounds* pSndA = SoundManager::Add(SndID::Coma, nullptr, 75);
		assert(pSndA);

		// Vol & Pan
		assert(pSndA->SetVol(0.10f) == Handle::Status::SUCCESS);
		assert(pSndA->SetPan(0.0f) == Handle::Status::SUCCESS);
		assert(pSndA->SetPitch(1.0f) == Handle::Status::SUCCESS);
		// Call the sound
		assert(pSndA->Play() == Handle::Status::SUCCESS);

	}
private:
	int newTime;
};

#endif