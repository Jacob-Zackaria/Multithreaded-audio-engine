#include "Demo1.h"
#include "TimeEventManager.h"

void Demo1()
{
	Trace::out("\n---- DEMO 1 ----\n");
	// Play 101 : Center
	Demo1A_0* p1A_0 = new Demo1A_0();
	assert(p1A_0);

	// Play 101 : Left
	Demo1A_1* p1A_1 = new Demo1A_1();
	assert(p1A_1);

	// Play 101 : Right
	Demo1A_2* p1A_2 = new Demo1A_2();
	assert(p1A_2);

	// Play 102 : Left to Right
	Demo1B_0* p1B_0 = new Demo1B_0();
	assert(p1B_0);

	// Play 102 : Right to Left
	Demo1B_1* p1B_1 = new Demo1B_1();
	assert(p1B_1);

	// Play 103 : Low to High
	Demo1C_0* p1C_0 = new Demo1C_0();
	assert(p1C_0);

	// Play 103 : High to Low
	Demo1C_1* p1C_1 = new Demo1C_1();
	assert(p1C_1);

	// Play 104 : Left
	Demo1D_0* p1D_0 = new Demo1D_0();
	assert(p1D_0);

	// Play 105 : Right
	Demo1D_1* p1D_1 = new Demo1D_1();
	assert(p1D_1);

	// Print 104 : Time
	Demo1D_2* p1D_2 = new Demo1D_2();
	assert(p1D_2);

	// Print 104 : Time
	Demo1D_3* p1D_3 = new Demo1D_3();
	assert(p1D_3);

	// Print 104 : Time and Stop
	Demo1D_4* p1D_4 = new Demo1D_4();
	assert(p1D_4);

	// Print 105 : Time and Stop
	Demo1D_5* p1D_5 = new Demo1D_5();
	assert(p1D_5);

	// Play 102 : 4 Times
	Demo1E_0* p1E_0 = new Demo1E_0();
	assert(p1E_0);

	TimeEventManager::Add(p1A_0, 0 * Time(Duration::TIME_ONE_SECOND));
	TimeEventManager::Add(p1A_1, 3 * Time(Duration::TIME_ONE_SECOND));
	TimeEventManager::Add(p1A_2, 6 * Time(Duration::TIME_ONE_SECOND));
	TimeEventManager::Add(p1B_0, 10 * Time(Duration::TIME_ONE_SECOND));
	TimeEventManager::Add(p1B_1, 15 * Time(Duration::TIME_ONE_SECOND));
	TimeEventManager::Add(p1C_0, 20 * Time(Duration::TIME_ONE_SECOND));
	TimeEventManager::Add(p1C_1, 25 * Time(Duration::TIME_ONE_SECOND));
	TimeEventManager::Add(p1D_1, 30 * Time(Duration::TIME_ONE_SECOND));
	TimeEventManager::Add(p1D_0, 30 * Time(Duration::TIME_ONE_SECOND));
	TimeEventManager::Add(p1D_2, 35 * Time(Duration::TIME_ONE_SECOND));
	TimeEventManager::Add(p1D_3, 38 * Time(Duration::TIME_ONE_SECOND));
	TimeEventManager::Add(p1D_4, 60 * Time(Duration::TIME_ONE_SECOND));
	TimeEventManager::Add(p1D_5, 72 * Time(Duration::TIME_ONE_SECOND));
	TimeEventManager::Add(p1E_0, 80 * Time(Duration::TIME_ONE_SECOND));
}