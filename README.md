# PLC_Project
## Overview
This project aims to create a game centered around the Pokédex, a text-based system to store and display Pokémon data. Players will be able to go on adventures to discover new Pokémon that they can add to their collection.

## Getting Started

### Clone the Repo

Go to the folder you want to save the project to by using `cd ~/Desktop`

Clone the project using `git clone https://github.com/halanaman/PLC_Project.git`

Open the project folder with `cd PLC_Project`

### Working in branches

Pull updates from main before working on your branch `git pull origin main`

Creating a branch `git checkout -b your-branch-name` or `git switch -c your-branch-name`

Stage a file `git add file.c` or stage all changes in working directory `git add .`

Commit your changes `git commit -m "Your commit message"`

Pushing your branch `git push origin your-branch-name`

### Merging onto main

Switch to the main branch `git checkout main` or `git switch main`

Pull any updates from main `git pull origin main`

Merge your branch onto main `git merge your-branch-name`

Resolve any merge conflicts, if any, then stage the resolved file(s) `git add resolved-file.txt`

Complete the merge `git commit -m "Resolved merge conflicts"`

Push `git push origin main`

## Prerequisites
- Ensure you have `gcc` installed.
- Make sure `make` is installed on your system.

## Compilation
To compile the program, run:
```sh
make
```
This will compile the `main.c` file located in the `src/` directory and generate an executable named `pokedex.exe`

## Compilation without ansi
To compile the progam without ansi, run:
```sh
## comment out this line
# CFLAGS_ANSI = -ansi -pedantic $(CFLAGS)  # CFLAGS with -ansi (default)

## use this line instead
CFLAGS_ANSI = $(CFLAGS)  # CFLAGS without ansi
```

## Clean Up
To remove the compiled executable, run:
```sh
make clean
```
This will delete the `pokedex.exe` file

## File Structure
```css
project-root/
|── data/
│── src/
│   ├── main.c
│── Makefile
│── README.md
```

