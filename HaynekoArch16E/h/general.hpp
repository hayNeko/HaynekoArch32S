// general header for HA32S visual machine.
// copyright (c) 2026, hayNeko

#ifndef HA32S_H_GENERAL_
#define HA32S_H_GENERAL_

#include <iostream>
#include <string>

#define VM_VERSION 3

// status code
constexpr int VM_PROCESS_EXIT_CODE_SUCCESS           = 0;
constexpr int VM_PROCESS_EXIT_CODE_FAILURE           = 1;
constexpr int VM_PROCESS_EXIT_CODE_ABORT             = 2;
constexpr int VM_INPUT_EXECUTABLE_CANNOT_FIND        = 3;
constexpr int VM_INPUT_EXECUTABLE_CANNOT_OPEN        = 4;
constexpr int VM_INPUT_EXECUTABLE_INVALID_FORMAT     = 5;
constexpr int VM_RUNTIME_EXTERNAL_INTERRUPT          = 7;
constexpr int VM_RUNTIME_MEMORY_OVERFLOW             = 8;
constexpr int VM_RUNTIME_INVALID_INSTRUCTION         = 9;
constexpr int VM_RUNTIME_INVALID_MEMORY_ACCESS       = 10; // only in PROTECTION_MODE
constexpr int VM_RUNTIME_DEREFERENCE_NULL_POINTER    = 11; // only in PROTECTION_MODE
constexpr int VM_RUNTIME_DIVISION_BY_ZERO            = 12;
constexpr int VM_DIE                                 = -1;

// macro

#define VMCPU_DISABLE_PROTECTION_MODE
#define VMMEM_CREATE_NO_WARNING

#define VMENDIAN_LITTLE

#define VER_ALPHA

// end macro

typedef unsigned char           byte;
typedef unsigned short          word;
typedef unsigned int            dword;
typedef unsigned long long      qword;
typedef signed char            sbyte;
typedef signed short           sword;
typedef signed int             sdword; // or just int
typedef signed long long       sqword;
typedef int                     rtrnval;

constexpr byte  BYTE_RANGE  = 0xFF;
constexpr word  WORD_RANGE  = 0xFFFF;
constexpr dword DWORD_RANGE = 0xFFFFFFFF;
constexpr qword QWORD_RANGE = 0xFFFFFFFFFFFFFFFF;
constexpr byte  BYTE_SIGN   = 0x80;
constexpr word  WORD_SIGN   = 0x8000;
constexpr dword DWORD_SIGN  = 0x80000000;
constexpr qword QWORD_SIGN  = 0x8000000000000000;

// placeholder arguments for override functions
/*
char Function(int arg1, char) return (char)1; <- Function(1, CHAR_ARGV) to get char return value
int Function(int arg1, int) return (int)1;    <- Function(1, INT_ARGV) to get int return value
*/

constexpr byte  BYTE_ARGV  = 0x0F;
constexpr word  WORD_ARGV  = 0x0F0F;
constexpr dword DWORD_ARGV = 0x0F0F0F0F;
constexpr qword QWORD_ARGV = 0x0F0F0F0F0F0F0F0F;

typedef dword                   maxsize;

typedef byte                    regb;
typedef word                    regw;
typedef dword                   regd;
typedef qword                   regq;
typedef byte                    regid;

typedef dword                   ctrlreg;
typedef byte                    crid;

typedef word                    addrw;
typedef dword                   addr;

typedef byte                    portid;

typedef sbyte                   dispb;
typedef sword                   dispw;
typedef sdword                  dispd;
typedef sqword                  dispq;

typedef byte                    immb;
typedef word                    immw;
typedef dword                   immd;
typedef qword                   immq;

typedef dword                   flag;

typedef byte                    factor;

// ### FUNCTIONS ###
inline void println( const std::string &msg ) {
	std::cout << msg << std::endl;
}

inline void logln( const std::string &msg ) {
	std::cout << "[LOG] " << msg << std::endl;
}

inline void errorln( const std::string &msg ) {
	std::cerr << "[ERROR] " << msg << std::endl;
}


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
	return (qword) val;
}

inline dword signExtendW2D( word val ) {
	if ( val & WORD_SIGN )
		return val | 0xFFFF8000;
	return (dword) val;
}

inline dword signExtendB2D( byte val ) {
	if ( val & BYTE_SIGN )
		return val | 0xFFFFFF80;
	return (dword) val;
}

// bit set/clear

inline bool isBitSet( dword res, byte bit_pos ) {
	return res & ( 1 << bit_pos );
}

inline void setBit( dword &res, byte bit_pos ) {
	res |= ( 1 << bit_pos );
}

inline void clearBit( dword &res, byte bit_pos ) {
	res &= ~( 1 << bit_pos );
}

inline void toggleBit( dword &res, byte bit_pos ) {
	res ^= ( 1 << bit_pos );
}

// tool

inline dword random( dword seed ) {
	dword ans = ( seed ^ 0x39DF307E ) >> ( seed & 0x07 );
	for ( byte i = 0; i <= ( (byte)( seed ^ 0x39 ) ); ++i ) {
		ans ^= ( ~( i << 2 ) + 0x16 ) * ( ( i << 2 ) + i ) - ( ( i << 8 ) | ( seed % 16 ) );
		ans += (dword)( ~( seed & 0x3900005B - i * 8 ) >> 3 );
	}
	return ans;
}

inline dword randoms( dword seed, byte times ) {
	dword ans = 0;
	for ( byte i = 0; i <= times; ++i ) {
		ans += random( seed );
	}
	return ans;
}

#endif // HA32S_H_GENERAL_