#!/usr/bin/env bash

# Usage: ./run_all [Shell package executable path] list.txt


test_files=$(cat $2);


function did_it_work {
    code=$1
    if [ "$code" -ne "0" ]
    then
        echo "Command: $CMD"
        echo "Error failure: code $code"
        exit 1
    fi
}

while IFS= read -r line ; do
	export CMD="$1 -MACHINE_TIME_LIMIT=5 -FILE=sounds/toymusic.mp3 -e tests/$line"
	echo $CMD;
	$CMD
	did_it_work $?
done <<< "$test_files"
