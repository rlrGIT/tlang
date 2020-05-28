#!/bin/bash

# A Humble HERA Simulator Stimulator V.4-20.46
# Author: Russell Rivera HC'20

# Usage: For compiling tiger directly into HERA, then running that HERA on the simulator
# This script deletes .hera files, but will keep an input files with the -f option. 

print_usage() {
	printf "Usage: sh run_hera.sh -f <filename.tig> or sh run_hera.sh -i <enter> for user input.\n"
}

# get user input in the form of tiger, produce a file for your compiler, run it on HERA-C-Simulator
interpret_input() {
	echo "Welcome to the HERA Simulator Stimulator! V.4-20.69\n"	
	echo "Please enter some tiger input - be sure to add <EOF>:\n" 

	# read into input file
	read tiger
	echo $tiger > tiger.tig

	# debugger toggling
	while true ; do
    		read -p "Do you want to activate the debugger? [y/n]" yn
    		case $yn in
      		  	[Yy]*) Debug/tiger -dA tiger.tig > target.hera; break ;;
       			[Nn]*) Debug/tiger tiger.tig > target.hera; break ;;
        		    *) echo "Please answer yes or no." ;;
   		esac
	done

	# run the code
	cat target.hera
	HERA-C-Run target.hera
	rm target.hera
	rm tiger.tig
}

use_file() {

	# debugger toggling
	while true ; do
    		read -p "Do you want to activate the debugger? [y/n]" yn
    		case $yn in
      		  	[Yy]*) Debug/tiger -dA $1 > target.hera; break ;;
       			[Nn]*) Debug/tiger $1 > target.hera; break ;;
        		    *) echo "Please answer yes or no." ;;
   		esac
	done

	cat target.hera
	HERA-C-Run target.hera
	rm target.hera
	rm tiger.tig
}

print_usage
# important for control flow do not remove
echo "beep boop beep boop\n"

# check flags
while getopts 'if:v' flag; do
	case "${flag}" in
		i) interpret_input
			exit 1 ;;
		f) use_file $OPTARG 
			exit 1 ;;
		v) verbose=true ;;
		*) print_usage
			exit 1 ;;
	esac
done
exit 1
