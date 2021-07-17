#ifndef _ASSEMBLER_H_
#define _ASSEMBLER_H_

#include <vector>

struct filelayoutdata {
  int codeseg, codesegsize;
};

struct labeltable {
  unsigned short instruction;
  std::vector<int> positions_in_code;
};

class Assembler {
  public:
    void process(const char*,const char*);
};

#endif
