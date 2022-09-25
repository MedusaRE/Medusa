#!/bin/sh

if [ $(id -u) != 0 ]; then
    echo "error: this program must be run as root."
    exit -1
fi

apt-get install git libgtkmm-3.0-dev libgtk-3-dev glade gimp texlive python3 python3-pillow nodejs npm
npm install badgen

git submodule init
git submodule update