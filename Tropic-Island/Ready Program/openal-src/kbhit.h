//
// kbhit & getche for Linux
//
// Based on code from a book "Beginning Linux Programming", from Wrox Press -- www.wrox.com
//

#ifndef	__KBHIT__
#define	__KBHIT__

void 	initKeyboard  ();				// initialize keyboard for "raw" mode
void 	closeKeyboard ();				// restore keyboard to normal mode
bool 	kbhit         ();				// whether any key has been hit
int		getche        ();				// unbuffered read key with echo

#endif
