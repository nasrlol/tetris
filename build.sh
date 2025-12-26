
#!/bin/sh
set -e

CC=cc
SRC=tetris.c
OUT=app

CFLAGS_COMMON="
-std=c11
-Wall -Wextra -Wpedantic
-I/usr/include
"

CFLAGS_DEBUG="
-g
-O0
-fno-omit-frame-pointer
"

CFLAGS_RELEASE="
-O2
-march=native
"

LDFLAGS="
-lraylib
-lGL
-lm
-lpthread
-ldl
-lX11
"

$CC $CFLAGS_COMMON $CFLAGS_DEBUG $SRC -o $OUT $LDFLAGS
./app
