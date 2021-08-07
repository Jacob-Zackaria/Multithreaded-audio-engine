
//----------------------------------------------------------------------------
// Copyright 2020, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#ifndef SOUND_MANAGER_H
#define SOUND_MANAGER_H

#include "CircularData.h"
#include "Manager.h"
#include "Sounds.h"
#include "UserCallBack.h"
// This class is only there for pretty UML
class SoundMan_Link : public Manager
{
public:
	Sounds_Link* poActive;
	Sounds_Link* poReserve;
};

class SoundManager : public SoundMan_Link
{

private: 

	SoundManager(int reserveNum = 3, int reserveGrow = 1) noexcept;
	SoundManager() = delete;
	SoundManager(const SoundManager&) = delete;
	SoundManager& operator = (const SoundManager&) = delete;
	~SoundManager();

public:

	// Public methods:
	static void Create(int reserveNum = 3, int reserveGrow = 1) noexcept;
	static void Destroy() noexcept;
	static void Update();
	static Sounds* Add(SndID snd_id, UserCallback* pCallback = nullptr, SoundPriority snd_priority = 0);
	static Sounds* Find(SndID snd_id);
	static Sounds* FindWithHandle(unsigned int sndHandle_id);
	static void Quit(SndID snd_id);

	static void Remove(Sounds* pNode);
	static void Dump();

	static CircularData* GetG2A() noexcept;
	static CircularData* GetA2G() noexcept;

protected:

	virtual DLink* DerivedCreateNode() override;
	virtual bool DerivedCompare(DLink* pLinkA, DLink* pLinkB) override;
	virtual void DerivedWash(DLink* pLink) override;
	virtual void DerivedDumpNode(DLink* pLink) override;
	virtual void DerivedDestroyNode(DLink* pLink) override;


private:
	static SoundManager* GetPrivateInstance() noexcept;

	static SoundManager* poInstance;
	Sounds* poNodeCompare;

	CircularData* pG2A;  // Game to Audio
	CircularData* pA2G; // Audio to Game
};

#endif


// End of File 
