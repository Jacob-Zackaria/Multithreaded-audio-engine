#ifndef DEMO1D_4_H
#define DEMO1D_4_H

#include "Command.h"
#include "SoundManager.h"

class Demo1D_4 : public Command
{
public:
	Demo1D_4() = default;
	~Demo1D_4() = default;
	Demo1D_4(const Demo1D_4&) = delete;
	Demo1D_4& operator = (const Demo1D_4&) = delete;

	// Behold the demo
	virtual void Execute() override
	{
		// Create a Snd Call
		Sounds* pSndA = SoundManager::Find(SndID::SongA);
		assert(pSndA);

		Trace::out("\n104 - Stop SongA: (60 sec)\n");
		Trace::out(" Vol : 0.7f | Pan : Left |\n Pitch : 1.0f | Priority : 200 |\n");
		

		Trace::out("\n104 - SongA PlaybackTime: (60 sec)\n");
		Trace::out(" Vol : 0.7f | Pan : Left |\n Pitch : 1.0f | Priority : 200 |\n");

		int playTime;
		pSndA->GetTimeInMS(playTime);
		Trace::out("Playback Time: %ds %dms\n", (playTime / 1000), (playTime % 1000));
		pSndA->Stop();
	}
};


#endif