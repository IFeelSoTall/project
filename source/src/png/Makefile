DIR:=$(shell pwd)
STR:=$(shell echo $(DIR) | sed 's/src\/png/include\/renderer/')
CFLAGS+=-I$(STR)
LFLAGS+=-L../renderer/
.PHONE : all

all:build
build : 
	gcc main.c -o png.out -lrenderer -lglut -lGLU -lGL -lpng -g $(CFLAGS) $(LFLAGS) -Wl,-rpath=.