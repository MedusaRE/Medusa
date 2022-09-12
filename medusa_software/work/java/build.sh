#!/bin/bash

javac src/**.java
mkdir bin
jar cf bin/main.jar src/**.class
