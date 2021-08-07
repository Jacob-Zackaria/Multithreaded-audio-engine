//----------------------------------------------------------------------------
// Copyright 2020, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------


#include "AudioEngine.h"
#include "ASoundManager.h"


ASoundManager* ASoundManager::pInstance = nullptr;

//---------------------------------------------------------------------------------------------------------
// Design Notes:
//
//  Singleton class - use only public static methods for customers
//
//  * One single compare node is owned by this singleton - used for find, prevent extra news
//  * Create one - NULL Object 
//
//---------------------------------------------------------------------------------------------------------

ASoundManager::ASoundManager(int reserveNum, int reserveGrow)
{
	this->QuitFlag = false;

	// At this point Man is created, now initialize the reserve
	this->BaseInitialize(reserveNum, reserveGrow);

	// initialize derived data here
	this->poNodeCompare = new ASounds();
	assert(this->poNodeCompare != nullptr);
}

ASoundManager::~ASoundManager()
{
	assert(ASoundManager::IsQuit() == true);
	// We created it... so we delete it
	delete this->poNodeCompare;

}

//----------------------------------------------------------------------
// Static Methods
//----------------------------------------------------------------------
void ASoundManager::Create(int reserveNum, int reserveGrow)
{
	// make sure values are ressonable 
	assert(reserveNum > 0);
	assert(reserveGrow > 0);

	// initialize the singleton here
	assert(pInstance == nullptr);

	// Do the initialization
	if (pInstance == nullptr)
	{
		pInstance = new ASoundManager(reserveNum, reserveGrow);
	}

}

void ASoundManager::Destroy()
{
	// Get the instance
	ASoundManager* pMan = ASoundManager::privGetInstance();
	assert(pMan != nullptr);

	// Clean up what it current owns reserve and active
	pMan->BaseDestroy();

	// bye bye singleton
	delete pMan->pInstance;
}

void ASoundManager::SetQuit()
{
	ASoundManager* pMan = ASoundManager::privGetInstance();
	assert(pMan != nullptr);

	pMan->QuitFlag = true;
}

bool  ASoundManager::IsQuit()
{
	ASoundManager* pMan = ASoundManager::privGetInstance();
	assert(pMan != nullptr);

	return pMan->QuitFlag;
}

ASounds* ASoundManager::Add(SndID snd_id)
{
	ASoundManager* pMan = ASoundManager::privGetInstance();
	assert(pMan != nullptr);

	ASounds* pNode = (ASounds*)pMan->BaseAdd();
	assert(pNode != nullptr);

	// Create a new one given a wash
	pNode->Set(snd_id);

	return pNode;
}

ASounds* ASoundManager::Find(SndID id)
{
	ASoundManager* pMan = ASoundManager::privGetInstance();
	assert(pMan != nullptr);

	// Compare functions only compares two Nodes

	// So:  Use the Compare Node - as a reference
	//      use in the Compare() function
	pMan->poNodeCompare->SetId(id);

	ASounds* pData = (ASounds*)pMan->BaseFind(pMan->poNodeCompare);
	return pData;
}

void ASoundManager::Remove(ASounds* pNode)
{
	ASoundManager* pMan = ASoundManager::privGetInstance();
	assert(pMan != nullptr);

	assert(pNode != nullptr);
	pMan->BaseRemove(pNode);
}

void ASoundManager::Dump()
{
	ASoundManager* pMan = ASoundManager::privGetInstance();
	assert(pMan != nullptr);
	Trace::out("\n**************************************\n");
	Trace::out("ASndMan::Dump()  \n");
	pMan->BaseDump();
	Trace::out("\n**************************************\n\n");
}

//----------------------------------------------------------------------
// Override Abstract methods
//----------------------------------------------------------------------
DLink* ASoundManager::DerivedCreateNode()
{
	DLink* pNode = new ASounds();
	assert(pNode != nullptr);

	return pNode;
}

bool ASoundManager::DerivedCompare(DLink* pLinkA, DLink* pLinkB)
{
	// This is used in baseFind() 
	assert(pLinkA != nullptr);
	assert(pLinkB != nullptr);

	ASounds* pDataA = (ASounds*)pLinkA;
	ASounds* pDataB = (ASounds*)pLinkB;

	bool status = false;

	SndID A;
	SndID B;

	if (pDataA->GetId(A) != Handle::Status::SUCCESS)
	{
		assert(false);
	}

	if (pDataB->GetId(B) != Handle::Status::SUCCESS)
	{
		assert(false);
	}

	if (A == B)
	{
		status = true;
	}

	return status;
}

void ASoundManager::DerivedWash(DLink* pLink)
{
	assert(pLink != nullptr);
	ASounds* pNode = (ASounds*)pLink;
	pNode->Wash();
}

void ASoundManager::DerivedDumpNode(DLink* pLink)
{
	assert(pLink != nullptr);
	ASounds* pData = (ASounds*)pLink;
	pData->Dump();
}

void ASoundManager::DerivedDestroyNode(DLink* pLink)
{
	assert(pLink);
	ASounds* pData = (ASounds*)pLink;
	delete pData;
}


//----------------------------------------------------------------------
// Private methods
//----------------------------------------------------------------------
ASoundManager* ASoundManager::privGetInstance()
{
	// Safety - this forces users to call Create() first before using class
	assert(pInstance != nullptr);

	return pInstance;
}

// --- End of File ---

