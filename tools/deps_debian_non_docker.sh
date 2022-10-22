#!/bin/sh

if [ $(id -u) != 0 ]; then
    echo "error: this program must be run as root."
    exit 1
fi

apt-get update
apt-get -y install texlive
