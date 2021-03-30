CC=gcc

compile:
	$(CC) -g -Wall -o mcsim mcsim.c \
		analog_signals.c sampling2.c regfile.c \
		terminal.c interpreter.c

run:
	make compile
	
	## UNIX
	# ./mcsim
	
	## WINDOWS
	mcsim
	