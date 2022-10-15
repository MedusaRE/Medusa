#!/bin/bash

MEDUSA_PATH=$(dirname $(realpath $0))/..
RDNS=$($MEDUSA_PATH/tools/rdns.sh $1)

HOST_OUTPUT=$(host -t txt $RDNS)
OUT_CUT=$(echo "$HOST_OUTPUT" | cut -d " " -f 4-)
OUT_CHOPPED=$(echo $OUT_CUT | tail -c +2 | head -c -2)
OUT_PROC=$(eval printf '%s\\n' "$OUT_CHOPPED")

echo $OUT_PROC