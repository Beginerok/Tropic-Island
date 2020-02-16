//
// Example of using OpenAL - moving source of sound
//
// Author: Alex V. Boreskoff <steps3d@narod.ru>, <alexboreskoff@mtu-net.ru>
//

#include	<stdlib.h>
#include	<stdio.h>
#include	<time.h>

#include	<al.h>
#include	<alc.h>
#include	<alut.h>

#include	"Vector3D.h"

#ifndef	_WIN32
    #include	"kbhit.h"
#else
    #include	<conio.h>
    
    #define	initKeyboard()
    #define	closeKeyboard()
#endif

ALuint buffer;										// buffer for sound data
ALuint source;										// source of sound


Vector3D	sourcePos ( 0, 0, 2 );					// source position
Vector3D	sourceVel ( 0, 0, 0 );					// source velocity (used for doppler effect)


Vector3D	listenerPos ( 0, 0, 0 );				// listeners position
Vector3D	listenerVel ( 0, 0, 0 );				// listern's velocity

													// listeners orientation (forward, up)
float 		listenerOri [] = { 0, 0, -1,  0, 1, 0 };

bool	setupSource ( char * fileName )
{
	ALenum		format;
	ALsizei		size;
	ALvoid    * data;
	ALsizei 	freq;
	ALboolean	loop;

	alGenBuffers ( 1, &buffer );					// create buffer

	if ( alGetError () != AL_NO_ERROR )
		return false;

													// load .wav data using alut
	alutLoadWAVFile ( (ALbyte *)fileName, &format, &data, &size, &freq, &loop );
	alBufferData    ( buffer, format, data, size, freq );
	alutUnloadWAV   ( format, data, size, freq );

	alGenSources ( 1, &source );					// create source

	if ( alGetError () != AL_NO_ERROR )
		return false;
													// setup source params
	alSourcei  ( source, AL_BUFFER,   buffer    );
	alSourcef  ( source, AL_PITCH,    1.0f      );
	alSourcef  ( source, AL_GAIN,     1.0f      );
	alSourcefv ( source, AL_POSITION, sourcePos );
	alSourcefv ( source, AL_VELOCITY, sourceVel );
	alSourcei  ( source, AL_LOOPING,  AL_TRUE    );

	return true;
}

int main ( int argc, char  * argv [] )
{
	initKeyboard ();
	alutInit     ( NULL, 0 );					// initialize OpenAL and clear the error bit.
	alGetError   ();

	char * fileName = argv [1];
	
	if ( argc < 2 )
		fileName = "wavdata/Footsteps.wav";
		
	if ( !setupSource ( fileName ) )			// load the wav data.
	{
	    printf ( "Error loading data \"%s\"\n.", fileName );

		return 0;
	}

	alListenerfv ( AL_POSITION,    listenerPos );
	alListenerfv ( AL_VELOCITY,    listenerVel );
	alListenerfv ( AL_ORIENTATION, listenerOri );

	printf ( "Press q to quit\n" );
	
	alSourcePlay ( source );

	while ( !kbhit () )
	{
		float	secs = clock () / CLOCKS_PER_SEC;

		sourcePos.x = 5*sin(secs*0.3);
		sourcePos.z = 5*sin(secs*0.3);

		alSourcefv ( source, AL_POSITION, sourcePos );
	}

	getche ();

	alDeleteBuffers ( 1, &buffer );
	alDeleteSources ( 1, &source );
	alutExit        ();
	closeKeyboard   ();
	
	return 0;
}

