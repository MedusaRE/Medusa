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

shopt -s globstar

if [ -z "${MEDUSA_PATH}" ]; then
	source $(realpath $(dirname $0))/source_env.sh
fi

cd $MEDUSA_PATH

for file in medusa_software/**/*.{cpp,cc,c,h,hh,hpp}; do
	if (echo $file | grep -q submodules); then
		continue
	fi
	echo formatting: $file
	clang-format -i $file
done
