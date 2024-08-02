#!/bin/bash
set -e

ROOT_DIR=$(pwd)
BUILD_DIR="$ROOT_DIR/build"
RELEASE_DIR="$BUILD_DIR/release"

[ ! -d "$BUILD_DIR" ] && mkdir -p "$BUILD_DIR"
[ ! -d "$RELEASE_DIR" ] && mkdir -p "$RELEASE_DIR"

cd "$RELEASE_DIR"

echo "Running CMake"
cmake -S "$ROOT_DIR" -G "Unix Makefiles" -DCMAKE_BUILD_TYPE="Release" -B "$RELEASE_DIR" "$@"

echo "Building..."
cmake --build "$RELEASE_DIR" --parallel


echo "Running CPack"
cpack
echo "Done! Your executable is in $RELEASE_DIR"
