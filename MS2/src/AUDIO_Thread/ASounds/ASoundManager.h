//----------------------------------------------------------------------------
// Copyright 2020, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#ifndef ASOUND_MANAGER_H
#define ASOUND_MANAGER_H

#include "Manager.h"
#include "SndID.h"
#include "ASounds.h"

// This class is only there for pretty UML
class ASoundMan_Link : public Manager
{
public:
	ASounds_Link* poActive;
	ASounds_Link* poReserve;
};

class ASoundManager : public ASoundMan_Link
{
	//----------------------------------------------------------------------
	// Big four
	//----------------------------------------------------------------------
private:
	ASoundManager(int reserveNum = 3, int reserveGrow = 1);
	ASoundManager(const ASoundManager&) = delete;
	ASoundManager& operator = (const ASoundManager&) = delete;
	ASoundManager() = delete;
	~ASoundManager();

public:

	//----------------------------------------------------------------------
	// Static Methods
	//----------------------------------------------------------------------
	static void Create(int reserveNum = 3, int reserveGrow = 1);
	static void Destroy();

	static ASounds* Add(SndID snd_id);
	static ASounds* Find(SndID id);

	static void  SetQuit();
	static bool  IsQuit();

	static void Remove(ASounds* pNode);
	static void Dump();

	//----------------------------------------------------------------------
	// Override Abstract methods
	//----------------------------------------------------------------------

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
	static ASoundManager* privGetInstance();

	//----------------------------------------------------------------------
	// Data - unique data for this manager 
	//----------------------------------------------------------------------
	static ASoundManager* pInstance;
	ASounds* poNodeCompare;

	bool QuitFlag;
};

#endif

// --- End of File ---
