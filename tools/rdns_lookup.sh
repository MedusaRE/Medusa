#!/bin/bash

MEDUSA_PATH=$(dirname $(realpath $0))/..
RDNS=$($MEDUSA_PATH/tools/rdns.sh $1)

# first, try the actual DNS we were passed (if it is actual DNS)
HOST_OUTPUT=$(host -t txt $RDNS 2>/dev/null)

# next, try reading the val we were passed + /res/rdns.txt, i.e.
# medusa_software/vienna would read medusa_software/vienna/res/rdns.txt, the
# "standard" path for the rDNS value
if [ $? -ne 0 ]; then
	RDNS=$($MEDUSA_PATH/tools/rdns.sh $(cat $1/res/rdns.txt 2>/dev/null) 2>/dev/null)
	HOST_OUTPUT=$(host -t txt $RDNS 2>/dev/null)
fi

# finally, try just reading the val we were passed, like if someone passed the
# path to rdns.txt directly
if [ $? -ne 0 ]; then
	RDNS=$($MEDUSA_PATH/tools/rdns.sh $(cat $1))
	HOST_OUTPUT=$(host -t txt $RDNS)
fi

OUT_CUT=$(echo "$HOST_OUTPUT" | cut -d " " -f 4-)
OUT_CHOPPED=$(echo $OUT_CUT | tail -c +2 | head -c -2)
OUT_PROC=$(eval printf '%s\\n' "$OUT_CHOPPED")

echo $OUT_PROC