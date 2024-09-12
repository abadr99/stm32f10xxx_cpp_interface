#!/bin/sh

echo "[CPP-CHECK] Static Analysis for dev directory"
cppcheck ./dev/ --enable=all --std=c++17  --suppress=missingInclude -i dev/mcal/src/stm32f103_startup.cpp --check-config

echo "[CPP-CHECK] Static Analysis for tests directory"
cppcheck ./tests/ --enable=all --std=c++17  --suppress=missingInclude --check-config