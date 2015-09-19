Introduction
=============

Codes & slides for the presentation done to the 24th performance user group
at Paris the 17/09/2015.

Example - Calculus on simple matrix
====================================

		cd src/02-matrix
		make build
		time valgrind --tool=callgrind --simulate-cache=yes --dump-instr=yes --collect-jumps=yes ./app 100 100

Look at symbol table
======================

		cd src/00-empty
		make build
		readelf -s ./app;
		readelf -s /lib/x86_64-linux-gnu/libc.so.6 | grep malloc

		# Strip effect on the symbol table
		strip ./app
		readelf -s ./app;

Profiling Callgrind
====================

		cd src/02-matrix
		make build

		# Profiling with callgrind for 100 * 100 matrix
		time valgrind --tool=callgrind --simulate-cache=yes --dump-instr=yes --collect-jumps=yes ./app 100 100

		# Perf impact of callgrind
		time ./app 100 100

Thread dump on Native application - Gstack
===========================================

		cd ~/sources/memcached

		sudo -s

Bash function to generate thread dump for native application as you
can do with jstack

		gstack() {
		  tmp=$(tempfile)
		  echo thread apply all bt >"$tmp"
		  gdb -batch -nx -q -x "$tmp" -p "$1"
		  rm -f "$tmp"
		}

Use it

		./memcached &

		while sleep 1; do gstack @pid@ ; done

Perf - Some commands
=====================

Get a list of avaible counters.

    perf list

Get an overview of counters for an application

    perf stat ./app


Perf - Impact on performance
=============================

		time ./app 500 500
		time perf record -g ./app 500 500

Memcached - Symbol table
=========================

		cd ~/sources/memcached
		readelf -s ./memcached

Generate flamegraph from gdb stack
===================================

		cd ~/sources/memcached
		./memcached &

		php src/03-memcache-php/memcache-set.php

		while sleep 0.1; do gstack 8748; done > stack.txt
		cat stack.txt | stackcollapse-gdb.pl | flamegraph.pl > gdb_graph.svg

MEMCACHE - PROFILING WITH PERF
===============================

		cd ~/sources/memcached

		perf record -g ./memcached

		php src/03-memcache-php/memcache-set.php
		perf report

		Warning to /proc/sys/kernel/kptr_restrict

MEMCACHED - PROFILING CPU CYCLE WITH PERF - WITH KERNEL STACKTRACE
===============================

		./memcached &
		sudo perf record -a -g -p @pid@

		php src/03-memcache-php/memcache-set.php
		perf report
