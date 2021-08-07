//----------------------------------------------------------------------------
// Copyright 2020, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#include "SoundManager.h"
#include "ACreateSounds.h"
// Timer control.
#include "TimeEventManager.h"
#include "Timer.h"
#include "AQuit.h"

SoundManager* SoundManager::poInstance = nullptr;

SoundManager::SoundManager(int reserveNum, int reserveGrow) noexcept
{
	// At this point ImageMan is created, now initialize the reserve
	this->BaseInitialize(reserveNum, reserveGrow);

	// initialize derived data here
	this->poNodeCompare = new Sounds();
	assert(this->poNodeCompare != nullptr);

	this->pG2A = new CircularData();
	assert(pG2A);

	this->pA2G = new CircularData();
	assert(pA2G);
}

SoundManager::~SoundManager()
{
	// We created it... so we delete it
	delete this->poNodeCompare;

	delete this->pA2G;
	delete this->pG2A;
}

CircularData* SoundManager::GetG2A() noexcept
{
	SoundManager* pMan = SoundManager::GetPrivateInstance();
	assert(pMan != nullptr);

	return pMan->pG2A;
}

CircularData* SoundManager::GetA2G() noexcept
{
	SoundManager* pMan = SoundManager::GetPrivateInstance();
	assert(pMan != nullptr);

	return pMan->pA2G;
}

void SoundManager::Update()
{
	// Process Queue
	Command* pCmd = nullptr;
	CircularData* pInGame = SoundManager::GetA2G();
	assert(pInGame);

	// Any commands to process?
	while (pInGame->PopFront(pCmd) == true)
	{
		assert(pCmd);
		pCmd->Execute();

		// Commands are instantly killed after execution
		// todo... recycle commands

		delete pCmd;
	}

	// TimeEvent Update() - needs to be called once a Game frame
	TimeEventManager::Update();
}

void SoundManager::Create(int reserveNum, int reserveGrow) noexcept
{
	// make sure values are ressonable 
	assert(reserveNum > 0);
	assert(reserveGrow > 0);

	// initialize the singleton here
	assert(poInstance == nullptr);

	// Do the initialization
	if (poInstance == nullptr)
	{
		poInstance = new SoundManager(reserveNum, reserveGrow);
	}

}

void SoundManager::Destroy() noexcept
{

	// Get the instance
	SoundManager* pMan = SoundManager::GetPrivateInstance();
	assert(pMan != nullptr);

	// Clean up what it current owns reserve and active
	pMan->BaseDestroy();

	// bye bye singleton
	delete pMan->poInstance;
}

Sounds* SoundManager::Add(SndID snd_id, UserCallback* pCallback, SoundPriority snd_priority)
{
	SoundManager* pMan = SoundManager::GetPrivateInstance();
	assert(pMan != nullptr);

	Sounds* pNode = (Sounds*)pMan->BaseAdd();
	assert(pNode != nullptr);

	// Create a new one given a wash
	pNode->Set(snd_id, snd_priority);

	// Now create a the sound call on the Audio thread
	// Place the "Create" command in the queue to the Audio thread
	CircularData* pOut = SoundManager::GetG2A();
	assert(pOut);

	// Doesn't need to know snd_priority its only on game side
	Command* pCmd = new ACreateSounds(snd_id, pNode, pCallback);
	assert(pCmd);

	pOut->PushBack(pCmd);

	return pNode;
}

Sounds* SoundManager::Find(SndID snd_id)
{
	SoundManager* pMan = SoundManager::GetPrivateInstance();
	assert(pMan != nullptr);

	// Compare functions only compares two Nodes

	// So:  Use the Compare Node - as a reference
	//      use in the Compare() function
	pMan->poNodeCompare->SetID(snd_id);

	Sounds* pData = (Sounds*)pMan->BaseFind(pMan->poNodeCompare);
	return pData;
}

Sounds* SoundManager::FindWithHandle(unsigned int sndHandle_id)
{
	SoundManager* pMan = SoundManager::GetPrivateInstance();
	assert(pMan != nullptr);

	Sounds* newSound = (Sounds*)pMan->BaseGetActive();
	while (newSound != nullptr)
	{
		if (newSound->GetHandleID() == sndHandle_id)
		{
			return (newSound);
		}

		newSound = (Sounds*)newSound->pNext;
	}
	return (newSound);
}

void SoundManager::Quit(SndID snd_id)
{
	SoundManager* pMan = SoundManager::GetPrivateInstance();
	assert(pMan != nullptr);

	Sounds* pNode = (Sounds*)pMan->BaseAdd();
	assert(pNode != nullptr);

	// Create a new one given a wash
	pNode->Set(snd_id, 0);

	// Now create a the sound call on the Audio thread
	// Place the "Quit" command in the queue to the Audio thread
	CircularData* pOut = SoundManager::GetG2A();
	assert(pOut);

	Command* pCmd = new AQuit(SndID::Quit, pNode);
	assert(pCmd);

	pOut->PushBack(pCmd);
}

void SoundManager::Remove(Sounds* pNode)
{
	SoundManager* pMan = SoundManager::GetPrivateInstance();
	assert(pMan != nullptr);

	assert(pNode != nullptr);
	pMan->BaseRemove(pNode);
}

void SoundManager::Dump()
{
	SoundManager* pMan = SoundManager::GetPrivateInstance();
	assert(pMan != nullptr);
	Trace::out("\n**************************************\n");
	Trace::out("SndMan::Dump()  \n");
	pMan->BaseDump();
	Trace::out("\n**************************************\n\n");
}

//----------------------------------------------------------------------
// Override Abstract methods
//----------------------------------------------------------------------
DLink* SoundManager::DerivedCreateNode()
{
	DLink* pNode = new Sounds();
	assert(pNode != nullptr);

	return pNode;
}

bool SoundManager::DerivedCompare(DLink* pLinkA, DLink* pLinkB)
{
	// This is used in baseFind() 
	assert(pLinkA != nullptr);
	assert(pLinkB != nullptr);

	Sounds* pDataA = (Sounds*)pLinkA;
	Sounds* pDataB = (Sounds*)pLinkB;

	bool status = false;

	SndID A_id;
	SndID B_id;

	pDataA->GetID(A_id);
	pDataB->GetID(B_id);

	if (A_id == B_id)
	{
		status = true;
	}

	return status;
}

void SoundManager::DerivedWash(DLink* pLink)
{
	assert(pLink != nullptr);
	Sounds* pNode = (Sounds*)pLink;
	pNode->Wash();
}

void SoundManager::DerivedDumpNode(DLink* pLink)
{
	assert(pLink != nullptr);
	Sounds* pData = (Sounds*)pLink;
	pData->Dump();
}

void SoundManager::DerivedDestroyNode(DLink* pLink)
{
	assert(pLink);
	Sounds* pData = (Sounds*)pLink;
	delete pData;
}


SoundManager* SoundManager::GetPrivateInstance() noexcept
{
	// Safety - this forces users to call Create() first before using class
	assert(poInstance != nullptr);

	return poInstance;
}


// End of File 
