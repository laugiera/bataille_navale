# makefile pour mac de Lou
CFLAGS =-I/Library/Frameworks/SDL.framework/Headers 
LDFLAGS =-framework SDL -framework Cocoa 

ifeq ($(strip $(shell uname -s)),Darwin)
	CFLAGS  += -arch i386
	LDFLAGS  += -arch i386
endif

battleshipMac: main.o init.o /Library/Frameworks/SDL.framework/Headers/SDLmain.m
	gcc -o test_battle main.o init.o /Library/Frameworks/SDL.framework/Headers/SDLmain.m -framework SDL -framework Cocoa -lSDL_TTF -lSDL_image
	#gcc ${LDFLAGS} -o $@ $^

main.o: test_graphique.c test_fct.h /Library/Frameworks/SDL.framework/Headers/SDLmain.m
	gcc -Wall -ansi  -g -c -o $@ $< 

init.o: test_fct.c test_fct.h /Library/Frameworks/SDL.framework/Headers/SDLmain.m
	gcc -Wall -ansi  -g -c -o $@ $< 

#SDLMain.o: /Library/Frameworks/SDL.framework/Headers/SDLmain.m
	#gcc ${LDFLAGS} -g -c -o $@ $< 

#game.o: game.c game.h
#	gcc `sdl-config --cflags --libs` -lSDL_ttf -o game.o -c game.c -Wall -ansi

# the line that worked : gcc -o exe main.o init.o /Library/Frameworks/SDL.framework/Headers/SDLmain.m -framework SDL -framework Cocoa 