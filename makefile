OBJS = main.o lib_misc.o lib_sdl.o map.o
CC = g++
CFLAGS = -Wall -std=c++0x -static-libgcc -static-libstdc++
LFLAGS = -lmingw32 -lSDLmain -lSDL -lSDL_image -lSDL_mixer

bin/game: ${OBJS}
	${CC} ${CFLAGS} ${OBJS} ${LFLAGS} -o $@

main.o: src/main.cpp src/lib_misc.h src/lib_sdl.h src/constants.h src/map.h
	${CC} ${CFLAGS} -c src/main.cpp

lib_misc.o: src/lib_misc.h src/lib_misc.cpp
	${CC} ${CFLAGS} -c src/lib_misc.cpp

lib_sdl.o: src/lib_sdl.h src/lib_sdl.cpp src/lib_misc.h src/constants.h
	${CC} ${CFLAGS} -c src/lib_sdl.cpp

map.o: src/map.h src/map.cpp src/lib_sdl.h src/lib_misc.h src/constants.h
	${CC} ${CFLAGS} -c src/map.cpp

res/resource.res: res/resource.rc res/icon.ico
	windres $< -O coff -o $@

windows: ${OBJS} res/resource.res
	${CC} ${CFLAGS} ${OBJS} res/resource.res ${LFLAGS} -mwindows -o bin/game.exe

clean:
	rm ${OBJS} res/resource.res bin/game.exe