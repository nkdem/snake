#!/bin/sh

set -e

clang main.c -o main -lraylib -L./raylib/src/ -I./raylib/src -framework Cocoa -framework OpenGL -framework IOKit
