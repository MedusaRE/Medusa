#!/bin/sh

FOLDER=$(dirname $(readlink -f $0))

node $FOLDER/badges.js