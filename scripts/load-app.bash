#!/bin/bash

app_name=$1

if [ -z "$1" ]; then
	app_name='showdown_app.elf'
	echo "No app name provided, defaulting to $app_name"
fi

dir_script="$( cd "$( dirname "${BASH_SOURCE[0]}" )" &> /dev/null && pwd )"
dir_bin="$dir_script"/../bin/

openocd -f interface/picoprobe.cfg -f target/rp2040.cfg -c "program $dir_bin/$app_name verify reset exit"
