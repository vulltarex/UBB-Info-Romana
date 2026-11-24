#!/bin/sh
set -eu
cd "$(dirname "$0")/.."
mkdir -p docs/javadoc
find src -name '*.java' -print > docs/javadoc/sources.txt
javadoc -quiet -Werror -encoding UTF-8 -docencoding UTF-8 -charset UTF-8 \
    -Xdoclint:all -d docs/javadoc @docs/javadoc/sources.txt
