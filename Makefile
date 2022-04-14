OBJS = main.cpp src/*.cpp
CC = clang++
INCLUDE_PATHS = -Iinclude -Iinclude/headers
LIBRARY_PATHS = -Llib
COMPILER_FLAGS = -std=c++17 -Wall -O2
# COMPILER_FLAGS = -std=c++17
LINKER_FLAGS = -lSDL2 -lSDL2_image -lSDL2_mixer
EXECUTABLE_NAME = pong

all:
	$(CC) ${COMPILER_FLAGS} ${LINKER_FLAGS} ${INCLUDE_PATHS} ${LIBRARY_PATHS} ${OBJS} -o ${EXECUTABLE_NAME}
