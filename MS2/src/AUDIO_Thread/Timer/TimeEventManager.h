//----------------------------------------------------------------------------
// Copyright 2020, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#ifndef TIME_EVENT_MAN_H
#define	TIME_EVENT_MAN_H


#include "Manager.h"
#include "Command.h"
#include "TimeEvent.h"
#include "Timer.h"

// This class is only there for pretty UML
class TimeEventManager_Link : public Manager
{
public:
	TimeEvent_Link* poActive;
	TimeEvent_Link* poReserve;
};

class TimeEventManager : public TimeEventManager_Link
{
	//----------------------------------------------------------------------
	// Big four
	//----------------------------------------------------------------------
private:
	TimeEventManager(int reserveNum = 3, int reserveGrow = 1);
	TimeEventManager(const TimeEventManager&) = delete;
	TimeEventManager& operator = (const TimeEventManager&) = delete;
	TimeEventManager() = delete;
	~TimeEventManager();

public:

	//----------------------------------------------------------------------
	// Static Methods
	//----------------------------------------------------------------------
	static void Create(int reserveNum = 1, int reserveGrow = 1);
	static void Destroy();

	static TimeEvent* Add(Command* pCommand, Time deltaTimeToTrigger);
	static TimeEvent* Find(TimeEvent::ID event_id);
	static Time GetTimeCurrent();

	static void Remove(TimeEvent* pNode);
	static void Dump();

	static void Update();


protected:
	virtual DLink* DerivedCreateNode() override;
	virtual bool DerivedCompare(DLink* pLinkA, DLink* pLinkB) override;
	virtual void DerivedWash(DLink* pLink) override;
	virtual void DerivedDumpNode(DLink* pLink) override;
	virtual void DerivedDestroyNode(DLink* pLink) override;

	//----------------------------------------------------------------------
	// Private methods
	//----------------------------------------------------------------------
private:
	static TimeEventManager* privGetInstance();

	//----------------------------------------------------------------------
	// Data - unique data for this manager 
	//----------------------------------------------------------------------
	static TimeEventManager* poInstance;

	TimeEvent* poNodeCompare;
	Time		mCurrTime;
	Timer		GameTime;
};

#endif

// --- End of File ---
