include ../Make.defines

BUILD_CFLAGS = -I"../include"
DLIB_FLAGS = -fpic -shared
SRC := $(shell find . -name '*.c')
OBJ := $(SRC:%.c=%.o)
TARGET := liblwzy.so


all: build install

%.o: %.c
	$(CC) -c -fpic $(CFLAGS) $(BUILD_CFLAGS) $< -o $@

build: $(OBJ)
	$(CC) $(DLIB_FLAGS) $(BUILD_LDFLAGS) $^ -o $(TARGET)

install:


clean:
	rm -rf ${OBJ} ${TARGET}
