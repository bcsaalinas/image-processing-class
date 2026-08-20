#!/usr/bin/env bash

set -euo pipefail

if [[ $# -ne 1 ]]; then
    echo "Usage: $0 sessions/<YYYY-MM-DD>/<exercise>.cpp" >&2
    exit 2
fi

project_dir="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
requested_source="$1"
source_file="$project_dir/${requested_source#./}"

if [[ ! -f "$source_file" ]]; then
    echo "Exercise not found: $requested_source" >&2
    exit 1
fi

relative_source="${source_file#"$project_dir/sessions/"}"
session_date="$(dirname "$relative_source")"
exercise_name="$(basename "$relative_source" .cpp)"

if [[ "$relative_source" == "$source_file" || "$session_date" == "." ]]; then
    echo "Exercise must be under sessions/<YYYY-MM-DD>/." >&2
    exit 2
fi

target_name="exercise_${session_date}_${exercise_name}"
target_name="${target_name//[^a-zA-Z0-9_]/_}"
binary_name="${session_date}_${exercise_name}"
binary_name="${binary_name//\//_}"

cmake --preset dev -S "$project_dir"
cmake --build --preset dev --target "$target_name"
"$project_dir/build/dev/bin/$binary_name"
