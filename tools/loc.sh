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

REVS=`git rev-list --all --date-order --reverse`

mkdir /tmp/loc_time

DIR=/tmp/loc_time

echo "TIMESTAMP,Lines of Code"

for rev in $REVS; do
	rm -rf /tmp/loc_time
	mkdir /tmp/loc_time
	git archive $rev | tar -C /tmp/loc_time -x
	LOC=`cat /tmp/loc_time/res/badges/loc.svg | grep "lines of code: " | tail -n 1 | cut -d">" -f 2 | cut -d" " -f 4 | cut -d"<" -f 1`
	if [ -z "${LOC}" ]; then
		LOC=`find /tmp/loc_time | cat | xargs cloc --exclude-ext=svg | grep SUM | awk '{ print $NF }'`
	fi
	LOC=${LOC:=0}
	echo `git show -s --format=%cI $rev`','$LOC
done
