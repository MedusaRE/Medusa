#!/bin/bash
#
#  Copyright (C) 2022, w212 research. <contact@w212research.com>
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

function check_if_behind() {
	git remote update
	current_status=$(git status -uno)
	if [[ "${current_status}" == *"behind"* ]]; then
		return 0
	fi

	return 1
}

MEDUSA_PATH=$(dirname $0)/../..
cd $MEDUSA_PATH

while true; do
	if check_if_behind; then
		echo "Copying."
		git pull
		cp -R $MEDUSA_PATH/www/* /var/www
	else
		echo "Up to date."
	fi

	sleep 180
done