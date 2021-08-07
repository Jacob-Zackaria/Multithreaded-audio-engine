#include "SoundPriorityEntry.h"

SoundPriorityEntry::SoundPriorityEntry()
{
	this->Clear();
}

void SoundPriorityEntry::Clear()
{
	this->priority = -1;
	this->sndID = SndID::Uninitialized;
	this->handleID = 0;
	this->startTime = Time(Duration::TIME_ZERO);
}