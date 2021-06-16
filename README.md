<!---
	Open this file in Web Browser with Markdown File Extension or MD File Viewer Application to read properly
	Otherwise Summary of this file
	1. Extract the zip
	2. Open terminal in extracted folder
	3. Installation: make
	4. Run:
    $ make run
    or
    $ make run FILE1=pathToFile1 FILE2=pathToFile2
-->

# MatMul

## ___'Bigger Matrices! Not a problem'___
-------------

**Table of Contents**

[TOCM]

[TOC]

## Features
-------------
Matrix Multiplier with following features
> Multithreading Supported
> Multiple Output Choice
> Error Handling
> Efficient



## Tech
-------------
MatMul is completely written in C Language.
It can efficiently multiply two matrices using threads.

## Installation
-------------

MatMul requires [GCC](https://www.gnu.org/software/gcc/), [GDB](https://www.gnu.org/software/gdb/) and [make](https://www.gnu.org/software/make/) to run.

Install all dependencies before installation

##### Dependencies Installation (for debian based linux)
1. open terminal
2. run the following commands on terminal
```sh
sudo apt update -y
sudo apt upgrade -y
sudo apt install make -y
sudo apt install gdb -y
sudo apt install gcc -y
```

##### MatMul Installation
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
make run FILE1=pathToFile1 FILE2=pathToFile2
```
##### Another Way
 ```sh
./bin/main pathToFile1 pathToFile1file2
```

## Additional Command
-------------
- To remove the previous build
```sh
make clean
```

## END
-------------
