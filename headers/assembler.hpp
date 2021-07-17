#pragma once
#ifndef _ASSEMBLER_H_
#define _ASSEMBLER_H_

#include <vector>

using namespace std;

struct filelayoutdata {
  int codeseg, codesegsize;
};

struct labeltable {
  unsigned short instruction;
  vector<int> positions_in_code;
};

class Assembler {
  public:
    void process(const char*,const char*);
};

#endif
