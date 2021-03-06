# README Report : Sockets
	[Ethan Ryan Josh]

Assignment 4 (Sockets) as per the assignment requirements

The sockets program contains two executables, a server and
it's associated client. The server and the client communicate
with eachother, sharing map data generated by the previous
assignment's map. 

# Installation

To "install" the project, make sure git is 
installed and clone the repository.

	$git clone https://github.com/elamitie/csi230-a3.git

# Building & Running

The makefile for the sockets project has quite a few different make targets.
To just build the project, there are two targets:

	$make

and

	$make complete

Make complete simply calls the clean-all target before building
the project to prevent having to manually call clean-all everytime 
the project needs to be built.
In order to run the server and client, there is:

   $make run-server
   $make run-client

To track the log files for the server and client, there is:

   $make log-server
   $make log-client

To show the network status of the server to verify it's IP/Port:

   $make check-netstat

Lastly, to run the test program as requested ten times, we have:

   $make test

Obviously, in order for these utility targets to do anything the
project needs to be built first.
Don't forget that in order for the programs to run properly, the
map driver needs to be mounted! As described in the README for 
the driver:

To build the driver:

    $make

To register the driver:

	$make register

To register the driver, you need to have root
priviledges on your system.
Don't forget to mknod the driver, exact instructions are given
upon entering the dmesg command. This is valid:

	$make run-mknod

Clean target to remove everything AND unregister the driver.
If the driver was never registered in the first place, use
$make clean.

# Quirks About the Sockets Implementation

Sometimes there is a bug where the project has to be remade / built
if the client is refused connection to the server for whatever
reason and we haven't been able to track this down yet.
One other bug / non-implemenation (and is a limitation of the
driver less so than a limitation of this specific project) is the
fact that the maps are limited to the original size of 2500 characters
and can't be resized despite the server being able to accept a packet-type
that inlcudes width and height data. This was mostly to prepare for the
future when the driver implementation was fixed; alas, the time didn't
allow for us to go back and do that. Related, we can't test other maps
besides the default. Other than thoes quirks / bugs, everything else has
been implemented to the best of our abilities.
In terms of implementation differences, our data packets are
essentially sent as a string delimited by '~' that get parsed by
the receiving end, whether it's the client or the server. This
allowed us to not need to manually handle `sizeof(char) + sizeof(int)`
instead, we can just get the integers directly into an array who's
contents depend on the amount passed in the packet.
