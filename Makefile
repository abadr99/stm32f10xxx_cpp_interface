
.PHONY: all clean build build-opt style-check 

all:build build-opt style-check

cpplint:
	make -C dev cpplint
build:
	make -C dev build

build-opt:
	make -C dev build-opt

style-check:
	@echo "[style-check]: NOT SUPPORTED"

clean:
	@echo "[clean]: NOT SUPPORTED"