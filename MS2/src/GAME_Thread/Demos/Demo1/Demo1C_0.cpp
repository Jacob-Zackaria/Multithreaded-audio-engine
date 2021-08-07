#include "Demo1C_0.h"

// Thread stuff
#include "ThreadHelper.h"

// Timer
#include "Timer.h"

// Launch point for thread
void Demo1C_0_Main(Sounds* pSnd)
{
	assert(pSnd);

	Handle::Status status;
	Timer timer;
	float delta;
	float vol;
	int TimeElapsed_ms;

	delta = 1.0f / 1000.0f;

	// Start the timer
	timer.tic();

	// Get the current time
	TimeElapsed_ms = Time::quotient(timer.toc(), Time(Duration::TIME_ONE_MILLISECOND));

	// Loop for 2 seconds
	while (TimeElapsed_ms < 2000)
	{
		pSnd->GetVol(vol);

		// Set panning	
		vol += delta;
		status = pSnd->SetVol(vol);

		if (status != Handle::Status::SUCCESS)
		{
			assert(false);
		}

		// update every 1 ms
		std::this_thread::sleep_for(std::chrono::microseconds(1000));

		// Update time
		TimeElapsed_ms = Time::quotient(timer.toc(), Time(Duration::TIME_ONE_MILLISECOND));
	}
}