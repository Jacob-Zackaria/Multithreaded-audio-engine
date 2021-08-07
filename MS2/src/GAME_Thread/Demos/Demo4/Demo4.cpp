//----------------------------------------------------------------------------
// Copyright 2020, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#include "TimeEventManager.h"

#include "Demo4.h"
#include "Demo4_0.h"
#include "Demo4_1.h"
void Demo4()
{
	Trace::out("\n---- DEMO 4 ----\n\n");
	// 0 sec
	Demo4_0 *p_0 = new Demo4_0();
	assert(p_0);

	// 3.5 sec
	Demo4_1* p_1 = new Demo4_1();
	assert(p_1);

	TimeEventManager::Add(p_0, 0 * Time(Duration::TIME_ONE_SECOND));
	TimeEventManager::Add(p_1, 3 * Time(Duration::TIME_ONE_SECOND));
	
}

// --- End of File ---
