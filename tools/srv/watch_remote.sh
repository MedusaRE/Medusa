#!/bin/bash

function check_if_behind() {
	git remote update
	current_status=$(git status -uno)
	if [[ "${current_status}" == *"behind"* ]]; then
		return 0
	fi

	return 1
}

MEDUSA_PATH=$(dirname $0)/../..

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