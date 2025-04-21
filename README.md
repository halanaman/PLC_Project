# PokéVenture

## Overview

This project is a text-based Pokémon adventure game written in C. Players can go on adventures, discover new Pokémon and add them to their Pokédex.

## Getting Started

### Pre-requisites
- Ensure you have `gcc` and `make` installed.

### Clone the Repo

Go to the folder you want to save the project, e.g. `cd ~/Desktop/`

Clone the project using `git clone https://github.com/halanaman/PLC_Project.git`

Open the project folder with `cd PLC_Project`

### Compilation
To compile the program, run:
```sh
make
```
This will compile the `main.c` file located in the `src/` directory and generate an executable named `pokeventure`

Launch the program `./pokeventure`

### Compilation Without ANSI
To compile the progam without ansi, edit `Makefile` in the project root folder
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
This will delete the `pokeventure` executable file

## File Structure
```css
project-root/
|── data/
│── src/
│   ├── initialize
│   ├── utils
│   ├── main.c
│── Makefile
│── README.md
```

### Working in branches

Pull updates from main before working on your branch `git pull origin main`

Creating a branch `git checkout -b your-branch-name` or `git switch -c your-branch-name`

Stage a file `git add file.c` or stage all changes in working directory `git add .`

Commit your changes `git commit -m "Your commit message"`

Pushing your branch `git push origin your-branch-name`

### Merging onto main

Switch to the main branch `git checkout main` or `git switch main`

Pull updates from main `git pull origin main`

Merge your branch onto main `git merge your-branch-name`

Resolve any merge conflicts, if any, then stage the resolved file(s) `git add resolved-file.c`

Complete the merge `git commit -m "Resolved merge conflicts"`

Push `git push origin main`

