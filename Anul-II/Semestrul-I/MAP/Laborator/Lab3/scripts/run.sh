#!/bin/sh
set -eu
cd "$(dirname "$0")/.."
mkdir -p out
find src -name '*.java' -print > out/sources.txt
javac -encoding UTF-8 --release 11 -d out @out/sources.txt
cp src/main/resources/config.properties out/config.properties
java -cp out Main
