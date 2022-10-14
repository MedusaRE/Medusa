#!/bin/bash

ARG=$1
SPLIT_ARG=${1//./ }

REVERSED_SPLIT=$(for i in $SPLIT_ARG; do echo $i; done | tac)
RDNS_NAME=$(printf ".%s" ${REVERSED_SPLIT[@]})
RDNS_NAME=${RDNS_NAME:1}

echo $RDNS_NAME
