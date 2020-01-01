src = $(wildcard *.c) 
obj  = $(src:.c=.o)

FLAGS =  -g -Wall
LDFLAGS = -lm -lpthread -lcrypt -lssl

.PHONY: all

all: $(obj) 
	@echo "compiling"
	gcc $< $(LDFLAGS) -o $@

%.o: %.c
	gcc ${FLAGS} -o $@ -c $<

.PHONY: clean 
clean: 
	@echo "Clean"
	rm *.o

