//
// Example of using OpenAL - check supported extensions
//
// Author: Alex V. Boreskoff <steps3d@narod.ru>, <alexboreskoff@mtu-net.ru>
//

#include	<stdlib.h>
#include	<stdio.h>
#include	<time.h>

#include	<al.h>
#include	<alc.h>


int main ( int argc, char  * argv [] )
{
	ALCdevice * device = alcOpenDevice ( NULL );

	if ( device == NULL )
	{
		printf ( "Error opening default device\n" );

		exit ( 1 );
	}

	ALCcontext * context = alcCreateContext ( device, NULL );

	if ( context == NULL )
	{
		printf ( "Error creating context\n" );

		exit ( 1 );
	}

	alcMakeContextCurrent ( context );

	const char * str = (const char *) alcGetString ( device, ALC_EXTENSIONS );

	if ( str != NULL )
		printf ( "Extensions:\n%s\n", str );
	else
	    printf ( "No extension found\n" );

	
	alcMakeContextCurrent ( NULL    );
	alcDestroyContext     ( context );
	alcCloseDevice        ( device  );

	return 0;
}
