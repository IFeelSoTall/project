DIR:=$(shell pwd)
STR:=$(shell echo $(DIR) | sed 's/src/include/')
CFLAGS+=-I$(STR)
.PHONE : all

all:build
build : 
	gcc -c -fPIC renderer.c -o renderer.o $(CFLAGS)
	gcc -shared -o librenderer.so -fPIC renderer.c $(CFLAGS)