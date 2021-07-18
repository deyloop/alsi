# Assembly-Like Symbolic Instruction
A Virtual Machine and an assembler that converts code written in `ALSI`, an 
assembly-like language to bytecode the VM can execute.

## Usage
1. Build
  ```sh
  # clone this repository
  git clone https://github.com/AnurupDey/alsi.git

  # generate build files
  cd alsi
  mkdir build && cd build
  cmake ..

  # run the build (here we use make on linux)
  make
  ```
2. Run the program
  ```sh
  # Run one of the examples
  ./alsi
  ```

## Examples
Some example programs can be found in `example_programs` directory.

## Example of Output
Here is an example of assembling and running the recursive factorial program.
```
$ ./alsi
Main Menu
1. Assemble file to bytecode
2. Execute bytecode
3. Assemble and execute
0. Exit

Enter choice 1
Enter source file name: ../example_programs/FactorialRec.txt
Enter bytecode file name: prog
Assemblage complete

Main Menu
1. Assemble file to bytecode
2. Execute bytecode
3. Assemble and execute
0. Exit

Enter choice 2
Enter bytecode file name: prog
 Enter a number: 5
 The Factorial of 5 is 120
Instructions Executed: 57

Main Menu
1. Assemble file to bytecode
2. Execute bytecode
3. Assemble and execute
0. Exit

Enter choice 0
```

## Writing `ALSI` code
Refer to the examples to learn how to write `ALSI` code. `ALSI` is an 
assembly language. Refer to `headers/opcodes.hpp` for a list and description
of all the supported opcodes.
