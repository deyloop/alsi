#include <iostream>
#include "CPU.h"
#include "opcodes.h"
using namespace std;

/******************************************************************************
This function is called when the CPU is created and before calling execute.
-----------------------------------------------------------------------------*/
void CPU::initialize( unsigned datasegsize, unsigned stacksize ) {
	for (auto& reg : registers) { //initializing all registers to 0
        reg.d = 0;
    }
    ip = 0; sp = 0;
    running = false;
    conditionflag = false;
    
    const unsigned ssize = stacksize;
    stack = new long long[ssize];
    stack_size = stacksize;
    stack[sp] = 0;
    code = nullptr;

    init_opcodes( );
}

/*-----------------------------------------------------------------------------
Function initializes the array of opcode-function binding. Each opcode is 
bound to a function that does what the opcode specifies to be doing. Whenever
the CPU needs to execute a particular opcode, it calls its corresponding function.
-----------------------------------------------------------------------------*/
void CPU::init_opcodes( ) {
	opcodes[endop]	= bind( &CPU::op_end, this );
    opcodes[mov]	= bind( &CPU::op_mov, this );
    opcodes[add]	= bind( &CPU::op_add, this );
    opcodes[sub]	= bind( &CPU::op_sub, this );
    opcodes[mul]	= bind( &CPU::op_mul, this );
    opcodes[divi]	= bind( &CPU::op_div, this );
	opcodes[rshift] = bind( &CPU::op_rshift, this );
    opcodes[lshift] = bind( &CPU::op_lshift, this );
    opcodes[call]	= bind( &CPU::op_call, this );
    opcodes[ret]	= bind( &CPU::op_ret, this );
    opcodes[reql]	= bind( &CPU::op_reql, this );
    opcodes[jmp_c]	= bind( &CPU::op_jmp_c, this );
    opcodes[jmp_cn] = bind( &CPU::op_jmp_cn, this );
    opcodes[push]	= bind( &CPU::op_push, this );
    opcodes[pop]	= bind( &CPU::op_pop, this );
	opcodes[disp]	= bind( &CPU::op_disp, this);
	opcodes[cmp	]	= bind( &CPU::op_cmp	 ,this);
	opcodes[in]		= bind( &CPU::op_in,this );
	opcodes[getstk] = bind( &CPU::op_getstk,this );
	opcodes[putstk] = bind( &CPU::op_putstk,this );    
}

/*-----------------------------------------------------------------------------
Reads in the code to be executed and executes each opcode in there.
Parameters:
[IN]	from_ip		-	the index of the instruction in the code from which 
						execution starts.

EXPLAINED: 
     The CPU must be provided with an array of opcodes previous to this.
	 This array is a sequence of commands that the CPU executes one by one.
	 For each opcode, it calls the corresponding function (stored in the array
	 CPU::opcodes[256]) that is responsible for actually doing the task that the 
	 command is supposed to do.
	     ex: if opcodes[ip] == mov, then by array lookup, we call CPU::op_mov,
		     which processes the parameters that follow.
-----------------------------------------------------------------------------*/
void CPU::execute( unsigned from_ip ) {
	 unsigned long inst_count = 0;

        running = true;
        while (running) {
            
			//Error checking: Check to see if the code going to be 
			//executed is a valid opcode
			if(code[ip] > nothing && code[ip] <= endop){
				opcodes[code[ip]]( );
				++inst_count;
			} else {
				//stop execution
				cout << "ERROR: Unexpected opcode detected at instruction " 
					 << ip <<endl;
				running = false;
			}
            
        }

        cout << "\nInstructions Executed: " << inst_count << endl;
}

/*-----------------------------------------------------------------------------
Called when its time to shut down.
-----------------------------------------------------------------------------*/
void CPU::cleanup( ) {
	delete[] stack;
}

/*-----------------------------------------------------------------------------
Displayes the contents of all the regsters to standard output.
-----------------------------------------------------------------------------*/
void CPU::dump_registers( ) {
	cout << "\n\nREGISTER DUMP:\n";
        int i = 0;
        for (auto & reg : registers) {
            cout << "Register " << i << ": \n"
                << "\tint\t\t: " << reg.i << "\n"
                << "\tunsigned short\t: "<<reg.us<< "\n"
                << "\tlong long\t: " << reg.ll << "\n"
                << "\tfloat\t\t: " << reg.f << "\n"
				<< "\tchar\t\t: "<<reg.c<<endl;
            ++i;
        }
		cout << "flag: " << conditionflag <<endl;
}