#!/bin/sh

pacman -S git gtkmm3 gtk3 glade gimp texlive-most python3 python-pillow node npm
npm install badgen

git submodule init
git submodule update