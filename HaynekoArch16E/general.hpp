#pragma once

#include <iostream>
#include <string>

#define print(msg) std::cout << (msg) << std::endl;
#define error(msg) std::cerr << (msg) << std::endl;

typedef unsigned char           byte;
typedef unsigned short          word;
typedef unsigned int            dword;
typedef unsigned long long      qword;

constexpr byte  BYTE_RANGE    = 0xFF;
constexpr word  WORD_RANGE    = 0xFFFF;
constexpr dword DWORD_RANGE   = 0xFFFFFFFF;
constexpr qword QWORD_RANGE   = 0xFFFFFFFFFFFFFFFF;
constexpr byte  BYTE_SIGN     = 0x80;
constexpr word  WORD_SIGN     = 0x8000;
constexpr dword DWORD_SIGN    = 0x80000000;
constexpr qword QWORD_SIGN    = 0x8000000000000000;


typedef dword                   maxsize;

typedef byte                    regb;
typedef word                    regw;
typedef dword                   regd;
typedef qword                   regq;

typedef dword                   ctrlreg;

typedef byte                    addrb;
typedef word                    addrw;
typedef dword                   addrd;
typedef qword                   addrq;

typedef byte                    dispb;
typedef word                    dispw;
typedef dword                   dispd;
typedef qword                   dispq;

typedef byte                    immb;
typedef word                    immw;
typedef dword                   immd;
typedef qword                   immq;

typedef dword                   flag;


// ### FUNCTIONS ###
// truncation
inline dword truncateQ2D( qword val ) {
	return val & DWORD_RANGE;
}

inline word truncateQ2W( qword val ) {
	return val & WORD_RANGE;
}

inline byte truncateQ2B( qword val ) {
	return val & BYTE_RANGE;
}

inline word truncateD2W( dword val ) {
	return val & WORD_RANGE;
}

inline byte truncateD2B( dword val ) {
	return val & BYTE_RANGE;
}

inline byte truncateWord( word val ) {
	return val & BYTE_RANGE;
}

// sign/zero extention
inline qword signExtendD2Q( dword val ) {
	if ( val & DWORD_SIGN )
		return val | 0xFFFFFFFF80000000;
}

inline dword signExtendW2D( word val ) {
	if ( val & WORD_SIGN )
		return val | 0xFFFF8000;
}

inline dword signExtendB2D( byte val ) {
	if ( val & BYTE_SIGN )
		return val | 0xFFFFFF80;
}