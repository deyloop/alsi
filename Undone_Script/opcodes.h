#pragma once
#ifndef _OPCODES_H_
#define _OPCODES_H_

/*-----------------------------------------------------------------------------
This is an enum representing all the opcodes that can be used within the script
-----------------------------------------------------------------------------*/
enum opcode {
    nothing   = 0 ,
	/*Quick guide to the Assembly-Like Scripting Instruction (ALSI):
	Here you will find the opcodes, with thier usages.
	
	[label] means a label. Marks parts of code. labels are declared like
	   labelname:
	That colon is important for the declaration. 
	They are used without the semicolon like
	   jmp_c labelname
	
	[reg] means a register name. (regA, regB, regSP, etc.).
	
	[arg] means argument. arguments ar written like this:
	if argument is a  constant data value:
		[type] [data]
	ex:
		i 25					//is an int with value 25
		
		str " hello"			//is a string saying hello
	
	see bellow for all [type]
	if argument is register:
		r [type] [reg]
	ex: 
		r ll regB				//take regB and treat it like a long long int
	
	*/
	//actual opcodes follow.
	mov,			//usage:	mov [arg] [arg]
    
	add,			//usage:	add [arg] [arg]
    sub,			//usage:	sub [arg] [arg]
    mul,			//usage:	mul [arg] [arg]
    divi,			//usage:	div [arg] [arg]	//divi-> because div was ambigius
               
    rshift,			//usage:	rshift [reg] [reg]
    lshift,			//usage:	lshift [reg] [reg]
               
	disp,			//usage:	disp [arg]

	in,				//usage:	in [arg]
	getstk,			//usage:	getstk [reg] [reg]
	putstk,			//usage:	putstk [reg] [reg]

    call,			//usage:	call [label]
    ret,			//usage:	ret

    reql,			//usage:	reql [reg] [reg]
    jmp_c,			//usage:	gmp_c [label]
    jmp_cn,			//usage:	jmp_cn [label]

	cmp,			//usage:	cmp [arg] [arg]
	
	push,
    pop,			//usage:	pop

    endop,			//usage:	endop

	//for further info about what these arguments mean, reffer to 
	//opcode implimentations in opcodes.cpp

	//The following are used to represent type
	r,
	m,

	//values for [type]
	c,				//char
	ui,				//unsigned int
	us,				//unsigned short
	ul,				//unsigned long
	f,				//float
	d,				//double
	ll,				//long long
	i,				//int
	s,				//short
	l,				//long
	str,			//string

	//The following are used to refer to specific registers.
    regA   = 0 ,
    regB       ,
    regC	   ,
    regSP	   ,

};
#endif