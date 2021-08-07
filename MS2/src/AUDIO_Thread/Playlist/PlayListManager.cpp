#include "PlayListManager.h"
#include "VoiceManager.h"
#include "WaveManager.h"


PlayListManager* PlayListManager::pInstance = nullptr;

//---------------------------------------------------------------------------------------------------------
// Design Notes:
//
//  Singleton class - use only public static methods for customers
//
//  * One single compare node is owned by this singleton - used for find, prevent extra news
//  * Create one - NULL Object 
//
//---------------------------------------------------------------------------------------------------------

PlayListManager::PlayListManager(int reserveNum, int reserveGrow)
{
	// At this point Man is created, now initialize the reserve
	this->BaseInitialize(reserveNum, reserveGrow);

	// initialize derived data here
	this->poNodeCompare = new Playlist();
	assert(this->poNodeCompare != nullptr);
}

PlayListManager::~PlayListManager()
{
	// We created it... so we delete it
	delete this->poNodeCompare;
}

//----------------------------------------------------------------------
// Static Methods
//----------------------------------------------------------------------
void PlayListManager::Create(int reserveNum, int reserveGrow)
{
	// make sure values are ressonable 
	assert(reserveNum > 0);
	assert(reserveGrow > 0);

	// initialize the singleton here
	assert(pInstance == nullptr);

	// Do the initialization
	if (pInstance == nullptr)
	{
		pInstance = new PlayListManager(reserveNum, reserveGrow);
	}

}

void PlayListManager::Destroy()
{

	// Get the instance
	PlayListManager* pMan = PlayListManager::privGetInstance();
	assert(pMan != nullptr);

	// Clean up what it current owns reserve and active
	pMan->BaseDestroy();

	// bye bye singleton
	delete pMan->pInstance;
}

Playlist* PlayListManager::Add(SndID snd_id)
{
	PlayListManager* pMan = PlayListManager::privGetInstance();
	assert(pMan != nullptr);

	Playlist* pNode = (Playlist*)pMan->BaseAdd();
	assert(pNode != nullptr);

	// Create a new one given a wash
	switch (snd_id)
	{
	case SndID::Fiddle:
		pNode->Set(snd_id, Voice::ID::Fiddle, Wave::ID::Fiddle);
		break;

	case SndID::Bassoon:
		pNode->Set(snd_id, Voice::ID::Bassoon, Wave::ID::Bassoon);
		break;
	case SndID::Calliope:
		pNode->Set(snd_id, Voice::ID::Calliope, Wave::ID::Calliope);
		break;
	case SndID::Oboe:
		pNode->Set(snd_id, Voice::ID::Oboe, Wave::ID::Oboe);
		break;

	case SndID::SongA:
		pNode->Set(snd_id, Voice::ID::SongA, Wave::ID::SongA);
		break;

	case SndID::SongB:
		pNode->Set(snd_id, Voice::ID::SongB, Wave::ID::SongB);
		break;
	case SndID::Intro_mono:
		pNode->Set(snd_id, Voice::ID::Intro_mono, Wave::ID::Intro_mono);
		break;
	case SndID::SndL:
	case SndID::SndM:
	case SndID::SndN:
	case SndID::SndO:
		pNode->Set(snd_id, Voice::ID::Bassoon, Wave::ID::Bassoon);
		break;
	case SndID::Coma:
		pNode->Set(snd_id, Voice::ID::Coma, Wave::ID::Coma);
		break;
	case SndID::Dial:
		pNode->Set(snd_id, Voice::ID::Dial, Wave::ID::Dial);
		break;

	case SndID::MoonPatrol:
		pNode->Set(snd_id, Voice::ID::MoonPatrol, Wave::ID::MoonPatrol);
		break;

	case SndID::Sequence:
		pNode->Set(snd_id, Voice::ID::Sequence, Wave::ID::Sequence);
		break;

	case SndID::Donkey:
		pNode->Set(snd_id, Voice::ID::Donkey, Wave::ID::Donkey);
		break;
	case SndID::Electro:
		pNode->Set(snd_id, Voice::ID::Electro, Wave::ID::Electro);
		break;
	case SndID::Alarm:
		pNode->Set(snd_id, Voice::ID::Alarm, Wave::ID::Alarm);
		break;
	case SndID::Beethoven:
		pNode->Set(snd_id, Voice::ID::Beethoven, Wave::ID::Beethoven);
		break;
	case SndID::Quit:
		assert(false);
		break;
	}

	return pNode;
}

Playlist* PlayListManager::Find(SndID id)
{
	PlayListManager* pMan = PlayListManager::privGetInstance();
	assert(pMan != nullptr);

	// Compare functions only compares two Nodes

	// So:  Use the Compare Node - as a reference
	//      use in the Compare() function
	pMan->poNodeCompare->SetId(id);

	Playlist* pData = (Playlist*)pMan->BaseFind(pMan->poNodeCompare);
	return pData;
}

void PlayListManager::Remove(Playlist* pNode)
{
	PlayListManager* pMan = PlayListManager::privGetInstance();
	assert(pMan != nullptr);

	assert(pNode != nullptr);
	pMan->BaseRemove(pNode);
}

void PlayListManager::Dump()
{
	PlayListManager* pMan = PlayListManager::privGetInstance();
	assert(pMan != nullptr);

	pMan->BaseDump();
}

//----------------------------------------------------------------------
// Override Abstract methods
//----------------------------------------------------------------------
DLink* PlayListManager::DerivedCreateNode()
{
	DLink* pNode = new Playlist();
	assert(pNode != nullptr);

	return pNode;
}

bool PlayListManager::DerivedCompare(DLink* pLinkA, DLink* pLinkB)
{
	// This is used in baseFind() 
	assert(pLinkA != nullptr);
	assert(pLinkB != nullptr);

	Playlist* pDataA = (Playlist*)pLinkA;
	Playlist* pDataB = (Playlist*)pLinkB;

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

void PlayListManager::DerivedWash(DLink* pLink)
{
	assert(pLink != nullptr);
	Playlist* pNode = (Playlist*)pLink;
	pNode->Wash();
}

void PlayListManager::DerivedDumpNode(DLink* pLink)
{
	assert(pLink != nullptr);
	Playlist* pData = (Playlist*)pLink;
	pData->Dump();
}

void PlayListManager::DerivedDestroyNode(DLink* pLink)
{
	assert(pLink);
	Playlist* pData = (Playlist*)pLink;
	delete pData;
}


//----------------------------------------------------------------------
// Private methods
//----------------------------------------------------------------------
PlayListManager* PlayListManager::privGetInstance()
{
	// Safety - this forces users to call Create() first before using class
	assert(pInstance != nullptr);

	return pInstance;
}

// --- End of File ---