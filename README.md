# Assembler

This assembler program translates instructions into binary machine code and then into unique base 15 code.

## General Info

Final project of the course 'Systems programming laboratory' in The Open University of Israel.

## Technologies

Project is created with ANSI C language on Ubuntu 16.04 operating system.

## Input files

- **Source file** of instructions with extension `.as`, for example `ps.as`.

## Output files

There are at most 4 output files:

- `.am` file of instructions after expanding macro statements.
- `.ob` file contains a two-column table with unique base 32 code representation. The first two numbers of the table are counters of instructions and directives translated into unique base 32 code. Other rows contain: list of instruction and directive addresses and codes.
- `.ext` (optional) file, created if there are external labels defined in the source file. Contains the names of external labels and their 32 base addresses.
- `.ent` (optional) file, created if there are entry labels defined in the source file. Contains the names of entry labels and their 32 base addresses.

## More details about running

The program can receive multiple `.as` files as input, but will refer to each file separately. If there is an error in a line of instruction, the program will print the error type to the terminal and continue execution. Lines that contain errors will be ignored in further steps.

Binary machine code in this program is a memory word that contains 10 bits (4 bits for opcode, 2 bits for source operand, 2 bits for destination operand, 2 bits for encoding type). Each line can be represented by 1 to 5 memory words. This intermediate step is not outputted and is directly translated into base 32 code.

## Running steps

1. **Preprocessor:**
   - Receives `.as` file and creates `.am` after expanding macro statements. At this step, the program doesn't check errors inside instructions.

2. **FirstPass:**
   - Read, save instructions and their parameters, separate by type: command or directive (create symbol tables). Check different errors like typos, wrong command names, wrong parameters, etc.

3. **SecondPass:**
   - Check label definitions and types. Handle possible errors in the labels list (e.g., a label defined as both entry and extern in the same source file) and complet encoding.
