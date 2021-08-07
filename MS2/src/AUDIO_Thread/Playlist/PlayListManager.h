#ifndef PLAYLIST_MANAGER_H
#define PLAYLIST_MANAGER_H

#include "Manager.h"
#include "Voice.h"
#include "Playlist.h"

// This class is only there for pretty UML
class PlaylistMan_Link : public Manager
{
public:
	Playlist_Link* poActive;
	Playlist_Link* poReserve;
};

class PlayListManager : public PlaylistMan_Link
{
	//----------------------------------------------------------------------
	// Big four
	//----------------------------------------------------------------------
private:
	PlayListManager(int reserveNum = 3, int reserveGrow = 1);
	PlayListManager(const PlayListManager&) = delete;
	PlayListManager& operator = (const PlayListManager&) = delete;
	PlayListManager() = delete;
	~PlayListManager();

public:

	//----------------------------------------------------------------------
	// Static Methods
	//----------------------------------------------------------------------
	static void Create(int reserveNum = 3, int reserveGrow = 1);
	static void Destroy();

	static Playlist* Add(SndID snd_id);
	static Playlist* Find(SndID id);

	static void Remove(Playlist* pNode);
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
	static PlayListManager* privGetInstance();

	//----------------------------------------------------------------------
	// Data - unique data for this manager 
	//----------------------------------------------------------------------
	static PlayListManager* pInstance;
	Playlist* poNodeCompare;
};

#endif

// --- End of File ---