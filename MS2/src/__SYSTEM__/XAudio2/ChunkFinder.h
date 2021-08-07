//This class contains functions to find and read chunks from the audio file.

#ifndef CHUNKFINDER_H
#define CHUNKFINDER_H

#include "File_Slow.h"

// Define FOURCC.
#ifdef _XBOX //Big-Endian
#define fourccRIFF 'RIFF'
#define fourccDATA 'data'
#define fourccFMT 'fmt '
#define fourccWAVE 'WAVE'
#define fourccXWMA 'XWMA'
#define fourccDPDS 'dpds'
#endif

#ifndef _XBOX //Little-Endian
#define fourccRIFF 'FFIR'
#define fourccDATA 'atad'
#define fourccFMT ' tmf'
#define fourccWAVE 'EVAW'
#define fourccXWMA 'AMWX'
#define fourccDPDS 'sdpd'
#endif

enum ChunkError
{
	CHUNK_SUCCESS = 0xC0000000,
	CHUNK_FAIL,

};

ChunkError FindChunk(File_Slow::Handle hFile, DWORD fourcc, DWORD& dwChunkSize, DWORD& dwChunkDataPosition);
ChunkError ReadChunkData(File_Slow::Handle hFile, void* buffer, DWORD buffersize, DWORD bufferoffset);


#endif
