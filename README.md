# Embedded System Simulator [![Build Status](https://travis-ci.org/ichpuchtli/ESS.png?branch=master)](https://travis-ci.org/ichpuchtli/ESS)

An Embedded System Simulator for Students at the University of Queensland.

## Installation

### Ubuntu

Dependencies:

    $ sudo add-apt-repository ppa:ubuntu-sdk-team/ppa
    $ sudo apt-get update
    $ sudo apt-get install ubuntu-sdk elfutils libelf-dev gcc-avr binutils-avr avr-libc gdb-avr

Building:

    $ git submodule init
    $ git submodule update
    $ make -C include/simavr
    $ ...
    $ qmake
    $ make

### Arch Linux

Dependencies:

    $ pacman -Syu qt5-base elfutils avr-binutils avr-gcc avr-gdb avr-libc

Building:

    $ git submodule init
    $ git submodule update
    $ make -C include/simavr
    $ ...
    $ qmake
    $ make

### Windows
  TODO

### Mac OSX
  TODO

##LICENSE
GPL v3
