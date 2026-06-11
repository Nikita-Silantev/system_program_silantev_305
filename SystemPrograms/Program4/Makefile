CC      = gcc
CFLAGS  = -Wall -Wextra

UNAME := $(shell uname)
ifeq ($(UNAME), Darwin)
	SHARED_FLAGS = -dynamiclib
	PLUGIN_EXT   = dylib
	DL_FLAGS     =
else
	SHARED_FLAGS = -shared -fPIC
	PLUGIN_EXT   = so
	DL_FLAGS     = -ldl
endif

PLUGIN = libplugin.$(PLUGIN_EXT)
SHARED = libdatastruct.$(PLUGIN_EXT)

all: program4_static program4_dynamic $(PLUGIN)

datastruct.o: datastruct.c datastruct.h
	$(CC) $(CFLAGS) -fPIC -c datastruct.c -o datastruct.o

libdatastruct.a: datastruct.o
	ar rcs libdatastruct.a datastruct.o

$(SHARED): datastruct.o
	$(CC) $(SHARED_FLAGS) datastruct.o -o $(SHARED)

$(PLUGIN): plugin.c
	$(CC) $(SHARED_FLAGS) plugin.c -o $(PLUGIN)

program4_static: main.c libdatastruct.a $(PLUGIN)
	$(CC) $(CFLAGS) main.c libdatastruct.a $(DL_FLAGS) -DPLUGIN_FILE='"$(PLUGIN)"' -o program4_static

program4_dynamic: main.c $(SHARED) $(PLUGIN)
	$(CC) $(CFLAGS) main.c -L. -ldatastruct $(DL_FLAGS) -DPLUGIN_FILE='"$(PLUGIN)"' -o program4_dynamic

clean:
	rm -f *.o *.a *.so *.dylib program4_static program4_dynamic
