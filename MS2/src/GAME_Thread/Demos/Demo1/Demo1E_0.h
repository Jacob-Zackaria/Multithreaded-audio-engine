
//----------------------------------------------------------------------------
// Copyright 2020, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#ifndef DEMO1E_0_H
#define DEMO1E_0_H

#include "Command.h"
#include "SoundManager.h"
#include "ThreadHelper.h"

void Demo1E_1_Main();

class Demo1E_0 : public Command
{
public:
	Demo1E_0() = default;
	~Demo1E_0() = default;
	Demo1E_0(const Demo1E_0&) = delete;
	Demo1E_0& operator = (const Demo1E_0&) = delete;

	// Behold the demo
	virtual void Execute() override
	{
		std::thread  Demo1E_1_Thread(Demo1E_1_Main);
		ThreadHelper::SetThreadName(Demo1E_1_Thread, "DEMO_1E_1");
		Demo1E_1_Thread.detach();
	}
};


#endif

// --- End of File ---
