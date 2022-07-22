#!/bin/sh

if [ $(id -u) != 0 ]; then
    echo "error: this program must be run as root."
    exit -1
fi

pacman -S git gtkmm3 gtk3 glade gimp texlive-most python3 python-pillow node npm
npm install badgen

git submodule init
git submodule update