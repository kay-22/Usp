CC = gcc
CXX = g++

RELEASE = -DNDEBUG
DEBUG =# -g
SDL_FLAGS = -lmingw32 -lSDL2main -lSDL2 
COMP_FLAGS = -std=c++11 -Wall -Werror -pedantic-errors ${DEBUG} ${RELEASE}

EXEC = usp

OBJS = main.o

#				need to figure out how make makefile work outside bin
${EXEC}: ${OBJS}
	${CXX} ${SDL_FLAGS} ${COMP_FLAGS} -o $@ ${OBJS}

main.o: ..\main.cpp
	${CXX} -c ${COMP_FLAGS} ..\$*.cpp

clean:
	rm -f ${OBJS} ${EXEC}.exe