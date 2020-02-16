#
# Makefile to build Cg examples for Linux
#
# Author: Alex V. Boreskoff, <steps3d@narod.ru>
#


CC=g++
AL_INC_PATH = /usr/local/include
AL_LIBS     = -ldl -lopenal -lmad -lpthread -logg -lvorbis -lvorbisfile
CFLAGS      = -x c++ -g -I$(AL_INC_PATH) -I$(AL_INC_PATH)/AL -Wall -O3

all: example-1 example-2 example-3 example-4

example-1: example-1.o kbhit.o Vector3D.o 
	$(CC) $(LDFLAGS) example-1.o kbhit.o -o example-1 $(LIBS) $(AL_LIBS) -lc

example-2: example-2.o kbhit.o Vector3D.o 
	$(CC) $(LDFLAGS) example-2.o kbhit.o -o example-2 $(LIBS) $(AL_LIBS) -lc

example-3: example-3.o kbhit.o Vector3D.o OpenAlContext.o Sound.o SoundData.o Data.o
	$(CC) $(LDFLAGS) example-3.o kbhit.o OpenAlContext.o Sound.o SoundData.o Data.o -o example-3 $(LIBS) $(AL_LIBS) -lc

example-4: example-4.o Vector3D.o 
	$(CC) $(LDFLAGS) example-4.o -o example-4 $(LIBS) $(AL_LIBS) -lc

clean:
	rm -r -f example-1 example-2 example-3 example-4 example-1.o example-2.o example-3.o example-4.o OpenAlContext.o Sound.o SoundData.o Data.o Vector3D.o kbhit.o 2> /dev/nul


%.o: %.cpp
	cc $(CFLAGS) $(INCLUDE) -c $<
	
#%.o: %.cpp
#	cc $(CFLAGS) $(INCLUDE) -I$(AL_INC_PATH) -I$(AL_INC_PATH)/AL -c $<
#	
