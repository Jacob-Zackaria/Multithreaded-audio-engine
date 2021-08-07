#include "WaveManager.h"

WaveManager* WaveManager::pInstance = nullptr;

//---------------------------------------------------------------------------------------------------------
// Design Notes:
//
//  Singleton class - use only public static methods for customers
//
//  * One single compare node is owned by this singleton - used for find, prevent extra news
//  * Create one - NULL Object 
//---------------------------------------------------------------------------------------------------------

WaveManager::WaveManager(int reserveNum, int reserveGrow)
{
	// At this point Man is created, now initialize the reserve
	this->BaseInitialize(reserveNum, reserveGrow);

	// initialize derived data here
	this->poNodeCompare = new Wave();
	assert(this->poNodeCompare != nullptr);
}

WaveManager::~WaveManager()
{
	// We created it... so we delete it
	delete this->poNodeCompare;

}

//----------------------------------------------------------------------
// Static Methods
//----------------------------------------------------------------------
void WaveManager::Create(int reserveNum, int reserveGrow)
{
	// make sure values are ressonable 
	assert(reserveNum > 0);
	assert(reserveGrow > 0);

	// initialize the singleton here
	assert(pInstance == nullptr);

	// Do the initialization
	if (pInstance == nullptr)
	{
		pInstance = new WaveManager(reserveNum, reserveGrow);
	}

}

void WaveManager::Destroy()
{

	// Get the instance
	WaveManager* pMan = WaveManager::privGetInstance();
	assert(pMan != nullptr);

	// Clean up what it current owns reserve and active
	pMan->BaseDestroy();

	// bye bye singleton
	delete pMan->pInstance;
}

Wave* WaveManager::Add(const char* const pWaveName, Wave::ID id, FileUserCallback* pFileUserCB)
{
	WaveManager* pMan = WaveManager::privGetInstance();
	assert(pMan != nullptr);

	Wave* pNode = (Wave*)pMan->BaseAdd();
	assert(pNode != nullptr);

	pNode->Set(pWaveName, id, pFileUserCB);

	return pNode;
}

Wave* WaveManager::Find(Wave::ID id)
{
	WaveManager* pMan = WaveManager::privGetInstance();
	assert(pMan != nullptr);

	// Compare functions only compares two Nodes

	// So:  Use the Compare Node - as a reference
	//      use in the Compare() function
	pMan->poNodeCompare->SetId(id);

	Wave* pData = (Wave*)pMan->BaseFind(pMan->poNodeCompare);
	return pData;
}

void WaveManager::Remove(Wave* pNode)
{
	WaveManager* pMan = WaveManager::privGetInstance();
	assert(pMan != nullptr);

	assert(pNode != nullptr);
	pMan->BaseRemove(pNode);
}

void WaveManager::Dump()
{
	WaveManager* pMan = WaveManager::privGetInstance();
	assert(pMan != nullptr);

	pMan->BaseDump();
}

//----------------------------------------------------------------------
// Override Abstract methods
//----------------------------------------------------------------------
DLink* WaveManager::DerivedCreateNode()
{
	DLink* pNode = new Wave();
	assert(pNode != nullptr);

	return pNode;
}

bool WaveManager::DerivedCompare(DLink* pLinkA, DLink* pLinkB)
{
	// This is used in baseFind() 
	assert(pLinkA != nullptr);
	assert(pLinkB != nullptr);

	Wave* pDataA = (Wave*)pLinkA;
	Wave* pDataB = (Wave*)pLinkB;

	bool status = false;

	Wave::ID A;
	Wave::ID B;

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

void WaveManager::DerivedWash(DLink* pLink)
{
	assert(pLink != nullptr);
	Wave* pNode = (Wave*)pLink;
	pNode->Wash();
}

void WaveManager::DerivedDumpNode(DLink* pLink)
{
	assert(pLink != nullptr);
	Wave* pData = (Wave*)pLink;
	pData->Dump();
}

void WaveManager::DerivedDestroyNode(DLink* pLink)
{
	assert(pLink);
	Wave* pData = (Wave*)pLink;
	delete pData;
}


//----------------------------------------------------------------------
// Private methods
//----------------------------------------------------------------------
WaveManager* WaveManager::privGetInstance()
{
	// Safety - this forces users to call Create() first before using class
	assert(pInstance != nullptr);

	return pInstance;
}

// --- End of File ---
