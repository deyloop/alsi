#include "cpu.hpp"
#include "opcodes.h"
#include <iostream>
using namespace std;

#define TYPED_OP(LHS,op,RHS)\
	int type;\
	if((LHS.type == m || LHS.type == r)&&(RHS.type != m || RHS.type != r))\
	type = RHS.type; else type = LHS.type;\
	regi ret;\
	switch(type){\
		case i:\
			ret.ll = *((int*)LHS.ptr) op *((int*)RHS.ptr);\
			break;\
		case f:\
			ret.ll = *((float*)LHS.ptr) op *((float*)RHS.ptr);\
			break;\
		case c:\
			ret.ll = *((char*)LHS.ptr) op *((char*)RHS.ptr);\
			break;\
		case ui:\
			ret.ll = *((unsigned int*)LHS.ptr) op *((unsigned int*)RHS.ptr);\
			break;\
		case us:\
			ret.ll = *((unsigned short*)LHS.ptr) op *((unsigned short*)RHS.ptr);\
			break;\
		case ul:\
			ret.ll = *((unsigned long*)LHS.ptr) op *((unsigned long*)RHS.ptr);\
			break;\
		case d:\
			ret.ll = *((double*)LHS.ptr) op *((double*)RHS.ptr);\
			break;\
		case ll:\
			ret.ll = *((long long*)LHS.ptr) op *((long long*)RHS.ptr);\
			break;\
		case s:\
			ret.ll = *((short*)LHS.ptr) op *((short*)RHS.ptr);\
			break;\
		case l:\
			ret.ll = *((long*)LHS.ptr) op *((long*)RHS.ptr);\
			break;\
		case str:\
            ((regi*)LHS.ptr)->str = (char*)RHS.ptr;break;}

var_p CPU::get_next_arg( ) {
	var_p LHS;
	LHS.type = (opcode)next_byte();
	switch (LHS.type) {
		case r:
			LHS.type = (opcode)next_byte();
			LHS.ptr = &registers[next_byte()].ll;
			break;
		case m:
			LHS.ptr = &stack[registers[next_byte()].us];
			break;

		case i:
			++ip;
			LHS.ptr = &code[ip];
			for(int i = 1; i < sizeof(int); ++i,++ip);
			break;
		case f:
			++ip;
			LHS.ptr = &code[ip];
			for(int i = 1; i < sizeof(float); ++i,++ip);
			break;
		case c:
			++ip;
			LHS.ptr = &code[ip];
			for(int i = 1; i < sizeof(char); ++i,++ip);
			break;
		case ui:
			++ip;
			LHS.ptr = &code[ip];
			for(int i = 1; i < sizeof(unsigned); ++i,++ip);
			break;
		case us:
			++ip;
			LHS.ptr = &code[ip];
			for(int i = 1; i < sizeof(unsigned short); ++i,++ip);
			break;
		case ul:
			++ip;
			LHS.ptr = &code[ip];
			for(int i = 1; i < sizeof(unsigned long); ++i,++ip);
			break;
		case d:
			++ip;
			LHS.ptr = &code[ip];
			for(int i = 1; i < sizeof(double); ++i,++ip);
			break;
		case ll:
			++ip;
			LHS.ptr = &code[ip];
			for(int i = 1; i < sizeof(long long); ++i,++ip);
			break;
		case s:
			++ip;
			LHS.ptr = &code[ip];
			for(int i = 1; i < sizeof(short); ++i,++ip);
			break;
		case l:
			++ip;
			LHS.ptr = &code[ip];
			for(int i = 1; i < sizeof(long); ++i,++ip);
			break;
		case str:
			++ip;
			LHS.ptr = &code[ip];
			for(char ch = code[ip]; ch != '\0';++ip) 
				ch = code[ip];
			--ip;
			break;
	}
	return LHS;
}

/*-----------------------------------------------------------------------------
This opcode marks the end of the program.
usage:
	endop
-----------------------------------------------------------------------------*/
void CPU::op_end( ) {
		running = false;
		++ip;
	}

/*-----------------------------------------------------------------------------
Compares two arguments. If the first argument is greater than the second,
the CPU::flag variable is set.
usage:
	cmp [arg] [arg]
-----------------------------------------------------------------------------*/
void CPU::op_cmp(){
	var_p LHS = get_next_arg(), RHS = get_next_arg();
	TYPED_OP(LHS, > , RHS);
	conditionflag = ret.ll;
	++ip;
}

/*-----------------------------------------------------------------------------
Gets input from the standard input stream and places it in the specified 
argument.
usage:
	in [arg]
-----------------------------------------------------------------------------*/
void CPU::op_in( ) {
	var_p arg = get_next_arg();
	switch(arg.type){
		case ui:
			cin >> *((unsigned int*)arg.ptr);
			break;
		case us:
			cin >> *((unsigned short*)arg.ptr);
			break;
		case ul:
			cin >> *((unsigned long*)arg.ptr);
			break;
		case f:
			cin >> *((float*)arg.ptr);
			break;
		case d:
			cin >> *((double*)arg.ptr);
			break;
		case ll:
			cin >> *((long long*)arg.ptr);
			break;
		case i:
			cin >> *((int*)arg.ptr);
			break;
		case s:
			cin >> *((short int*)arg.ptr);
			break;
		case l:
			cin >> *((long int*)arg.ptr);
			break;
		case c:
			cin >> *((char*)arg.ptr);
			break;
	}
	
	++ip; 
}

/*-----------------------------------------------------------------------------
Copies the value stored at a particular position in the stack into the register
specified. The position must be stored in the register that is given as second 
argument.
usage:
	getstk	[reg1] [reg2]

	where reg1 is the register where the stack value is copied,
		  reg2 contains the position of value to get from stack. 
-----------------------------------------------------------------------------*/
void CPU::op_getstk( ) {
	registers[next_byte()].ll = stack[registers[next_byte()].us];++ip;
}

/*-----------------------------------------------------------------------------
Puts Things into the stack, at a specified position.
usage:
	putstk [reg1] [reg2]

	where reg1 contains the position in stack where the new value is to be put
	      reg2 conatins the value to put.

OR maybe the other way... idk.
-----------------------------------------------------------------------------*/
void CPU::op_putstk( ) {
	stack[registers[next_byte()].us] = registers[next_byte()].ll;++ip;
}


/*-----------------------------------------------------------------------------
Displays the contents of the provided argument.
usage:
	disp [arg]
-----------------------------------------------------------------------------*/
void CPU::op_disp( ) {
	var_p arg = get_next_arg( );
	switch (arg.type) {
		case str:{
			opcode* ch = ((opcode*)arg.ptr);
			for (; *ch != opcode(0); ch++) {
				cout << *(char*)ch;
			}
		}break;
		case ui:
			cout << *((unsigned int*)arg.ptr);
			break;
		case us:
			cout << *((unsigned short*)arg.ptr);
			break;
		case ul:
			cout << *((unsigned long*)arg.ptr);
			break;
		case f:
			cout << *((float*)arg.ptr);
			break;
		case d:
			cout << *((double*)arg.ptr);
			break;
		case ll:
			cout << *((long long*)arg.ptr);
			break;
		case i:
			cout << *((int*)arg.ptr);
			break;
		case s:
			cout << *((short int*)arg.ptr);
			break;
		case l:
			cout << *((long int*)arg.ptr);
			break;
		case c:
			cout << *((char*)arg.ptr);
			break;
	}
	++ip;
}

/*-----------------------------------------------------------------------------
Copies the value stored in second argument (arg2) into arg1.
usage: 
	mov [arg1] [arg2]
-----------------------------------------------------------------------------*/
void CPU::op_mov( ) {
	var_p LHS = get_next_arg(), RHS = get_next_arg();
	TYPED_OP(LHS, = , RHS);
	++ip;
}

/*-----------------------------------------------------------------------------
Adds. Basically LHS = LHS+RHS.
usage:
	add [arg1] [arg2]
	
	after this, arg1 = arg1 + arg2
-----------------------------------------------------------------------------*/
 void CPU::op_add( ) {
	var_p LHS = get_next_arg(), RHS = get_next_arg();
	TYPED_OP(LHS,+=,RHS);
	++ip;
}

 /*-----------------------------------------------------------------------------
subtracts. Basically LHS = LHS-RHS.
usage:
	sub [arg1] [arg2]
	
	after this, arg1 = arg1 - arg2
-----------------------------------------------------------------------------*/
void CPU::op_sub( ) {
	var_p LHS = get_next_arg(), RHS = get_next_arg();
	TYPED_OP(LHS,-=,RHS);
	++ip;
}

/*-----------------------------------------------------------------------------
multiplies. Basically LHS = LHS x RHS.
usage:
	mul [arg1] [arg2]
	
	after this, arg1 = arg1 x arg2
-----------------------------------------------------------------------------*/
void CPU::op_mul( ) {
	var_p LHS = get_next_arg(), RHS = get_next_arg();
	TYPED_OP(LHS,*=,RHS);
	++ip;
}

/*-----------------------------------------------------------------------------
Divides Basically LHS = LHS / RHS.
usage:
	div [arg1] [arg2]
	
	after this, arg1 = arg1 / arg2
-----------------------------------------------------------------------------*/
void CPU::op_div( ) {
	var_p LHS = get_next_arg(), RHS = get_next_arg();
	TYPED_OP(LHS,/=,RHS);
	++ip;
}

/*-----------------------------------------------------------------------------
Right shift opperation.
usage:
	rshift [reg1] [reg2]
	
	[reg1] is tthe register the operation is carried on,
	[reg2] must provide the number of bits to shift.
-----------------------------------------------------------------------------*/
void CPU::op_rshift( ) {
	regi& reg = registers[next_byte( )];
	reg.ll = reg.ll >> registers[next_byte()].ll;
	++ip;
}

/*-----------------------------------------------------------------------------
Left shift. Similar to rshift. same arguments and usage.
-----------------------------------------------------------------------------*/
void CPU::op_lshift( ) {
	regi& reg = registers[next_byte( )];
	reg.ll = reg.ll << registers[next_byte()].ll;
	++ip;
}

/*-----------------------------------------------------------------------------
Makes something that looks like a function call.
usage:
	call [label]

	where [label] is the label that marks the instruction that has to executed
	next. after the block of code following [label] returns, (using ret) the 
	code after this opcode is executed. Just like a function call.
-----------------------------------------------------------------------------*/
void CPU::op_call( ) {
	unsigned retip;
	var_p addr = get_next_arg( );
	retip = ip;
	retip++;
	stack_push( retip );	//We save the current instruction index, so we can
							//resume execution from here when we return.
	ip = *((unsigned int*)addr.ptr); //off we go to new "function"
}

/*-----------------------------------------------------------------------------
Returns to previous call statement. Supposed to.
For this to work, the top of the stack must be the "ip" that was saved by the 
previous call statement.
usage:
	ret
-----------------------------------------------------------------------------*/
void CPU::op_ret( ) {
	ip = stack[sp];
	stack_pop( );
}

/*-----------------------------------------------------------------------------
Checks if two registers are equal. If they are equal, the 'flag' is set to true,
otherwise it is set to false.
usage:
	reql [reg1] [reg2]
-----------------------------------------------------------------------------*/
void CPU::op_reql( ) {
	conditionflag = registers[next_byte( )].ll == registers[next_byte( )].ll;
	++ip;
}

/*-----------------------------------------------------------------------------
Conditional Jump. Jumps to code labeled by [label] if the conditionflag is true.
usage:
	jump_c [label]
	
-----------------------------------------------------------------------------*/
void CPU::op_jmp_c( ) {
	if (conditionflag){
		ip = *((unsigned short*)get_next_arg().ptr);
	} else {
		get_next_arg( );
		++ip;
	}
}

/*-----------------------------------------------------------------------------
Conditional Jump. Jumps to code labeled by [label] if the conditionflag is false.
Basically opposite of jump_c.
usage:
	jump_cn [label]
	
-----------------------------------------------------------------------------*/
void CPU::op_jmp_cn( ) {
	if (!conditionflag) ip = *((unsigned short*)get_next_arg().ptr);
	else {
		get_next_arg();
		++ip;
	}
}

/*-----------------------------------------------------------------------------
Pushes stuff onto the stack
usage:
	push [reg]

	contents of [reg] are pushed to stack.
	
-----------------------------------------------------------------------------*/
void CPU::op_push( ) {
	stack_push( registers[next_byte( )].ll );
	++ip;
}

/*-----------------------------------------------------------------------------
pops the stack.
usage:
	pop 
-----------------------------------------------------------------------------*/
void CPU::op_pop( ) {
	stack_pop( );
	++ip;
}
