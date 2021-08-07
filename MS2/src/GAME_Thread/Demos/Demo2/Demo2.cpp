#include "Demo2.h"
#include "TimeEventManager.h"
#include "SoundManager.h"

void Demo2()
{
	Trace::out("\n---- DEMO 2 ----\n\n");

	// Play Voice stitching. 
	Demo2A_0* p2A_0 = new Demo2A_0();
	assert(p2A_0);

	// Pan Center
	Demo2A_1* p2A_1 = new Demo2A_1(0);
	assert(p2A_1);

	// Pan Right.
	Demo2A_2* p2A_2 = new Demo2A_2(10);
	assert(p2A_2);

	// Pan Left.
	Demo2A_3* p2A_3 = new Demo2A_3(20);
	assert(p2A_3);

	// Pan Center
	Demo2A_1* p2A_4 = new Demo2A_1(30);
	assert(p2A_4);

	// Pan Right.
	Demo2A_2* p2A_5 = new Demo2A_2(40);
	assert(p2A_5);

	// Pan Left.
	Demo2A_3* p2A_6 = new Demo2A_3(50);
	assert(p2A_6);

	TimeEventManager::Add(p2A_1, 0 * Time(Duration::TIME_ONE_SECOND));
	TimeEventManager::Add(p2A_0, 0 * Time(Duration::TIME_ONE_SECOND));
	TimeEventManager::Add(p2A_2, 10 * Time(Duration::TIME_ONE_SECOND));
	TimeEventManager::Add(p2A_3, 20 * Time(Duration::TIME_ONE_SECOND));
	TimeEventManager::Add(p2A_4, 30 * Time(Duration::TIME_ONE_SECOND));
	TimeEventManager::Add(p2A_5, 40 * Time(Duration::TIME_ONE_SECOND));
	TimeEventManager::Add(p2A_6, 50 * Time(Duration::TIME_ONE_SECOND));
}