#!/bin/bash

# tools/lexicon_wrapper.sh create medusa-re.org TXT "example.example.medusa-re.org" "RDNS_NAME=\"org.medusa-re.example.example\""

lexicon cloudflare $1 $2 $3 --name="$4" --content="$5"