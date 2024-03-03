
.PHONY: all clean build build-opt cpplint

all:build build-opt cpplint

cpplint:
	make -C dev   cpplint
	make -C tests cpplint

build:
	make -C dev build

build-opt:
	make -C dev build-opt

build-unittests:
	make -C tests build-unittests

run-unittests:
	make -C tests run-unittests

clean:
	@echo "[clean]: NOT SUPPORTED"