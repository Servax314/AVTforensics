CC = gcc
FLAGS = -lm
DIRS := analysis\
		debug\
		vm

SRCS := $(wildcard $(addsuffix /*.c,$(DIRS)))
#SRCS := $(notdir $(SRCS))
$(info SRCS=$(SRCS))
OBJ := $(SRCS:%.c=%.o)
BIN := $(notdir $(SRCS:%.c=%))
$(info BIN=$(BIN))
BUILD_DIR := ./build

all: main

main: ${OBJ}
	
	${CC} -o main main.c $(BUILD_DIR)/*.o

${OBJ}: $(BUILD_DIR)

$(BUILD_DIR):
	mkdir $(BUILD_DIR)

%.o: %.c
	${CC} -c $< 
	mv $(notdir $@) $(BUILD_DIR)


clean:
	rm -f $(BUILD_DIR)/*.o
	rm -f main


.PHONY = all clean