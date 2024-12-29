#
# Log Makefile
#
# @file Makefile
#
# @author Jacob Smith
#
PROJECT_NAME = sync

CC = gcc
AS = nasm
DISABLE = #TIMER MUTEX SPINLOCK RW_LOCK SEMAPHORE CONDITION_VARIABLE MONITOR BARRIER

CC_FLAGS = -fPIC -I$(INCLUDE_DIRECTORY) $(DEFINES) -Wall -Wextra -Wpointer-arith -Wstrict-prototypes -Wformat-security -Wfloat-equal -Wshadow -Wconversion -pthread -lpthread -Wlogical-not-parentheses -Wnull-dereference
LD_FLAGS = -g

INCLUDE_DIRECTORY = $(shell pwd)/include
LIBRARY_DIRECTORY = $(shell pwd)/lib
BUILD_DIRECTORY   = $(shell pwd)/build

LIBRARY_SOURCES = sync.c 
EXAMPLE_SOURCES = main.c

DEFINES = -D_GNU_SOURCE $(addprefix -DSYNC_BUILD_NO_,$(DISABLE))

.PHONY : clean all sync_example_run

.SUFFIXES:
%.o: %.c; $(CC) -o $(BUILD_DIRECTORY)/$@ -c $< $(CC_FLAGS)
%.i: %.c; $(CC) -I $(CC_FLAGS) -o $(BUILD_DIRECTORY)/$@ -E $< 
%.s: %.c; $(CC) -I $(CC_FLAGS) -o $(BUILD_DIRECTORY)/$@ -S $<

all: dependencies sync example
	#      >>>> SYNC ALL <<<<

dependencies:
	#      >>>> SYNC DEPENDENCIES <<<<
	ln -s ../extern/log/include/log -t include log & 2>/dev/null
	make -C extern/log INCLUDE_DIRECTORY=$(INCLUDE_DIRECTORY) LIBRARY_DIRECTORY=$(LIBRARY_DIRECTORY) BUILD_DIRECTORY=$(BUILD_DIRECTORY)

sync: sync.o
	#      >>>> SYNC LIB <<<<

	$(CC) $(CC_FLAGS) $(DEFINES) -I$(INCLUDE_DIRECTORY) -shared -o "$(LIBRARY_DIRECTORY)/lib$@.so" $(BUILD_DIRECTORY)/$^

example: ./main.o
	#      >>>> SYNC EXAMPLE <<<<

	$(CC) -L$(LIBRARY_DIRECTORY) -Wl,-rpath=$(LIBRARY_DIRECTORY) $(CC_FLAGS) $(DEFINES) -o "$(BUILD_DIRECTORY)/$(PROJECT_NAME)_$@" $(BUILD_DIRECTORY)/$^ -lsync -llog

clean:
	#      >>>> CLEAN <<<<
	rm -rf *.o $(LIBRARY_DIRECTORY)/* $(BUILD_DIRECTORY)/*
