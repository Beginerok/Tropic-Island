APP=Demo
CPP=g++
SRC=Game.cpp Scene1.cpp main.cpp
FLAGS=-I. -IIL -lGL -lSDL2 -lcurl -lssl -lIL -lILU -lGLU -lm

run:clean all
	./$(APP)

all:$(APP)

$(APP):
	$(CPP) $(SRC) $(FLAGS) -o $(APP)

clean:
	rm $(APP)

depends:
	sudo apt install    \
	libssl-dev          \
	libsdl2-dev         \
	libdevil-dev        \
	libopenal-dev       \
	libgl1-mesa-dev     \
	libglu1-mesa-dev    \
	libcurl4-openssl-dev 
