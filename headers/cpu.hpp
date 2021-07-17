#pragma once
#ifndef _CPU_H_
#define _CPU_H_

#include <functional>
#include "opcodes.h" 

enum opcode;
typedef char byte;

/*-----------------------------------------------------------------------------
This is a register. Registers are memory slots which the CPU can directly 
access. All other memory (RAM,Disk,etc) cannot be accesssed directly by the 
CPU. All calculations are performed on the registers, and then the other
memories (secondary memory- RAM) are updated if and when required.

A register has the ability to store any type of variable, and they also can be 
interpreted as any type of variable, thus they are implemented as an union.
-----------------------------------------------------------------------------*/
union regi {
    char           c;
    unsigned       ui;
    unsigned short us;
    unsigned long  ul;
    float          f;
    double         d;
    long long      ll;
    int            i;
    short          s;
    long           l;
	char*          str;
};

/*-----------------------------------------------------------------------------
When working with variables, the CPU can refer to them without knowing 
what type it is using these
-----------------------------------------------------------------------------*/
struct var_p {
    void*           ptr;
    int type;
};

/*-----------------------------------------------------------------------------
Creates a virtual environment for opcodes to be executed. Basically a virtual
CPU/Machine
-----------------------------------------------------------------------------*/
struct CPU {
    regi registers[4];

    opcode* code;  unsigned code_size;
    long long*   stack; unsigned stack_size;

    unsigned short ip, sp;
    bool conditionflag;

    bool running;

    std::function<void(void)> opcodes[256];

    struct Data_Seg {
        unsigned size;
        int*       ints;
        float*     floats;
        double*    doubles;
        long*	   longs;
        char*      chars;
        short*     shorts;
        unsigned int* uints;
        unsigned short* ushorts;
        long long* longlongs;
        unsigned long* ulongs;
    } Data_Segment;

    void initialize(unsigned datasegsize, unsigned stacksize );
    void init_opcodes( );
    void execute(unsigned from_ip );
    void cleanup( );
    void dump_registers( );

    byte next_byte( ) {
        ++ip;
        return code[ip];
    }

    void stack_push(long long content) {
        ++sp;
        stack[sp] = content;
        registers[regSP].us = sp;
    }

    void stack_pop( ) {
        --sp;
		registers[regSP].us = sp;
		
    }

    var_p get_next_arg( );

    //opcodel
    void op_end( );
    void op_cmp();
    void op_in( );
    void op_getstk( );
    void op_putstk( );
    void op_disp();
    void op_mov( );
    void op_add( );
    void op_sub( );
    void op_mul( );
    void op_div( );
    void op_rshift( );
    void op_lshift( );
    void op_call( );
    void op_ret( );
    void op_reql( );
    void op_jmp_c( );
    void op_jmp_cn( );
    void op_push( );
    void op_pop( );
};


#endif
