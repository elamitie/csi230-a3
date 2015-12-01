#!/bin/bash

MAP_WIDTH=10
MAP_HEIGHT=10
MAP_SUCCESS=false
FAILURES=0
declare -A MAP

# Gen map derived from gen_food() in the bash snake game

function gen_map {
	local rand
	for ((i=0; i<MAP_WIDTH * MAP_HEIGHT; i++))
	do
		rand=$[(RANDOM % 2) + 1]
		if [ $rand -eq 1 ] ; then
			MAP[$i]=" ";
		else
			MAP[$i]="x";
		fi

	done
	
	validate_map
}

function validate_map() {
	local spaces=0
	for ((i=0; i<MAP_WIDTH * MAP_HEIGHT; i++))
	do
		blank=" "
		if [ "${MAP[$i]}" == "$blank" ] ; then
			spaces=$((spaces+1))
		fi
	done

	if [ $spaces -gt $(((MAP_WIDTH * MAP_HEIGHT) / 2)) ] ; then
		FAILURES=$((FAILURES+1))
		
		if [ $FAILURES -ge 10 ] ; then
			>&2 echo "Failed validation 10 times, exiting"
			exit 1
		fi

		gen_map
	fi

}

function print_map() {
	for ((i=0; i<MAP_WIDTH * MAP_HEIGHT; i++))
	do
		mod=$[$i % MAP_WIDTH]
		if [ $mod -eq 0 ] ; then
			printf "\n"
		fi

		printf "%s" "${MAP[$i]}"	
	done

	printf "\n"
}

gen_map
print_map
