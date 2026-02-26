#pragma once

#include <iostream>
#include <string>

#define print(msg) std::cout << "[General] " << (msg) << std::endl;
#define warn(msg)  std::cout << "[Warning] " << (msg) << std::endl;
#define error(msg) std::cerr << "[Error] " << (msg) << std::endl;

// macro

#define VM_CPU_DISABLE_PROTECTION_MODE
#define VM_MEM_CREATE_NO_WARNING

// end macro

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

// placeholder arguments for override functions
/*
char Function(int arg1, char) return (char)1; <- Function(1, CHAR_ARGV) to get char return value
int Function(int arg1, int) return (int)1;    <- Function(1, INT_ARGV) to get int return value
*/
constexpr byte  BYTE_ARGV     = 0x0F;
constexpr word  WORD_ARGV     = 0x0F0F;
constexpr dword DWORD_ARGV    = 0x0F0F0F0F;
constexpr qword QWORD_ARGV    = 0x0F0F0F0F0F0F0F0F;


typedef dword                   maxsize;

typedef byte                    regb;
typedef word                    regw;
typedef dword                   regd;
typedef qword                   regq;

typedef dword                   ctrlreg;

typedef dword                   addr;

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