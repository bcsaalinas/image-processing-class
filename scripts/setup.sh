#!/usr/bin/env bash

set -euo pipefail

project_dir="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"

opencv_formula=""
if command -v brew >/dev/null 2>&1; then
    opencv_formula="$(brew list --versions opencv 2>/dev/null || true)"
fi

if ! command -v cmake >/dev/null 2>&1 || [[ "$opencv_formula" != opencv\ 5.* ]]; then
    if ! command -v brew >/dev/null 2>&1; then
        echo "Homebrew is required to install CMake and OpenCV: https://brew.sh" >&2
        exit 1
    fi
    echo "Installing missing development dependencies..."
    brew bundle --file "$project_dir/Brewfile"
fi

cmake --preset dev -S "$project_dir"
cmake --build --preset dev

echo
echo "Setup complete. Try:"
echo "  ./scripts/run.sh sessions/2026-08-19/opencv_basics.cpp"
