#!/bin/bash
#
#  Copyright (C) 2023, w212 research. <contact@w212research.com>
#
#  This program is free software; you can redistribute it and/or modify it
#  under the terms of version 2 of the GNU General Public License as
#  published by the Free Software Foundation.
#
#  This program is distributed in the hope that it will be useful,
#  but WITHOUT ANY WARRANTY; without even the implied warranty of
#  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#  GNU General Public License for more details.
#
#  You should have received a copy of the GNU General Public License along
#  with this program; if not, write to the Free Software Foundation, Inc.,
#  51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
#

RDNS_OF_ARG1=$($MEDUSA_PATH/tools/rdns.sh $1)
lexicon cloudflare delete $MEDUSA_DOMAIN TXT --name="$RDNS_OF_ARG1"
lexicon cloudflare create $MEDUSA_DOMAIN TXT --name="$RDNS_OF_ARG1" --content="RDNS_NAME=\"$1\" PROJECT_DIR=\"$2\" PROJECT_DESC=\"$3\""