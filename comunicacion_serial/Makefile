# try to do some autodetecting
UNAME := $(shell uname -s)

ifeq "$(UNAME)" "Darwin"
	OS=macosx
endif
ifeq "$(OS)" "Windows_NT"
	OS=windows
endif
ifeq "$(UNAME)" "Linux"
	OS=linux
endif


#################  Common  ##################################################

CFLAGS += $(INCLUDES) -O -Wall -std=gnu99


all: arduino-serial 

arduino-serial: arduino-serial.o arduino-serial-lib.o
	$(CC) $(CFLAGS) -o arduino-serial$(EXE_SUFFIX) arduino-serial.o arduino-serial-lib.o $(LIBS)


.c.o:
	$(CC) $(CFLAGS) -c $*.c -o $*.o


clean:
	rm -f $(OBJ) arduino-serial arduino-serial.exe *.o *.a
	rm -f $(OBJ) arduino-serial-server arduino-serial-server.exe *.o *.a


