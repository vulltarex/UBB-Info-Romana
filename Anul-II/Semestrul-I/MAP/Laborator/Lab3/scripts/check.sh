#!/bin/sh
set -eu
cd "$(dirname "$0")/.."
PROJECT_DIR=$(pwd)
CHECK_DIR=$(mktemp -d "${TMPDIR:-/tmp}/social-network-check.XXXXXX")
trap 'rm -rf "$CHECK_DIR"' EXIT HUP INT TERM
find "$PROJECT_DIR/src" "$PROJECT_DIR/test" -name '*.java' -print | while IFS= read -r source; do
    printf '"%s"\n' "$source"
done > "$CHECK_DIR/sources.txt"
mkdir -p "$CHECK_DIR/classes"
javac -encoding UTF-8 --release 11 -d "$CHECK_DIR/classes" @"$CHECK_DIR/sources.txt"
cp src/main/resources/config.properties "$CHECK_DIR/classes/config.properties"
cd "$CHECK_DIR"
java -cp "$CHECK_DIR/classes" Lab3Tests
