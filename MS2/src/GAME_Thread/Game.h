//----------------------------------------------------------------------------
// Copyright 2020, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#ifndef GAME_H
#define GAME_H

#include "AzulCore.h"

class Game: public Engine
{
public:
	// constructor
	Game() noexcept;
	Game(const Game&) = delete;
	Game(Game&&) = delete;
	Game& operator = (const Game&) = delete;
	Game& operator = (Game&&) = delete;
	~Game() = default;

	// Methods Users need to overloade in their game
    virtual void Initialize();
    virtual void LoadContent();
	virtual void Update();
    virtual void Draw();
    virtual void UnLoadContent();

	void QuitCheck();

private:	
	// legacy
	Game( const char* windowName, const int Width,const int Height);


};

#endif

// End of File 
