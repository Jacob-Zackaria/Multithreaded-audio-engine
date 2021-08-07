//----------------------------------------------------------------------------
// Copyright 2020, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#include "TimeEventManager.h"
#include "TimeEvent.h"

TimeEventManager* TimeEventManager::poInstance = nullptr;


TimeEventManager::TimeEventManager(int reserveNum, int reserveGrow)
{
	// At this point ImageMan is created, now initialize the reserve
	this->BaseInitialize(reserveNum, reserveGrow);

	// initialize derived data here
	this->poNodeCompare = new TimeEvent();
	assert(this->poNodeCompare != nullptr);

	this->GameTime.tic();
	this->mCurrTime = this->GameTime.toc();

}

TimeEventManager::~TimeEventManager()
{
	// We created it... so we delete it
	delete this->poNodeCompare;
}


//----------------------------------------------------------------------
// Static Methods
//----------------------------------------------------------------------

void TimeEventManager::Update()
{
	// Get the instance
	TimeEventManager* pMan = TimeEventManager::privGetInstance();
	assert(pMan != nullptr);

	// squirrel away
	pMan->mCurrTime = pMan->GameTime.toc();

	// walk the list
	TimeEvent* pEvent = (TimeEvent*)pMan->BaseGetActive();
	TimeEvent* pNextEvent = nullptr;

	// Walk the list until there is no more list OR currTime is greater than timeEvent 
	// ToDo Fix: List needs to be sorted
	while (pEvent != nullptr)
	{
		// Difficult to walk a list and remove itself from the list
		// so squirrel away the next event now, use it at bottom of while
		pNextEvent = (TimeEvent*)pEvent->pNext;

		if (pMan->mCurrTime >= (pEvent->GetTriggerTime()))
		{
			// call it
			pEvent->Process();

			// remove from list
			pMan->BaseRemove(pEvent);
		}

		// advance the pointer
		pEvent = pNextEvent;
	}
}



void TimeEventManager::Create(int reserveNum, int reserveGrow)
{
	// make sure values are ressonable 
	assert(reserveNum > 0);
	assert(reserveGrow > 0);

	// initialize the singleton here
	assert(poInstance == nullptr);

	// Do the initialization
	if (poInstance == nullptr)
	{
		poInstance = new TimeEventManager(reserveNum, reserveGrow);
	}

}

void TimeEventManager::Destroy()
{

	// Get the instance
	TimeEventManager* pMan = TimeEventManager::privGetInstance();
	assert(pMan != nullptr);

	// Clean up what it current owns reserve and active
	pMan->BaseDestroy();

	// bye bye singleton
	delete pMan->poInstance;
}

Time TimeEventManager::GetTimeCurrent()
{
	// Get the instance
	TimeEventManager* pMan = TimeEventManager::privGetInstance();
	assert(pMan != nullptr);

	return pMan->mCurrTime;
}

TimeEvent* TimeEventManager::Add(Command* pCommand, Time deltaTimeToTrigger)
{
	TimeEventManager* pMan = TimeEventManager::privGetInstance();
	assert(pMan != nullptr);

	TimeEvent* pNode = (TimeEvent*)pMan->BaseAdd();
	assert(pNode != nullptr);

	// Create a new one given a wash
	assert(pCommand);
	pNode->Set(pCommand, deltaTimeToTrigger);

	return pNode;
}

TimeEvent* TimeEventManager::Find(TimeEvent::ID event_id)
{
	TimeEventManager* pMan = TimeEventManager::privGetInstance();
	assert(pMan != nullptr);

	// Compare functions only compares two Nodes

	// So:  Use the Compare Node - as a reference
	//      use in the Compare() function
	pMan->poNodeCompare->SetID(event_id);

	TimeEvent* pData = (TimeEvent*)pMan->BaseFind(pMan->poNodeCompare);
	return pData;
}

void TimeEventManager::Remove(TimeEvent* pNode)
{
	TimeEventManager* pMan = TimeEventManager::privGetInstance();
	assert(pMan != nullptr);

	assert(pNode != nullptr);
	pMan->BaseRemove(pNode);
}

void TimeEventManager::Dump()
{
	TimeEventManager* pMan = TimeEventManager::privGetInstance();
	assert(pMan != nullptr);
	Trace::out("\n**************************************\n");
	Trace::out("TimerMan::Dump()  \n");
	pMan->BaseDump();
	Trace::out("\n**************************************\n\n");
}

//----------------------------------------------------------------------
// Override Abstract methods
//----------------------------------------------------------------------
DLink* TimeEventManager::DerivedCreateNode()
{
	DLink* pNode = new TimeEvent();
	assert(pNode != nullptr);

	return pNode;
}

bool TimeEventManager::DerivedCompare(DLink* pLinkA, DLink* pLinkB)
{
	// This is used in baseFind() 
	assert(pLinkA != nullptr);
	assert(pLinkB != nullptr);

	TimeEvent* pDataA = (TimeEvent*)pLinkA;
	TimeEvent* pDataB = (TimeEvent*)pLinkB;

	bool status = false;

	if (pDataA->GetID() == pDataB->GetID())
	{
		status = true;
	}

	return status;
}

void TimeEventManager::DerivedWash(DLink* pLink)
{
	assert(pLink != nullptr);
	TimeEvent* pNode = (TimeEvent*)pLink;
	pNode->Wash();
}

void TimeEventManager::DerivedDumpNode(DLink* pLink)
{
	assert(pLink != nullptr);
	TimeEvent* pData = (TimeEvent*)pLink;
	pData->Dump();
}

void TimeEventManager::DerivedDestroyNode(DLink* pLink)
{
	assert(pLink);
	TimeEvent* pData = (TimeEvent*)pLink;
	delete pData;
}

//----------------------------------------------------------------------
// Private methods
//----------------------------------------------------------------------
TimeEventManager* TimeEventManager::privGetInstance()
{
	// Safety - this forces users to call Create() first before using class
	assert(poInstance != nullptr);

	return poInstance;
}


// --- End of File ---
