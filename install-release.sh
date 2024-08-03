#!/bin/bash
set -e

ROOT_DIR=$(pwd)
BUILD_DIR="$ROOT_DIR/build"
RELEASE_DIR="$BUILD_DIR/release"

[ ! -d "$BUILD_DIR" ] && mkdir -p "$BUILD_DIR"
[ ! -d "$RELEASE_DIR" ] && mkdir -p "$RELEASE_DIR"

cd "$RELEASE_DIR"

echo "Installing..."
cmake --install "$RELEASE_DIR"


echo "Done! Your executable is now installed
