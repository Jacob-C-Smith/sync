#
# Sync Makefile
#
# @file Makefile
#
# @author Jacob Smith
#
PROJECT_NAME = sync

CC = gcc
AS = nasm
DISABLE = #TIMER MUTEX SPINLOCK READ_WRITE_LOCK SEMAPHORE CONDITION_VARIABLE MONITOR BARRIER

CC_FLAGS = -g -fPIC -I $(INCLUDE_DIRECTORY) $(DEFINES) -Wall -Wextra -Wpointer-arith -Wstrict-prototypes -Wformat-security -Wfloat-equal -Wshadow -Wconversion -pthread -lpthread -Wlogical-not-parentheses -Wnull-dereference
LD_FLAGS = -g

INCLUDE_DIRECTORY = $(shell pwd)/include
LIBRARY_DIRECTORY = $(shell pwd)/lib
BUILD_DIRECTORY   = $(shell pwd)/build

LIBRARY_SOURCES = sync.c 
EXAMPLE_SOURCES = main.c

DEFINES = -D_GNU_SOURCE $(addprefix -DSYNC_BUILD_NO_,$(DISABLE))

.PHONY : clean sync log all sync sync_example sync_example_run 

.SUFFIXES:
%.o: %.c; $(CC) -o $(BUILD_DIRECTORY)/$@ -c $< $(CC_FLAGS)
%.i: %.c; $(CC) -I $(CC_FLAGS) -o $(BUILD_DIRECTORY)/$@ -E $< 
%.s: %.c; $(CC) -I $(CC_FLAGS) -o $(BUILD_DIRECTORY)/$@ -S $<

all: dependencies sync
	
sync: sync.o 
	$(CC) -L $(LIBRARY_DIRECTORY) -Wl,-rpath=$(LIBRARY_DIRECTORY) $(CC_FLAGS) $(DEFINES) -I $(INCLUDE_DIRECTORY) -shared -o $(LIBRARY_DIRECTORY)/lib$@.so $(BUILD_DIRECTORY)/$^ -llog

sync_example: ./main.o 
	$(CC) -L $(LIBRARY_DIRECTORY) -Wl,-rpath=$(LIBRARY_DIRECTORY) $(CC_FLAGS) $(DEFINES) -I $(INCLUDE_DIRECTORY) -o $(BUILD_DIRECTORY)/$@ $(BUILD_DIRECTORY)/$^ -llog -lsync 

dependencies: clean_symlinks
	CWD=$(pwd)/extern ln -s $(shell pwd)/extern/log/include/log -t $(INCLUDE_DIRECTORY) log 2>/dev/null & 
	make -C extern/log LIBRARY_DIRECTORY=$(LIBRARY_DIRECTORY) BUILD_DIRECTORY=$(BUILD_DIRECTORY) INCLUDE_DIRECTORY=$(INCLUDE_DIRECTORY)

sync_example_run: sync_example
	$(BUILD_DIRECTORY)/$^

clean: clean_symlinks
	rm -rf *.o $(LIBRARY_DIRECTORY)/* $(BUILD_DIRECTORY)/*

clean_symlinks:
	rm -f include/log