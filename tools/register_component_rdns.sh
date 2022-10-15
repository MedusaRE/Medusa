#!/bin/bash

RDNS_OF_ARG1=$($MEDUSA_PATH/tools/rdns.sh $1)
lexicon cloudflare delete $MEDUSA_DOMAIN TXT --name="$RDNS_OF_ARG1"
lexicon cloudflare create $MEDUSA_DOMAIN TXT --name="$RDNS_OF_ARG1" --content="RDNS_NAME=\"$1\" PROJECT_DIR=\"$2\" PROJECT_DESC=\"$3\""