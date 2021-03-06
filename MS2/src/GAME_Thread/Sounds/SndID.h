#ifndef SND_ID_H
#define SND_ID_H

enum class SndID
{
	Fiddle = 101,
	Bassoon = 102,
	Oboe = 103,
	SongA = 104,
	SongB = 105,

	SndL = 120,
	SndM = 130,
	SndN = 140,
	SndO = 150,
	Calliope = 113,
	Coma = 301,
	Dial = 401,
	MoonPatrol = 402,
	Sequence = 403,
	Donkey = 404,
	Electro = 501,
	Alarm = 502,
	Beethoven = 503,
	Intro_mono = 110,

	Quit,

	Uninitialized = 0x7FFF0000
};

#endif