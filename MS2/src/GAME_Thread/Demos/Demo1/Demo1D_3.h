#ifndef DEMO1D_3_H
#define DEMO1D_3_H

#include "Command.h"
#include "SoundManager.h"

class Demo1D_3 : public Command
{
public:
	Demo1D_3() = default;
	~Demo1D_3() = default;
	Demo1D_3(const Demo1D_3&) = delete;
	Demo1D_3& operator = (const Demo1D_3&) = delete;

	// Behold the demo
	virtual void Execute() override
	{
		Trace::out("\n104 - SongA PlaybackTime: (38 sec)\n");
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