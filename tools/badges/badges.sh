#!/bin/sh

FOLDER=$(dirname $(readlink -f $0))
cd $FOLDER/../../

node $FOLDER/badges.js