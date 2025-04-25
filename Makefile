# Create a Makefile that will compile the program

BlackJack: main.o player.o table.o
	gcc main.o player.o table.o -o BlackJack

# Make targets for the individual files, seperating the compilation from the linking

main.o: main.c player.h table.h
	gcc main.c -c -o main.o

player.o: player.c player.h
	gcc player.c -c -o player.o


table.o: table.c table.h player.h
	gcc table.c -c -o table.o

# TODO: finish this target so that it removes the executable 
# and any other files that were created when the program was compiled
clean:
	rm *.o 
	rm BlackJack