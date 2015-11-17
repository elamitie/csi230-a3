# README Report
	[Ethan Ryan Josh]

Assignment 3 as per the assignment requirements

The shell script uses a function based on the food generation
of Housenka, the bash game to generate a random map of ascii
characters, in this case it is filled with blanks and the x
character.

The C Driver starts as a static map of our initials in ascii
art, and the driver lets the user call the read(), write(),
open(), close(), and lseek() system calls to modify the map,
which is 50 x 50 characters.

# Installation

To "install" the project, make sure git is 
installed and clone the repository.

	$git clone https://github.com/elamitie/csi230-a3.git

# Building & Running [Shell Script]

Shell script:
	
	$./genmap.sh

If the shell script doesn't have permissions:

	$chmod u+x ./genmap.sh

# Building & Running [C Driver]

To build the project:

	$make

To register the driver:

	$make register

To register the driver, you need to have root
priviledges on your system.

To run the program:

	$./mapdriver-test

Command line arguments are optional and are as follows:

	1.) [String to write to driver]
	2.) [Position to seek to before writing]

# Makefile Specifics

The Makefile associated with this project has some targets
to make building and testing easier.

	$make seek-out-of-bounds

This target sets up a test application where the program
seeks to a position out of bounds of the map, and writes
a string to wherever the default position is, in this case
it should be the beginning of the map.

	$make run

Just a simple target to combine make, make register, and
./mapdriver-test into one command. Make sure you are root
before executing!

	$make run-mknod

Useful for first time running after booting up the system.
Otherwise for subsequent runs, use $make run.

	$make clean-all

Clean target to remove everything AND unregister the driver.
If the driver was never registered in the first place, use
$make clean.
