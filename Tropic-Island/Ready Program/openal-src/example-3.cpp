//
// Example of using OpenAL wrapper classes
//
// Author: Alex V. Boreskoff <steps3d@narod.ru>, <alexboreskoff@mtu-net.ru>
//

#include	<stdio.h>
#include	<stdlib.h>

#ifndef	_WIN32
    #include	"kbhit.h"
#else
    #include	<windows.h>
    #include	<conio.h>
    #include	<process.h>
    
    #define	initKeyboard()
    #define	closeKeyboard()
#endif

#include	"OpenAlContext.h"
#include	"Sound.h"
#include	"SoundData.h"

int main ()
{
	OpenAlContext	context;
	SoundData     * data = OpenAlContext :: open ( "wavdata/Chi Mai.mp3" );
	
	if ( data == NULL )
		return 1;
		
	initKeyboard ();
	
	Sound * sound = new Sound ( data, true );

	sound -> play ();

	for ( ; ; )
	{
		sound -> update ();
	
		if ( kbhit () )
			break;

											// make some delay
		int	i, j;
		
		for ( i = j = 0; i < 1000; i++ )
		    j += i*j + 1;	    
	}
	
	closeKeyboard ();
	
	return 0;
}
