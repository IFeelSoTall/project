
#.PHONE : all

#all:main

#main:main.c renderer.c
#	gcc main.c renderer.c -lglut -lGLU -lGL -lpng -g

#clean : a.out
#	rm -f a.out
#include Makefile.param
#ROOT_DIR
export ROOT_DIR:=$(shell pwd)/build;
#echo "$(ROOT_DIR)";
#$(yes);
.PHONE : all
all:clean build

clean :
	rm -rf build/

build : source/
	echo $(ROOT_DIR)
	mkdir build
	cp source/* build/ -r
	make -C build ROOT_DIR=$(ROOT_DIR)
	
	
	
