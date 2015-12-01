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

log-server:
	tail -f server_log.txt

log-client:
	tail -f client_log.txt

run-client:
	./mapclient

run-server:
	./mapserver

check-netstat:
	netstat -lpt | grep "23032"

debug:
	@echo "TODO: make debug"

test:
	./mapclient
	./mapclient
	./mapclient
	./mapclient
	./mapclient
	./mapclient
	./mapclient
	./mapclient
	./mapclient
	./mapclient
clean:
	rm -f $(EXE) $(OBJ)
	rm -f server_log.txt
	rm -f client_log.txt
	touch server_log.txt
	touch client_log.txt

clean-all:
	make clean

# EOF
