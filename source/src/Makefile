include $(ROOT_DIR)/build.cfg
dir_y:=
dir_$(CFG_RENDERER_ENABLE)+= renderer
dir_$(CFG_PNG_ENABLE)+= png

.PHONE : all
all:build
build : 
	for i in $(dir_y); do \
		make -C $$i ROOT_DIR=$(ROOT_DIR); \
	done
