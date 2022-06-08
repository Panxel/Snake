CXX = g++
CCFLAGS = -Wall `sdl2-config --cflags`
SRC = main.cpp menu.cpp snake.cpp
OBJ = $(SRC:.cpp=.o)
LIBS = `sdl2-config --libs` -lSDL2_image -lSDL2_ttf
EXEC = prog

all : ${EXEC}

snake.o: snake.h
menu.o: menu.h
main.o: snake.h menu.h

%.o: %.cpp
	$(CXX) -c $< ${CCFLAGS}

${EXEC} : ${OBJ}
	$(CXX) -o $@ $^ ${LIBS}

clean : 
	rm -rf *.o

mrproper : clean
	rm -rf ${EXEC}

	