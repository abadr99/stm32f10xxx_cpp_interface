
.PHONY: all clean build build-opt style-check 

all:build build-opt style-check

build:
	make -C development build

build-opt:
	make -C development build-opt

style-check:
	@echo "[style-check]: NOT SUPPORTED"

clean:
	@echo "[clean]: NOT SUPPORTED"