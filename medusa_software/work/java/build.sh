#!/bin/bash

shopt -s globstar

javac -cp . -cp org **/*.java
mkdir bin
jar cmvf META-INF/MANIFEST.MF bin/main.jar **/*.class

