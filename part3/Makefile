####
#
# Makefile
#
# Main makefile to build: - The Micro Time Server
#                         - The Snoop Server
#
# Serguei A. Mokhov
#
##

# Compiler and its options
CC=gcc
DEBUG=-g #-D_DEBUG
#LOG=-D_PRINT -D_LOG -D_ELOG -D_OLOG
#ISO=-ansi -pedantic
CC_OPTIONS=-Wall -Wmissing-prototypes -Wmissing-declarations $(ISO) $(DEBUG)

# Where to look for header files and libraries
INC=-I. -I$(COMMON) -I$(IPC) -I../server -I../client -I$(UTIL) -I$(TTY)
LIBDIRS=-L$(IPC) -L$(TTY)

# Executables and object files
# EXE=mtimesrv snoopsrv
# OBJ=server.o mtimesrv.o snoopsrv.o
# LIBIPC=libipc.a
# LIBTTY=libtty.a

EXE=mapserver mapclient
OBJ=mapserver.o mapclient.o

all: $(EXE)
	@echo ""
	@echo "Client and Server Built"
	@echo ""

mapserver.o: mapserver.h mapserver.c common.h
	$(CC) $(CC_OPTIONS) -c mapserver.c

mapclient.o: mapclient.h mapclient.c common.h
	$(CC) $(CC_OPTIONS) -c mapclient.c

mapserver: mapserver.o
	$(CC) mapserver.o -o mapserver

mapclient: mapclient.o
	$(CC) mapclient.o -o mapclient

complete:
	make clean-all
	make

run:
	@make all

log:
	@echo "TODO: make log"

debug:
	@echo "TODO: make debug"

clean:
	rm -f $(EXE) $(OBJ)

clean-all:
	make clean

# EOF