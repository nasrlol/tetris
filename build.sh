
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

build_debug() {
    $CC $CFLAGS_COMMON $CFLAGS_DEBUG $SRC -o $OUT $LDFLAGS
}

build_release() {
    $CC $CFLAGS_COMMON $CFLAGS_RELEASE $SRC -o $OUT $LDFLAGS
}

case "$1" in
    debug)   build_debug ;;
    release) build_release ;;
    *)
        echo "usage: $0 [debug|release]"
        exit 1
        ;;
esac
