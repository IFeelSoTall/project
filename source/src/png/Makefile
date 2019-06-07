
DIR:=$(shell pwd)
export DIR;
STR:=$(shell echo $(DIR) | sed 's/src/include/')
STR2:=${DIR/src/include}
CFLAGS+=-I$(STR)
.PHONE : all

all:build
build : 
	echo $(DIR)
	echo $(STR)
	echo $(STR2)
	echo $(CFLAGS)
	gcc -c -fPIC renderer.c -o renderer.o $(CFLAGS)
	gcc -shared -o librenderer.so -fPIC renderer.c $(CFLAGS)