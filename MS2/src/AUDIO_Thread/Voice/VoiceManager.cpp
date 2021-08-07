#include "VoiceManager.h"
#include "WaveManager.h"

VoiceManager* VoiceManager::pInstance = nullptr;

//---------------------------------------------------------------------------------------------------------
// Design Notes:
//
//  Singleton class - use only public static methods for customers
//
//  * One single compare node is owned by this singleton - used for find, prevent extra news
//  * Create one - NULL Object 
//
//---------------------------------------------------------------------------------------------------------

VoiceManager::VoiceManager(int reserveNum, int reserveGrow)
{
	// At this point Man is created, now initialize the reserve
	this->BaseInitialize(reserveNum, reserveGrow);

	// initialize derived data here
	this->poNodeCompare = new Voice();
	assert(this->poNodeCompare != nullptr);
}

VoiceManager::~VoiceManager()
{
	// We created it... so we delete it
	delete this->poNodeCompare;

}

//----------------------------------------------------------------------
// Static Methods
//----------------------------------------------------------------------
void VoiceManager::Create(int reserveNum, int reserveGrow)
{
	// make sure values are ressonable 
	assert(reserveNum > 0);
	assert(reserveGrow > 0);

	// initialize the singleton here
	assert(pInstance == nullptr);

	// Do the initialization
	if (pInstance == nullptr)
	{
		pInstance = new VoiceManager(reserveNum, reserveGrow);
	}

}

void VoiceManager::Destroy()
{

	// Get the instance
	VoiceManager* pMan = VoiceManager::privGetInstance();
	assert(pMan != nullptr);

	// Clean up what it current owns reserve and active
	pMan->BaseDestroy();

	// bye bye singleton
	delete pMan->pInstance;
}

Voice* VoiceManager::Add(Voice::ID voice_id, Wave::ID wave_id)
{
	VoiceManager* pMan = VoiceManager::privGetInstance();
	assert(pMan);

	Wave* pWave = WaveManager::Find(wave_id);
	assert(pWave);

	Voice* pNode = (Voice*)pMan->BaseAdd();
	assert(pNode != nullptr);

	pNode->Set(voice_id, pWave);

	return pNode;
}

Voice* VoiceManager::Find(Voice::ID id)
{
	VoiceManager* pMan = VoiceManager::privGetInstance();
	assert(pMan != nullptr);

	// Compare functions only compares two Nodes

	// So:  Use the Compare Node - as a reference
	//      use in the Compare() function
	pMan->poNodeCompare->SetId(id);

	Voice* pData = (Voice*)pMan->BaseFind(pMan->poNodeCompare);
	return pData;
}

void VoiceManager::Remove(Voice* pNode)
{
	VoiceManager* pMan = VoiceManager::privGetInstance();
	assert(pMan != nullptr);

	assert(pNode != nullptr);
	pMan->BaseRemove(pNode);
}

void VoiceManager::Dump()
{
	VoiceManager* pMan = VoiceManager::privGetInstance();
	assert(pMan != nullptr);

	pMan->BaseDump();
}

//----------------------------------------------------------------------
// Override Abstract methods
//----------------------------------------------------------------------
DLink* VoiceManager::DerivedCreateNode()
{
	DLink* pNode = new Voice();
	assert(pNode != nullptr);

	return pNode;
}

bool VoiceManager::DerivedCompare(DLink* pLinkA, DLink* pLinkB)
{
	// This is used in baseFind() 
	assert(pLinkA != nullptr);
	assert(pLinkB != nullptr);

	Voice* pDataA = (Voice*)pLinkA;
	Voice* pDataB = (Voice*)pLinkB;

	bool status = false;

	Voice::ID A;
	Voice::ID B;

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

void VoiceManager::DerivedWash(DLink* pLink)
{
	assert(pLink != nullptr);
	Voice* pNode = (Voice*)pLink;
	pNode->Wash();
}

void VoiceManager::DerivedDumpNode(DLink* pLink)
{
	assert(pLink != nullptr);
	Voice* pData = (Voice*)pLink;
	pData->Dump();
}

void VoiceManager::DerivedDestroyNode(DLink* pLink)
{
	assert(pLink);
	Voice* pData = (Voice*)pLink;
	delete pData;
}


//----------------------------------------------------------------------
// Private methods
//----------------------------------------------------------------------
VoiceManager* VoiceManager::privGetInstance()
{
	// Safety - this forces users to call Create() first before using class
	assert(pInstance != nullptr);

	return pInstance;
}

// --- End of File ---