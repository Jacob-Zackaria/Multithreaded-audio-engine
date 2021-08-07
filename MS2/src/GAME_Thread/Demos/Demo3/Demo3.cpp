//----------------------------------------------------------------------------
// Copyright 2020, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#include "TimeEventManager.h"

#include "Demo3.h"
#include "Demo3_0.h"
#include "Demo3_1.h"
#include "Demo3_2.h"
#include "Demo3_3.h"
#include "Demo3_4.h"
#include "Demo3_5.h"
#include "Demo3_6.h"
void Demo3()
{
	Trace::out("\n---- DEMO 3 ----\n\n");

	// Play Coma A,B,C Priority : 10,50,150
	Demo3_0 *p_0 = new Demo3_0();
	assert(p_0);	

	// priority 50
	Demo3_1 *p_1 = new Demo3_1();
	assert(p_1);	

	// priority 75
	Demo3_2 *p_2 = new Demo3_2();
	assert(p_2);	

	// priority 100
	Demo3_3 *p_3 = new Demo3_3();
	assert(p_3);	

	// priority 150
	Demo3_4 *p_4 = new Demo3_4(4);
	assert(p_4);

	// priority 75
	Demo3_5* p_5 = new Demo3_5(5);
	assert(p_5);

	// priority 75
	Demo3_5* p_6 = new Demo3_5(6);
	assert(p_6);

	// priority 75
	Demo3_5* p_7 = new Demo3_5(7);
	assert(p_7);

	// priority 150
	Demo3_4* p_8 = new Demo3_4(8);
	assert(p_8);

	// Stop all
	Demo3_6* p_13 = new Demo3_6();
	assert(p_13);
	
	TimeEventManager::Add(p_0, 0 * Time(Duration::TIME_ONE_SECOND));

	TimeEventManager::Add(p_1, 1 * Time(Duration::TIME_ONE_SECOND));

	TimeEventManager::Add(p_2, 2 * Time(Duration::TIME_ONE_SECOND));

	TimeEventManager::Add(p_3, 3 * Time(Duration::TIME_ONE_SECOND));

	TimeEventManager::Add(p_4, 4 * Time(Duration::TIME_ONE_SECOND));

	TimeEventManager::Add(p_5, 5 * Time(Duration::TIME_ONE_SECOND));

	TimeEventManager::Add(p_6, 6 * Time(Duration::TIME_ONE_SECOND));

	TimeEventManager::Add(p_7, 7 * Time(Duration::TIME_ONE_SECOND));

	TimeEventManager::Add(p_8, 8 * Time(Duration::TIME_ONE_SECOND));

	TimeEventManager::Add(p_13, 13 * Time(Duration::TIME_ONE_SECOND));
}

// --- End of File ---
