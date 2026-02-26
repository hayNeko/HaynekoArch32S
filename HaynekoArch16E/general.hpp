#pragma once

#include <iostream>
#include <string>

#define print(msg) std::cout << (msg) << std::endl;

typedef unsigned char           byte;
typedef unsigned short          word;
typedef unsigned int            dword;
typedef unsigned long long      qword;

typedef byte                    regb;
typedef word                    regw;
typedef dword                   regd;
// typedef qword                regq;

typedef dword                   ctrlreg;

typedef byte                    addrb;
typedef word                    addrw;
typedef dword                   addrd;
// typedef qword                addrq;

typedef byte                    dispb;
typedef word                    dispw;
typedef dword                   dispd;
// typedef qword                dispq;

typedef byte                    immb;
typedef word                    immw;
typedef dword                   immd;
// typedef qword                immq;

typedef dword                   prt;

typedef dword                   flag;

