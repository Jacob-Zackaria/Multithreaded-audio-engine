#ifndef DEMO5_2_H
#define DEMO5_2_H

#include "Command.h"
#include "SoundManager.h"

class Demo5_2 : public Command
{
public:
	Demo5_2() = default;
	~Demo5_2() = default;
	Demo5_2(const Demo5_2&) = delete;
	Demo5_2& operator = (const Demo5_2&) = delete;

	// Behold the demo
	virtual void Execute() override
	{
		Trace::out("\n-- (60 sec) --\n");

		// create a sound call.
		Sounds* pSndA = SoundManager::Find(SndID::Beethoven);

		// stop
		pSndA->Stop();
	}

};

#endif