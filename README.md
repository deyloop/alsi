# Assembly-Like Symbolic Instruction
A Virtual Machine and an assembler that converts code written in ALSI, an 
assembly-like language to bytcode the VM can excecute.

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
