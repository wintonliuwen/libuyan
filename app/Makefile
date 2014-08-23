include ../Make.defines

PROGS=test
BUILD_CFLAGS=-I"../include"
LDFLAGS= -llwzy

all: $(PROGS)

%.o: %.c
	$(CC) -c -fpic $(CFLAGS) $(BUILD_CFLAGS) $< -o $@

test:test.o
	$(CC) $^ $(LDDIR) $(LDFLAGS) -o $@

install:


clean:
	rm -rf *.o
	rm -f test
