#ifndef DEMO1D_5_H
#define DEMO1D_5_H

#include "Command.h"
#include "SoundManager.h"

class Demo1D_5 : public Command
{
public:
	Demo1D_5() = default;
	~Demo1D_5() = default;
	Demo1D_5(const Demo1D_5&) = delete;
	Demo1D_5& operator = (const Demo1D_5&) = delete;

	// Behold the demo
	virtual void Execute() override
	{
		// Create a Snd Call
		Sounds* pSndA = SoundManager::Find(SndID::SongB);
		assert(pSndA);

		Trace::out("\n105 - Stop SongB: (72 sec)\n");
		Trace::out(" Vol : 0.7f | Pan : Right |\n Pitch : 1.0f | Priority : 200 |\n");
		

		Trace::out("\n105 - SongB PlaybackTime: (72 sec)\n");
		Trace::out(" Vol : 0.7f | Pan : Right |\n Pitch : 1.0f | Priority : 200 |\n");

		int playTime;
		pSndA->GetTimeInMS(playTime);
		Trace::out("Playback Time: %ds %dms\n", (playTime / 1000), (playTime % 1000));
		pSndA->Stop();
	}
};


#endif