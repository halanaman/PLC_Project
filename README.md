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

Creating a branch `git checkout -b your-branch-name`

Pushing your branch `git push origin your-branch-name`


## Prerequisites
- Ensure you have `gcc` installed.
- Make sure `make` is installed on your system.

## Compilation
To compile the program, run:
```sh
make
```
This will compile the `main.c` file located in the `src/` directory and generate an executable named `program`

## Clean Up
To remove the compiled executable, run:
```sh
make clean
```
This will delete the `program` file

## File Structure
```css
project-root/
|── data/
│── src/
│   ├── main.c
│── Makefile
│── README.md
```

