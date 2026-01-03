#!/bin/bash

# Generates code coverage HTML

# Usage: ./coverage.sh [build-directory]
# Script will attempt to locate build-directory if not provided

set -e

# Use build directory if specified.
if [ -n "$1" ]; then
    BUILD_DIR="$1"
    if [ ! -d "$BUILD_DIR" ]; then
        echo "Error: Build directory '$BUILD_DIR' does not exist"
        exit 1
    fi
else
    # Auto-detect build directory by looking for CMakeCache.txt
    # Use the most recently modified build (the one you just ran tests on)

    # Find all CMakeCache.txt files and sort by modification time (newest first)
    NEWEST_CACHE=$(ls -t build/CMakeCache.txt build/*/CMakeCache.txt 2>/dev/null | head -1)

	# Make sure we have our build directory.
    if [ -n "$NEWEST_CACHE" ] && [ -f "$NEWEST_CACHE" ]; then
        BUILD_DIR=$(dirname "$NEWEST_CACHE")
    else
        echo "Error: Could not find build directory"
        echo "Try running from the project root, or specify build directory:"
        echo "  ./coverage.sh <build-directory>"
        exit 1
    fi
fi

# Verify this is a CMake build directory
if [ ! -f "$BUILD_DIR/CMakeCache.txt" ]; then
    echo "Error: '$BUILD_DIR' does not appear to be a CMake build directory"
    exit 1
fi

echo "Using build directory: $BUILD_DIR"
echo "Generating coverage report..."

cmake --build "$BUILD_DIR" --target coverage-html
