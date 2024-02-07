#!/bin/bash

set -xe

mkdir -p build

gcc -Wall -Wextra -o build/main src/main.c src/crymath.c