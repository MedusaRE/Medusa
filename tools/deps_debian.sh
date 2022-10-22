#!/bin/sh

if [ $(id -u) != 0 ]; then
    echo "error: this program must be run as root."
    exit 1
fi

apt-get update
apt-get -y install git libgtkmm-3.0-dev libgtk-3-dev glade gimp python3 python3-pillow nodejs npm doxygen clang-13
npm install badgen

git submodule init
git submodule update