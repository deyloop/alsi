#include <iostream>
#include <functional>
#include "opcodes.hpp"
#include "cpu.hpp"
#include "assembler.hpp"

#include <fstream>
#include <string>
#include <vector>


/*-----------------------------------------------------------------------------
  Loads binary opcodes from file and executes the opcodes.
Parameters:
[IN]	cpu		-	reference to the CPU object that will execute the code.
[IN]	bytecode-	string containing the name of the binary bytecode file to
load.
----------------------------------------------------------------------------*/
void ExecuteCode(CPU& cpu,std::string bytecode) {
  cpu.initialize( 0 , 1024 );

  std::ifstream codefile(bytecode,std::ios::binary);

  //Load in the layout and actual code/opcodes into memory.
  filelayoutdata layout;
  codefile.read((char*)&layout,sizeof(layout));

  std::vector<opcode> code;
  code.resize(layout.codesegsize);
  codefile.seekg(layout.codeseg,std::ios::beg);
  codefile.read((char*)&code[0],code.size()*sizeof(opcode));

  //tell the cpu about our code.
  cpu.code = &code[0];

  //GO!
  cpu.execute(0);

  cpu.cleanup( );
}


/*-----------------------------------------------------------------------------
  Assembles, that is, Converts text code into binary.
Parameters:
[IN]	comp		- reference to Assembler object that does the assembling
[IN]	sourcefile	- string containing name of source file.
[IN]	outputfile	- string containing the name of the file that will 
contain the resulting opcode binary after assembly
-----------------------------------------------------------------------------*/
void Assemble( Assembler& comp,std::string sourcefile, std::string outputfile) {

  comp.process(sourcefile.c_str(),outputfile.c_str());
  std::cout << "Assemblage complete\n";
}

/*-----------------------------------------------------------------------------
  The starting point of the Application. Displays a menu and acts accordingly
-----------------------------------------------------------------------------*/
int main( ) {

  bool run = true;
  Assembler comp;
  CPU cpu;

  while (run) {
    std::cout << "Main Menu\n"
      << "1. Assemble file to bytecode\n"
      << "2. Execute bytecode\n"
      << "3. Assemble and execute\n"
      << "0. Exit\n\n";
    int opt;
    std::cout << "Enter choice ";
    std::cin >> opt;
    switch (opt) {
      case 1:{
        std::string sourcefile, outputfile;
        std::cout << "Enter source file name: ";
        std::cin >> sourcefile;
        std::cout << "Enter bytecode file name: ";
        std::cin >> outputfile;
        Assemble(comp,sourcefile,outputfile);
      } break;
      case 2: {
        std::cout << "Enter bytecode file name: ";
        std::string bytecode;
        std::cin >> bytecode;
        ExecuteCode(cpu,bytecode);
      } break;
      case 3:{
        std::string sourcefile;
        std::cout << "Enter source file name: ";
        std::cin >> sourcefile;
        Assemble(comp,sourcefile,"tempout.bytecode");
        ExecuteCode(cpu,"tempout.bytecode");
        remove("tempout.bytecode");
      } break;
      case 0:
        run = false;
        break;
    }
    std::cout << std::endl;
  }

  return 0;
}
