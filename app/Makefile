include ../Make.defines

PROGS=test config errtest
BUILD_CFLAGS=-I"../include"
LDFLAGS= -llwzy

all: $(PROGS)

%.o: %.c
	$(CC) -c $(CFLAGS) $(BUILD_CFLAGS) $< -o $@

test:test.o
	$(CC) $^ $(LDDIR) $(LDFLAGS) -o $@

config:config.o
	$(CC) $^ $(LDDIR) $(LDFLAGS) -o $@

errtest:errtest.o
	$(CC) $^ $(LDDIR) $(LDFLAGS) -o $@

clean:
	rm -rf *.o
	rm -f $(PROGS)
