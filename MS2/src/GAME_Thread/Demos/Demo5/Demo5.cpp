//----------------------------------------------------------------------------
// Copyright 2020, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#include "TimeEventManager.h"

#include "Demo5.h"
#include "Demo5_0.h"
#include "Demo5_1.h"
#include "Demo5_2.h"

void Demo5()
{
	Trace::out("\n---- DEMO 5 ----\n\n");

	// 0 sec
	Demo5_0 *p_0 = new Demo5_0();
	assert(p_0);

	// 5 sec
	Demo5_1* p_1 = new Demo5_1(5);
	assert(p_1);

	// 10 sec
	Demo5_1* p_2 = new Demo5_1(10);
	assert(p_2);

	// 15 sec
	Demo5_1* p_3 = new Demo5_1(15);
	assert(p_3);

	// 20 sec
	Demo5_1* p_4 = new Demo5_1(20);
	assert(p_4);

	// 25 sec
	Demo5_1* p_5 = new Demo5_1(25);
	assert(p_5);

	// 60 sec
	Demo5_2* p_6 = new Demo5_2();
	assert(p_6);

	TimeEventManager::Add(p_0, 0 * Time(Duration::TIME_ONE_SECOND));
	TimeEventManager::Add(p_1, 5 * Time(Duration::TIME_ONE_SECOND));
	TimeEventManager::Add(p_2, 10 * Time(Duration::TIME_ONE_SECOND));
	TimeEventManager::Add(p_3, 15 * Time(Duration::TIME_ONE_SECOND));
	TimeEventManager::Add(p_4, 20 * Time(Duration::TIME_ONE_SECOND));
	TimeEventManager::Add(p_5, 25 * Time(Duration::TIME_ONE_SECOND));
	TimeEventManager::Add(p_6, 60 * Time(Duration::TIME_ONE_SECOND));
}


// --- End of File ---
