include ../Make.defines

BUILD_CFLAGS = -I"../include"
DLIB_FLAGS = -fpic -shared
SRC := $(shell find . -name '*.c')
OBJ := $(SRC:%.c=%.o)
TARGET := liblwzy.so


all: build

%.o: %.c
	$(CC) -c -fpic $(CFLAGS) $(BUILD_CFLAGS) $< -o $@

build: $(OBJ)
	$(CC) $(DLIB_FLAGS)  $^ -o $(TARGET)

install:
	cp liblwzy.so /usr/lib/
	cp ../include/*.h /usr/include

clean:
	rm -rf ${OBJ} ${TARGET}
