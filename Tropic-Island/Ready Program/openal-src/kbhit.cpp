//
// kbhit & getche for Linux
//
// Based on code from a book "Beginning Linux Programming", from Wrox Press -- www.wrox.com
//

#include <termios.h>
#include <unistd.h>
#include <stdio.h>

static struct termios initialSettings, newSettings;
static int 			  peekCharacter = -1;

void initKeyboard ()
{
    tcgetattr ( 0, &initialSettings );
    
    newSettings              = initialSettings;
    newSettings.c_lflag     &= ~ICANON;
    newSettings.c_lflag     &= ~ECHO;
    newSettings.c_lflag     &= ~ISIG;
    newSettings.c_cc [VMIN]  = 1;
    newSettings.c_cc [VTIME] = 0;
    
    tcsetattr ( 0, TCSANOW, &newSettings );
}

void closeKeyboard ()
{
    tcsetattr (0, TCSANOW, &initialSettings );
}

bool kbhit()
{
	char ch;
	int	 n;

    if ( peekCharacter != -1 )
    	return true;
    	
    newSettings.c_cc [VMIN] = 0;
    
    tcsetattr ( 0, TCSANOW, &newSettings );
    
    n = read ( 0, &ch, 1 );
    
    newSettings.c_cc [VMIN] = 1;
    
    tcsetattr ( 0, TCSANOW, &newSettings );
    
    if ( n < 1 )
    	return false;
    	
    peekCharacter = ch;
        
    return true;
}

int getche ()
{
	char ch;

    if ( peekCharacter != -1 )
    {
        ch            = peekCharacter;
        peekCharacter = -1;
        
        return ch;
    }
    
    read ( 0, &ch, 1 );
    
    putchar ( ch );
    
    return ch;
}
