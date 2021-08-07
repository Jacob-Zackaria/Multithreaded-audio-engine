#ifndef VOICE_MANAGER_H
#define VOICE_MANAGER_H

#include "Manager.h"
#include "Voice.h"

class VoiceMan_Link : public Manager
{
public:
	Voice_Link* poActive;
	Voice_Link* poReserve;
};

class VoiceManager : public VoiceMan_Link
{
	//----------------------------------------------------------------------
	// Big four
	//----------------------------------------------------------------------
private:
	VoiceManager(int reserveNum = 3, int reserveGrow = 1);
	VoiceManager(const VoiceManager&) = delete;
	VoiceManager& operator = (const VoiceManager&) = delete;
	VoiceManager() = delete;
	~VoiceManager();

public:

	//----------------------------------------------------------------------
	// Static Methods
	//----------------------------------------------------------------------
	static void Create(int reserveNum = 3, int reserveGrow = 1);
	static void Destroy();

	static Voice* Add(Voice::ID voice_id, Wave::ID wave_id);
	static Voice* Find(Voice::ID name);

	static void Remove(Voice* pNode);
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
	static VoiceManager* privGetInstance();

	//----------------------------------------------------------------------
	// Data - unique data for this manager 
	//----------------------------------------------------------------------
	static VoiceManager* pInstance;
	Voice* poNodeCompare;
};

#endif

// --- End of File ---
