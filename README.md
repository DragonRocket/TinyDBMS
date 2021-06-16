<!---
	Open this file in Web Browser with Markdown File Extension or MD File Viewer Application to read properly
	Otherwise Summary of this file
	1. Extract the zip
	2. Open terminal in extracted folder
	3. Installation: make
	4. Run:
    $ make run
-->

# TinyDBMS

## ___'You Definately Need Efficient Record Keeper'___
-------------

**Table of Contents**

[TOCM]

[TOC]

## Features
-------------
TinyDBMS with following features
> Search by ID in O(1)
> Search by Title in O(lgn)
> Add Record Feature
> Update Existing Record Feature
> Delete Exisiting Record Feature
> Interactive UI



## Tech
-------------
TinyDBMS is completely written in C++ Language.
It can efficiently search for a Record stored in file and it have Record adding, updating and deletion feature.

## Installation
-------------

TinyDBMS requires [G++](https://gcc.gnu.org/), [GDB](https://www.gnu.org/software/gdb/) and [make](https://www.gnu.org/software/make/) to run.

Install all dependencies before installation

##### Dependencies Installation (for debian based linux)
1. open terminal
2. run the following commands on terminal
```sh
sudo apt update -y
sudo apt upgrade -y
sudo apt install make -y
sudo apt install gdb -y
sudo apt install g++ -y
```

##### TinyDBMS Installation
1. extract the zip
2. open the terminal in the extracted folder
3. run the following command on terminal
 ```sh
make
```


## RUN
-------------

#### Execute either way
Enter following commands on terminal

##### One Way
 ```sh
make run
```
##### Another Way
 ```sh
./bin/main
```

## Additional Command
-------------
- To remove the previous build
```sh
make clean
```

## END
-------------
