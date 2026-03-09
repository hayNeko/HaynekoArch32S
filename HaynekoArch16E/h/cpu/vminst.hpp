#ifndef HA32S_H_VMINST_
#define HA32S_H_VMINST_

#include "h/general.hpp"
#include "cpu/vminstprefix.hpp"
#include "cpu/vmreg.hpp"
#include "cpu/vmflag.hpp"

class VM;

class Inst {
public:

	// some of the instruction will modify the dstreg. ( dstreg OP= srcreg, but not dstreg = srcreg OP srcreg2 )

	static void nop( VM &vm );
	static void mov( VM &vm, regid dstreg, regid srcreg );
	static void entr( VM &vm );
	static void leav( VM &vm );
	static void lea( VM &vm, regid dstreg, regid srcreg, dispb offset );
	static void leasc( VM &vm, regid dstreg, regid srcreg, factor factor, regid srcreg2, dispb offset );
	static void brk( VM &vm );
	static void cmp( VM &vm, regid dstreg, regid srcreg );
	static void jmp( VM &vm, dispw offset );
	static void jmpr( VM &vm, regid dstreg );
	static void callr( VM &vm, regid dstreg );
	static void intr( VM &vm, byte imm ); // the original instruction is 'int'(interrupt), but it's a keyword in C++
	static void iret( VM &vm );
	static void in( VM &vm, portid port );
	static void out( VM &vm, portid port );
	static void syscall( VM &vm );

	static void ld( VM &vm, regid dstreg, regid srcreg, dispb offset );
	static void st( VM &vm, regid dstreg, regid srcreg, dispb offset );
	static void ldofip( VM &vm, regid dstreg, dispw offset );
	static void stofip( VM &vm, regid dstreg, dispw offset );

	static void jz( VM &vm, dispw offset );
	static void jc( VM &vm, dispw offset );
	static void jo( VM &vm, dispw offset );
	static void jn( VM &vm, dispw offset );
	static void jnz( VM &vm, dispw offset );
	static void jnc( VM &vm, dispw offset );
	static void jno( VM &vm, dispw offset );
	static void jnn( VM &vm, dispw offset );
	static void jl( VM &vm, dispw offset );
	static void jge( VM &vm, dispw offset );
	static void ja( VM &vm, dispw offset );
	static void jbe( VM &vm, dispw offset );
	static void jle( VM &vm, dispw offset );
	static void jag( VM &vm, dispw offset );
	static void call( VM &vm, dispw addr ); // a WORD ptr call, not DWORD ptr call.
	static void ret( VM &vm );

	static void movz( VM &vm, regid dstreg, regid srcreg );
	static void movc( VM &vm, regid dstreg, regid srcreg );
	static void movo( VM &vm, regid dstreg, regid srcreg );
	static void movn( VM &vm, regid dstreg, regid srcreg );
	static void movnz( VM &vm, regid dstreg, regid srcreg );
	static void movnc( VM &vm, regid dstreg, regid srcreg );
	static void movno( VM &vm, regid dstreg, regid srcreg );
	static void movnn( VM &vm, regid dstreg, regid srcreg );
	static void movl( VM &vm, regid dstreg, regid srcreg );
	static void movge( VM &vm, regid dstreg, regid srcreg );
	static void mova( VM &vm, regid dstreg, regid srcreg );
	static void movbe( VM &vm, regid dstreg, regid srcreg );
	static void movle( VM &vm, regid dstreg, regid srcreg );
	static void movag( VM &vm, regid dstreg, regid srcreg );
	static void jmpfar( VM &vm, addr addr ); // a DWORD ptr jmp.

	static void pushimmdw( VM &vm, dword imm );
	static void push_ra( VM &vm );
	static void push_rb( VM &vm );
	static void push_rc( VM &vm );
	static void push_rd( VM &vm );
	static void push_ri( VM &vm );
	static void push_bp( VM &vm );
	static void addsp( VM &vm, immb imm ); // unsigned immediate there.
	/* this is OP 0x48 series */
	static void pushimmb( VM &vm, immb imm );
	static void pushtr( VM &vm, regid dstreg, regid srcreg, regid srcreg2 );
	static void pushimmw( VM &vm, immw imm );
	static void poptr( VM &vm, regid dstreg, regid srcreg, regid srcreg2 );
	static void ldstvalow( VM &vm, regid dstreg, dispw offset );
	static void ststvalow( VM &vm, regid srcreg, dispw offset );
	static void push( VM &vm, regid dstreg );
	static void pop( VM &vm, regid dstreg );
	static void ldstval( VM &vm, regid dstreg, dispb offset );
	static void ststval( VM &vm, regid dstreg, dispb offset );
	static void pushf( VM &vm );
	static void popf( VM &vm );
	static void puship( VM &vm );
	/* end of OP 0x48 series */
	static void pop_ra( VM &vm );
	static void pop_rb( VM &vm );
	static void pop_rc( VM &vm );
	static void pop_rd( VM &vm );
	static void pop_ri( VM &vm );
	static void pop_bp( VM &vm );
	static void subsp( VM &vm, immb imm ); // unsigned immediate there.

	/* this is OP 0x50 series */
	static void btle( VM &vm, regid dstreg, regid srcreg );
	static void xorr( VM &vm, regid dstreg, regid srcreg, regid srcreg2 ); // the original instruction is 'xor'(bitwise xor), but it's a keyword in C++
	static void andr( VM &vm, regid dstreg, regid srcreg, regid srcreg2 ); // the original instruction is 'and'(bitwise logical and), but it's a keyword in C++
	static void orr( VM &vm, regid dstreg, regid srcreg, regid srcreg2 ); // the original instruction is 'or'(bitwise logical or), but it's a keyword in C++
	static void btbe( VM &vm, regid dstreg, regid srcreg );
	static void xnor( VM &vm, regid dstreg, regid srcreg, regid srcreg2 );
	static void nand( VM &vm, regid dstreg, regid srcreg, regid srcreg2 );
	static void nor( VM &vm, regid dstreg, regid srcreg, regid srcreg2 );
	static void shlr( VM &vm, regid dstreg, regid srcreg );
	static void shrr( VM &vm, regid dstreg, regid srcreg );
	static void imm( VM &vm, regid dstreg, immd imm );
	static void imb( VM &vm, regid dstreg, immb imm ); // the original instruction is 'immb'(immediate byte), but it's a type defined in general.hpp.
	static void immbsx( VM &vm, regid dstreg, immb imm );
	static void sarr( VM &vm, regid dstreg, regid srcreg );
	static void rolr( VM &vm, regid dstreg, regid srcreg );
	static void rorr( VM &vm, regid dstreg, regid srcreg );
	/* end of OP 0x50 series */
	static void xori( VM &vm, regid dstreg, regid srcreg, immb imm );
	static void andi( VM &vm, regid dstreg, regid srcreg, immb imm );
	static void ori( VM &vm, regid dstreg, regid srcreg, immb imm );
	static void notr( VM &vm, regid dstreg, regid srcreg ); // the original instruction is 'not'(bitwise logical not), but it's a keyword in C++
	static void xnori( VM &vm, regid dstreg, regid srcreg, immb imm );
	static void nandi( VM &vm, regid dstreg, regid srcreg, immb imm );
	static void nori( VM &vm, regid dstreg, regid srcreg, immb imm );
	static void shl( VM &vm, regid dstreg, regid srcreg, immb imm );
	static void shr( VM &vm, regid dstreg, regid srcreg, immb imm );
	static void clr_ra( VM &vm );
	static void copyip( VM &vm );
	static void xchg( VM &vm, regid dstreg, regid srcreg );
	static void sar( VM &vm, regid dstreg, regid srcreg, immb imm );
	static void rol( VM &vm, regid dstreg, regid srcreg, immb imm );
	static void ror( VM &vm, regid dstreg, regid srcreg, immb imm );

	static void mul( VM &vm, regid dstreg, regid srcreg, regid srcreg2, regid srcreg3 ); // this is a 4-operand operation.
	static void div( VM &vm, regid dstreg, regid srcreg, regid srcreg2, regid srcreg3 ); // this is a 4-operand operation.
	static void addib( VM &vm, regid dstreg, regid srcreg, immb imm );
	static void smul( VM &vm, regid dstreg, regid srcreg, regid srcreg2, regid srcreg3 ); // same as mul, but signed.
	static void sdiv( VM &vm, regid dstreg, regid srcreg, regid srcreg2, regid srcreg3 ); // same as div, but signed.
	static void subib( VM &vm, regid dstreg, regid srcreg, immb imm );
	static void random( VM &vm );
	static void inc( VM &vm, regid dstreg, regid srcreg ); // it's 2-operand type, not only one operand!
	static void neg( VM &vm, regid dstreg, regid srcreg ); // it's 2-operand type, not only one operand!
	static void addidw( VM &vm, regid dstreg, regid srcreg, dword imm );
	static void inc_rc( VM &vm );
	static void dec( VM &vm, regid dstreg, regid srcreg ); // it's 2-operand type, not only one operand!
	static void abs( VM &vm, regid dstreg, regid srcreg ); // it's 2-operand type, not only one operand!
	static void subidw( VM &vm, regid dstreg, regid srcreg, dword imm );
	static void dec_rc( VM &vm );

	static void add( VM &vm, regid dstreg, regid srcreg, regid srcreg2 );
	static void xoridw( VM &vm, regid dstreg, regid srcreg, dword imm );
	static void andidw( VM &vm, regid dstreg, regid srcreg, dword imm );
	static void oridw( VM &vm, regid dstreg, regid srcreg, dword imm );
	static void sub( VM &vm, regid dstreg, regid srcreg, regid srcreg2 );
	static void xnoridw( VM &vm, regid dstreg, regid srcreg, dword imm );
	static void nandidw( VM &vm, regid dstreg, regid srcreg, dword imm );
	static void noridw( VM &vm, regid dstreg, regid srcreg, dword imm );

	/* this is OP 0x80 series */
	static void nop2( VM &vm );
	static void nop3( VM &vm );
	static void nop4( VM &vm );
	static void nop5( VM &vm );
	static void nop6( VM &vm );
	static void nop7( VM &vm );
	static void nop8( VM &vm );
	static void nop9( VM &vm );
	static void nop10( VM &vm );
	static void nop11( VM &vm );
	static void nop12( VM &vm );
	static void nop13( VM &vm );
	static void nop14( VM &vm );
	static void nop15( VM &vm );
	/* end of OP 0x80 series */

	static void halt( VM &vm );
	static void ldidt( VM &vm );
	static void modidt( VM &vm, dispb offset, dword imm );
	static void setidt( VM &vm, addr addr ); // a DWORD ptr, not a WORD ptr.
	static void sti( VM &vm );
	static void movk( VM &vm, crid dstreg, regid srcreg );
	static void cli( VM &vm );
	static void copk( VM &vm, regid dstreg, crid srcreg );
	static void sysret( VM &vm );


	sdword distrubite( VM &vm );
};

#endif // HA32S_H_VMINST_