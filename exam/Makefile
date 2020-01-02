src = $(wildcard *.c) 
obj  = $(src:.c=.o)

FLAGS =  -g -Wall
LDFLAGS = -lm -lpthread -lcrypto -lssl

.PHONY: all

all: server client
	@echo "compiling finished."

client: client.o common.o reentrant.o
	gcc $^ $(LDFLAGS) -o $@
	@echo "client generated"

server: server.o common.o reentrant.o
	gcc $^ $(LDFLAGS) -o $@
	@echo "server generated"

%.o: %.c
	gcc ${FLAGS} -o $@ -c $<

.PHONY: clean 
clean: 
	@echo "Clean"
	rm *.o client server

