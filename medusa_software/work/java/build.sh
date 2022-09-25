#!/bin/bash

shopt -s globstar

find . -name "*.java" -type f > sources.txt
javac -cp . @sources.txt
mkdir bin
jar cmvf META-INF/MANIFEST.MF bin/main.jar **/*.class

