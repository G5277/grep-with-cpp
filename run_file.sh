#!/bin/sh
#
# Script to compile and run the program locally.
#

set -e  # Exit immediately if any command fails

# Navigate to the script's directory
cd "$(dirname "$0")"

# Compile the project using CMake
cmake -B build -S . -DCMAKE_TOOLCHAIN_FILE=${VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake
cmake --build build --config Debug  # Ensure Debug mode build

# Ensure the executable exists before running
EXECUTABLE="./build/Debug/exe.exe"  # Corrected path

if [ ! -f "$EXECUTABLE" ]; then
  echo "Error: Executable not found at $EXECUTABLE"
  exit 1
fi

# Run the compiled program with any arguments passed to this script
exec "$EXECUTABLE" "$@"
