#ifndef WAVE_MANAGER_H
#define WAVE_MANAGER_H

#include "Manager.h"
#include "Wave.h"

// This class is only there for pretty UML
class WaveMan_Link : public Manager
{
public:
	Wave_Link* poActive;
	Wave_Link* poReserve;
};

class WaveManager : public WaveMan_Link
{
private:
	WaveManager() = delete;
	WaveManager(const WaveManager&) = delete;
	const WaveManager& operator = (const WaveManager&) = delete;
	~WaveManager();
	WaveManager(int reserveNum = 3, int reserveGrow = 1);

public:

	//----------------------------------------------------------------------
	// Static Methods
	//----------------------------------------------------------------------

	static void Create(int reserveNum = 3, int reserveGrow = 1);
	static void Destroy();

	static Wave* Add(const char* const pWaveName, Wave::ID id, FileUserCallback* pFileUserCB = nullptr);
	static Wave* Find(Wave::ID id);

	static void Remove(Wave* pNode);
	static void Dump();

protected:
	virtual DLink* DerivedCreateNode() override;
	virtual bool DerivedCompare(DLink* pLinkA, DLink* pLinkB) override;
	virtual void DerivedWash(DLink* pLink) override;
	virtual void DerivedDumpNode(DLink* pLink) override;
	virtual void DerivedDestroyNode(DLink* pLink) override;

private:

	static WaveManager* privGetInstance();

	//----------------------------------------------------------------------
	// Data - unique data for this manager 
	//----------------------------------------------------------------------
	static WaveManager* pInstance;
	Wave* poNodeCompare;
};

#endif