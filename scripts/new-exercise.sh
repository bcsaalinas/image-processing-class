#!/usr/bin/env bash

set -euo pipefail

if [[ $# -lt 1 || $# -gt 2 ]]; then
    echo "Usage: $0 <exercise-name> [YYYY-MM-DD]" >&2
    exit 2
fi

project_dir="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
exercise_name="$1"
session_date="${2:-$(date +%F)}"

if [[ ! "$exercise_name" =~ ^[a-zA-Z][a-zA-Z0-9_-]*$ ]]; then
    echo "Exercise name must start with a letter and contain only letters, numbers, _ or -." >&2
    exit 2
fi

if [[ ! "$session_date" =~ ^[0-9]{4}-[0-9]{2}-[0-9]{2}$ ]]; then
    echo "Date must use YYYY-MM-DD." >&2
    exit 2
fi

session_dir="$project_dir/sessions/$session_date"
destination="$session_dir/$exercise_name.cpp"

if [[ -e "$destination" ]]; then
    echo "Already exists: $destination" >&2
    exit 1
fi

mkdir -p "$session_dir"
cp "$project_dir/templates/exercise.cpp" "$destination"

# Refresh CMake's target list and compile_commands.json when the project has
# already been set up. This lets VS Code resolve OpenCV includes immediately.
if [[ -d "$project_dir/build/dev" ]]; then
    cmake --preset dev -S "$project_dir" >/dev/null
fi

echo "Created $destination"
echo "Run it with: ./scripts/run.sh sessions/$session_date/$exercise_name.cpp"
