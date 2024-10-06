#!/bin/sh

YELLOW='\033[1;33m'
NC='\033[0m' # No Color

echo "${YELLOW}[CPP-CHECK] Static Analysis for dev directory${NC}"
cppcheck ./dev/ --enable=all --std=c++17  --suppress=missingInclude -i dev/mcal/src/stm32f103_startup.cpp --check-config

echo "${YELLOW}[CPP-CHECK] Static Analysis for tests directory${NC}"
cppcheck ./tests/ --enable=all --std=c++17  --suppress=missingInclude --check-config