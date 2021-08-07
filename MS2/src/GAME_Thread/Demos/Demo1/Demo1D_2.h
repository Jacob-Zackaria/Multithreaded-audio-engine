#ifndef DEMO1D_2_H
#define DEMO1D_2_H

#include "Command.h"
#include "SoundManager.h"

class Demo1D_2 : public Command
{
public:
	Demo1D_2() = default;
	~Demo1D_2() = default;
	Demo1D_2(const Demo1D_2&) = delete;
	Demo1D_2& operator = (const Demo1D_2&) = delete;

	// Behold the demo
	virtual void Execute() override
	{
		Trace::out("\n104 - SongA PlaybackTime: (35 sec)\n");
		Trace::out(" Vol : 0.7f | Pan : Left |\n Pitch : 1.0f | Priority : 200 |\n");

		// Create a Snd Call
		Sounds* pSndA = SoundManager::Find(SndID::SongA);
		assert(pSndA);

		int playTime;
		pSndA->GetTimeInMS(playTime);
		Trace::out("Playback Time: %ds %dms\n", (playTime / 1000), (playTime % 1000));
	}
};


#endif