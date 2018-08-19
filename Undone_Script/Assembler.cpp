#include "Assembler.h"
#include "opcodes.h"
#include <map>
#include <fstream>
#include <string>

void Assembler::process( const char* filename, const char* exefile) {
		ifstream source(filename);
		
		vector<opcode> code; 
		enum {codeseg, unkown} segment = unkown;
		map<string,labeltable> labels;

		string word;
		while (!source.eof( )) {
			source >> word;
			
			if (word == "codeseg:") {segment = codeseg; continue;}
			
			
			if (segment == codeseg){
				//converting test versions to code.
				if(word =="mov"		)code.push_back(mov		);		else
				if(word =="r"		)code.push_back(r		);		else
				if(word =="m"		)code.push_back(m		);		else
				if(word =="c"		)code.push_back(c		);		else
				if(word =="ui"		)code.push_back(ui		);		else
				if(word =="us"		)code.push_back(us		);		else
				if(word =="ul"		)code.push_back(ul		);		else
				if(word =="f"		)code.push_back(f		);		else
				if(word =="d"		)code.push_back(d		);		else
				if(word =="ll"		)code.push_back(ll		);		else
				if(word =="i"		)code.push_back(i		);		else
				if(word =="s"		)code.push_back(s		);		else
				if(word =="l"		)code.push_back(l		);		else
				if(word =="str"		)code.push_back(str		);		else
				if(word =="add"		)code.push_back(add		);		else
				if(word =="sub"		)code.push_back(sub		);		else
				if(word =="mul"		)code.push_back(mul		);		else
				if(word =="div"		)code.push_back(divi	);		else
				if(word =="rshift"  )code.push_back(rshift  );		else
				if(word =="lshift"	)code.push_back(lshift	);		else
				if(word =="endop"	)code.push_back(endop	);		else
				if(word =="disp"	)code.push_back(disp	);		else
				if(word =="call"	)code.push_back(call	);		else
				if(word =="ret" 	)code.push_back(ret 	);		else
				if(word =="reql"	)code.push_back(reql	);		else
				if(word =="jmp_c"	)code.push_back(jmp_c	);		else
				if(word =="jmp_cn"	)code.push_back(jmp_cn	);		else
				if(word =="cmp"		)code.push_back(cmp		);		else
				if(word =="in"		)code.push_back(in		);		else
				if(word =="getstk"	)code.push_back(getstk	);		else
				if(word =="putstk"	)code.push_back(putstk	);		else
				if(word =="push"	)code.push_back(push	);		else
				if(word =="pop" 	)code.push_back(pop 	);		else
				if(word =="regA"	)code.push_back(regA	);		else
				if(word =="regB" 	)code.push_back(regB 	);		else
				if(word =="regC"	)code.push_back(regC	);		else	
				if(word =="regSP"	)code.push_back(regSP	);
				else if (word[word.length( ) - 1] == ':') {
					labels[word].instruction = code.size( );
				} else if (isalpha( word[0] )) {
					code.push_back(us);
					int pos = code.size();
					for (int i = 0; i < sizeof( unsigned short ); ++i) {
						code.push_back(opcode(0));
					}
					labels[word+':'].positions_in_code.push_back(pos);
				}
				else {
					//its a number then
					opcode num_type = code.back( );
					int num_bytes;
					switch (num_type) {
						case i:
							num_bytes = sizeof(int);
							break;
						case f:
							num_bytes = sizeof(float);
							break;
						case d:
							num_bytes = sizeof(double);
							break;
						case l:
							num_bytes = sizeof(long);
							break;
						case ll:
							num_bytes = sizeof(long long);
							break;
						case c:
							num_bytes = sizeof(char);
							break;
						case ui:
							num_bytes = sizeof(unsigned int);
							break;
						case us:
							num_bytes = sizeof(unsigned short);
							break;
						case s:
							num_bytes = sizeof(short);
							break;
						case str:{
							char ch;
							word[0] = ' ';
							source.get(ch);
							while (ch != '\"'){
								word += ch;
								source.get(ch);
							}

							for (int i = 0; i < word.length( ); ++i) {
								code.push_back((opcode)word[i]);
							}
							code.push_back(opcode(0));
						}continue;
					}
					//save position we are going to put this number at
					int pos = code.size( );
					//now make space for the new variable
					for (int i = 0; i < num_bytes; ++i) {
						code.push_back(opcode(0));
					}
					//copy number into code.
					switch (num_type) {
						case i:{
							int num = atoi(word.c_str());
							memcpy((void*)&code[pos],&num,sizeof(int));
						}break;
						case f:{
							float num = atof(word.c_str());
							memcpy((void*)&code[pos],&num,sizeof(float));
						}break;
						case d:{
							double num = stod(word.c_str());
							memcpy((void*)&code[pos],&num,sizeof(double));
						}break;
						case l:{
							long num = atol(word.c_str());
							memcpy((void*)&code[pos],&num,sizeof(long));
						}break;
						case ll:{
							long long num = atoll(word.c_str());
							memcpy((void*)&code[pos],&num,sizeof(long long));
						}break;
						case c:{
							char num = atoi(word.c_str());
							memcpy((void*)&code[pos],&num,sizeof(char));
						}break;
						case ui:{
							unsigned int num = atoi(word.c_str());
							memcpy((void*)&code[pos],&num,sizeof(unsigned int));
						}break;
						case us:{
							unsigned short int num = atoi(word.c_str());
							memcpy((void*)&code[pos],&num,sizeof(unsigned short int));
						}break;
						case s:{
							short num = atoi(word.c_str());
							memcpy((void*)&code[pos],&num,sizeof(short));
						}break;
					}
					
				}//number crunching done.

				//need to fill out the label redirections
				for (auto& lbl : labels) {
					for (auto& ref : lbl.second.positions_in_code) {
						memcpy((void*)&code[ref],&lbl.second.instruction,sizeof(unsigned short));
					}
				}
			}
		};//done reading from source;
		source.close();

		//now write to outputfile.
		ofstream exe( exefile,ios::binary); 
		filelayoutdata layout;
		exe.seekp(sizeof(layout)+1,ios::beg);
		
		layout.codeseg = exe.tellp();
		layout.codesegsize = code.size();
		exe.write((char*)&code[0],code.size()*sizeof(opcode));

		exe.seekp(0,ios::beg);
		exe.write((char*)&layout,sizeof(layout));

		exe.close();
	}