//----------------------------------------------------------------------------
// Copyright 2020, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#ifndef FILE_MANAGER_H
#define FILE_MANAGER_H

#include "Handle.h"
#include "Wave.h"
#include "CircularData.h"

class FileUserCallback;

class FileManager
{
public:

	//----------------------------------------------------------------------
	// Big four
	//----------------------------------------------------------------------
private:
	FileManager(const FileManager&) = delete;
	FileManager& operator = (const FileManager&) = delete;
	FileManager();
	~FileManager();

public:

	//----------------------------------------------------------------------
	// Static Methods
	//----------------------------------------------------------------------

	//----------------------------------------------------------------------
	// Need protection... might be executed from different threads
	//----------------------------------------------------------------------
	static Handle::Status Add(const char * const pWaveName, Wave::ID name, FileUserCallback *pFileCB = nullptr);

	//----------------------------------------------------------------------
	// No need for handle protection... the quueue have their own mutex
	//----------------------------------------------------------------------
	static CircularData *GetFileInQueue();
	static Wave::Status GetStatus(Wave::ID id);
	static void SetQuit();
	static bool IsQuit();
	static void Quit();

	//----------------------------------------------------------------------
	// Private methods
	//----------------------------------------------------------------------
private:
	static FileManager*privGetInstance();

	//----------------------------------------------------------------------
	// Data - unique data for this manager 
	//----------------------------------------------------------------------

	CircularData *poFileInQueue;   // File in
	bool QuitFlag;
	Handle		  handle;
};


#endif

// --- End of File ---
