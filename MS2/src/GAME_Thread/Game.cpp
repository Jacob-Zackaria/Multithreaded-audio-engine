//----------------------------------------------------------------------------
// Copyright 2020, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#include "AzulCore.h"
#include "Game.h"
#include "GameApp.h"
#include "InputTest.h"

// Sound stuff.
#include "SndID.h"

// Thread stuff
#include <thread>
#include "ThreadHelper.h"
#include "AudioThread.h"


// Managers
#include "SoundManager.h"
#include "WaveManager.h"
#include "VoiceManager.h"
#include "PlayListManager.h"
#include "TimeEventManager.h"
#include "ASoundManager.h"

// Input.
#include "InputProcess.h"

// File
#include "FileManager.h"
#include "FileMain.h"
//-----------------------------------------------------------------------------
// Game::Game()
//-----------------------------------------------------------------------------
Game::Game() noexcept
{
	// do nothing
}

//-----------------------------------------------------------------------------
// Game::Initialize()
//		Allows the engine to perform any initialization it needs to before 
//      starting to run.  This is where it can query for any required services 
//      and load any non-graphic related content. 
//-----------------------------------------------------------------------------
void Game::Initialize()
{ 
	// Game Window Device setup
	this->setWindowName("Audio Engine");
	this->setWidthHeight(400, 300);
	this->SetClearColor(0.74f, 0.74f, 0.86f, 1.0f);
}

//-----------------------------------------------------------------------------
// Game::LoadContent()
//		Allows you to load all content needed for your engine,
//	    such as objects, graphics, etc.
//-----------------------------------------------------------------------------
void Game::LoadContent()
{	
	// Load up the demo application
	GameApp::LoadDemo(this->getWidth(), this->getHeight());

	// Name the current main thread
	ThreadHelper::SetCurrentThreadName("--- GAME ---");
	ThreadHelper::DebugBegin(0);

	// Initialize the managers.
	SoundManager::Create();
	WaveManager::Create();
	VoiceManager::Create();
	PlayListManager::Create();
	ASoundManager::Create();
	TimeEventManager::Create();


	//---------------------------------------------------------------------------------------------------------
	// Launch audio Thread
	//---------------------------------------------------------------------------------------------------------

	// Create an Audio thread.
	std::thread audioThread(Audio_Main);
	ThreadHelper::SetThreadName(audioThread, "--- AUDIO ---");
	audioThread.detach();

	//---------------------------------------------------------------------------------------------------------
	// Launch the file Thread 
	//---------------------------------------------------------------------------------------------------------

	std::thread  FileThread(FileMain);
	ThreadHelper::SetThreadName(FileThread, "--- FILE ---");
	FileThread.detach();

	// Load audio on file thread.
	//Demo1 Load files
	FileManager::Add("../../MS2_AudioFiles/Fiddle_mono.wav", Wave::ID::Fiddle);
	FileManager::Add("../../MS2_AudioFiles/Bassoon_mono.wav", Wave::ID::Bassoon);
	FileManager::Add("../../MS2_AudioFiles/Oboe2_mono.wav", Wave::ID::Oboe);
	FileManager::Add("../../MS2_AudioFiles/SongA.wav", Wave::ID::SongA);
	FileManager::Add("../../MS2_AudioFiles/SongB.wav", Wave::ID::SongB);

	//Demo2 Load files
	FileManager::Add("../../MS2_AudioFiles/Intro_mono.wav", Wave::ID::Intro_mono);
	FileManager::Add("../../MS2_AudioFiles/A_mono.wav", Wave::ID::A_mono);
	FileManager::Add("../../MS2_AudioFiles/AtoB_mono.wav", Wave::ID::AtoB_mono);
	FileManager::Add("../../MS2_AudioFiles/B_mono.wav", Wave::ID::B_mono);
	FileManager::Add("../../MS2_AudioFiles/BtoC_mono.wav", Wave::ID::BtoC_mono);
	FileManager::Add("../../MS2_AudioFiles/C_mono.wav", Wave::ID::C_mono);
	FileManager::Add("../../MS2_AudioFiles/CtoA_mono.wav", Wave::ID::CtoA_mono);
	FileManager::Add("../../MS2_AudioFiles/End_mono.wav", Wave::ID::End_mono);

	//Demo3 Load files
	FileManager::Add("../../MS2_AudioFiles/Coma_mono.wav", Wave::ID::Coma);

	//Demo4 Load files
	FileManager::Add("../../MS2_AudioFiles/Dial_mono.wav", Wave::ID::Dial);
	FileManager::Add("../../MS2_AudioFiles/MoonPatrol_mono.wav", Wave::ID::MoonPatrol);
	FileManager::Add("../../MS2_AudioFiles/Sequence1_mono.wav", Wave::ID::Sequence);
	FileManager::Add("../../MS2_AudioFiles/Donkey_mono.wav", Wave::ID::Donkey);

	//Demo5 Load files
	FileManager::Add("../../MS2_AudioFiles/Electro_mono.wav", Wave::ID::Electro);
	FileManager::Add("../../MS2_AudioFiles/Alert_mono.wav", Wave::ID::Alarm);
}

//-----------------------------------------------------------------------------
// Game::Update()
//      Called once per frame, update data, tranformations, etc
//      Use this function to control process order
//      Input, AI, Physics, Animation, and Graphics
//-----------------------------------------------------------------------------
void Game::Update()
{
	// Update the demo application
	GameApp::UpdateDemo();
	
	SoundManager::Update();

	this->QuitCheck();

	InputProcess();

}

//-----------------------------------------------------------------------------
// Game::Draw()
//		This function is called once per frame
//	    Use this for draw graphics to the screen.
//      Only do rendering here
//-----------------------------------------------------------------------------
void Game::Draw()
{
	// Draw the demo application
	GameApp::DrawDemo();
}



//-----------------------------------------------------------------------------
// Game::UnLoadContent()
//       unload content (resources loaded above)
//       unload all content that was loaded before the Engine Loop started
//-----------------------------------------------------------------------------
void Game::UnLoadContent()
{
	// Create a Quit command
	SoundManager::Quit(SndID::Quit);
	FileManager::Quit();
	
	// Destroy managers.
	VoiceManager::Destroy();
	WaveManager::Destroy();
	SoundManager::Destroy();
	ASoundManager::Destroy();
	PlayListManager::Destroy();
	TimeEventManager::Destroy();

	ThreadHelper::DebugEnd(0);
}

void Game::QuitCheck()
{
	Keyboard* key = Keyboard::GetInstance();
	assert(key);

	// Read Quit Key
	static bool QuitKey = false;
	if (key != nullptr)
	{
		if (key->GetKeyState(AZUL_KEY::KEY_Q) && !QuitKey)
		{
			// Create a Snd Call
			SoundManager::Quit(SndID::Quit);
			FileManager::Quit();
			QuitKey = true;
		}
	}
}

// End of File 

