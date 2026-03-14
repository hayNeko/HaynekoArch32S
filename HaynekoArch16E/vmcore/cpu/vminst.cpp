#include "h/general.hpp"
#include "h/vm.hpp"
#include <stdexcept>

#include "cpu/vminst.hpp"

void VMInst::nop( VM &vm ) {
	// do nothing
}

void VMInst::mov( VM &vm, regid dstreg, regid srcreg ) {
	vm.registers.writeReg( dstreg, vm.registers.readReg( srcreg ) );
}

void VMInst::entr( VM &vm ) {
	// Enter: set BP = SP
	vm.registers.writeReg( VMGPR::BP, vm.registers.readReg( VMGPR::SP ) );
}

void VMInst::leav( VM &vm ) {
	// Leave: set SP = BP
	vm.registers.writeReg( VMGPR::SP, vm.registers.readReg( VMGPR::BP ) );
}

void VMInst::jmp( VM &vm, dispw offset ) {
	vm.setIP( static_cast<addr>( vm.getIP() + offset ) );
}

void VMInst::jmpr( VM &vm, regid dstreg ) {
	vm.setIP( static_cast<addr>( vm.registers.readReg( dstreg ) ) );
}

void VMInst::call( VM &vm, dispw offset ) {
	// push return address (current IP) then jump relative
	vm.stpush( vm.getIP() );
	vm.setIP( static_cast<addr>( vm.getIP() + offset ) );
}

void VMInst::callr( VM &vm, regid dstreg ) {
	vm.stpush( vm.getIP() );
	vm.setIP( static_cast<addr>( vm.registers.readReg( dstreg ) ) );
}

void VMInst::ret( VM &vm ) {
	dword retaddr = vm.stpop();
	vm.setIP( static_cast<addr>( retaddr ) );
}

void VMInst::push( VM &vm, regid srcreg ) {
	vm.stpush( srcreg );
}

void VMInst::pop( VM &vm, regid dstreg ) {
	dword val = vm.stpop();
	vm.writeRegister( dstreg, val );
}

void VMInst::push_ra( VM &vm ) { vm.stpush( VMGPR::RA ); }
void VMInst::push_rb( VM &vm ) { vm.stpush( VMGPR::RB ); }
void VMInst::push_rc( VM &vm ) { vm.stpush( VMGPR::RC ); }
void VMInst::push_rd( VM &vm ) { vm.stpush( VMGPR::RD ); }
void VMInst::push_ri( VM &vm ) { vm.stpush( VMGPR::RI ); }
void VMInst::push_bp( VM &vm ) { vm.stpush( VMGPR::BP ); }

void VMInst::pop_ra( VM &vm ) { vm.registers.writeReg( VMGPR::RA, vm.stpop() ); }
void VMInst::pop_rb( VM &vm ) { vm.registers.writeReg( VMGPR::RB, vm.stpop() ); }
void VMInst::pop_rc( VM &vm ) { vm.registers.writeReg( VMGPR::RC, vm.stpop() ); }
void VMInst::pop_rd( VM &vm ) { vm.registers.writeReg( VMGPR::RD, vm.stpop() ); }
void VMInst::pop_ri( VM &vm ) { vm.registers.writeReg( VMGPR::RI, vm.stpop() ); }
void VMInst::pop_bp( VM &vm ) { vm.registers.writeReg( VMGPR::BP, vm.stpop() ); }

void VMInst::puship( VM &vm ) {
	vm.stpush( vm.getIP() );
}

void VMInst::copyip( VM &vm, regid dstreg ) {
	vm.writeRegister( dstreg, static_cast<dword>( vm.getIP() ) );
}

void VMInst::cmp( VM &vm, regid dstreg, regid srcreg ) {
	dword a = vm.registers.readReg( dstreg );
	dword b = vm.registers.readReg( srcreg );
	dword res = a - b;

	// Zero flag
	if ( res == 0 ) vm.flags.set( VMFlag::Z ); else vm.flags.clear( VMFlag::Z );

	// Carry flag for subtraction: set when borrow (a < b)
	if ( a < b ) vm.flags.set( VMFlag::C ); else vm.flags.clear( VMFlag::C );

	// Negative flag: sign bit of result
	if ( res & DWORD_SIGN ) vm.flags.set( VMFlag::N ); else vm.flags.clear( VMFlag::N );

	// Overflow flag: signed overflow detection for subtraction
	bool overflow = ( ( ( a ^ b ) & ( a ^ res ) ) & DWORD_SIGN ) != 0;
	if ( overflow ) vm.flags.set( VMFlag::O ); else vm.flags.clear( VMFlag::O );
}

void VMInst::jz( VM &vm, dispw offset ) {
	if ( vm.flags.get( VMFlag::Z ) ) vm.setIP( static_cast<addr>( vm.getIP() + offset ) );
}

void VMInst::jnz( VM &vm, dispw offset ) {
	if ( !vm.flags.get( VMFlag::Z ) ) vm.setIP( static_cast<addr>( vm.getIP() + offset ) );
}

void VMInst::jc( VM &vm, dispw offset ) {
	if ( vm.flags.get( VMFlag::C ) ) vm.setIP( static_cast<addr>( vm.getIP() + offset ) );
}

void VMInst::jnc( VM &vm, dispw offset ) {
	if ( !vm.flags.get( VMFlag::C ) ) vm.setIP( static_cast<addr>( vm.getIP() + offset ) );
}

void VMInst::jo( VM &vm, dispw offset ) {
	if ( vm.flags.get( VMFlag::O ) ) vm.setIP( static_cast<addr>( vm.getIP() + offset ) );
}

void VMInst::jno( VM &vm, dispw offset ) {
	if ( !vm.flags.get( VMFlag::O ) ) vm.setIP( static_cast<addr>( vm.getIP() + offset ) );
}

void VMInst::jn( VM &vm, dispw offset ) {
	if ( vm.flags.get( VMFlag::N ) ) vm.setIP( static_cast<addr>( vm.getIP() + offset ) );
}

void VMInst::jnn( VM &vm, dispw offset ) {
	if ( !vm.flags.get( VMFlag::N ) ) vm.setIP( static_cast<addr>( vm.getIP() + offset ) );
}

void VMInst::jl( VM &vm, dispw offset ) {
	// signed less: NF != OF
	bool nf = vm.flags.get( VMFlag::N );
	bool of = vm.flags.get( VMFlag::O );
	if ( nf != of ) vm.setIP( static_cast<addr>( vm.getIP() + offset ) );
}

void VMInst::jge( VM &vm, dispw offset ) {
	// signed greater or equal: NF == OF
	bool nf = vm.flags.get( VMFlag::N );
	bool of = vm.flags.get( VMFlag::O );
	if ( nf == of ) vm.setIP( static_cast<addr>( vm.getIP() + offset ) );
}

void VMInst::ja( VM &vm, dispw offset ) {
	// unsigned above: CF == 0 && ZF == 0
	if ( !vm.flags.get( VMFlag::C ) && !vm.flags.get( VMFlag::Z ) ) vm.setIP( static_cast<addr>( vm.getIP() + offset ) );
}

void VMInst::jbe( VM &vm, dispw offset ) {
	// unsigned below or equal: CF == 1 || ZF == 1
	if ( vm.flags.get( VMFlag::C ) || vm.flags.get( VMFlag::Z ) ) vm.setIP( static_cast<addr>( vm.getIP() + offset ) );
}

void VMInst::jle( VM &vm, dispw offset ) {
	// signed less or equal: ZF == 1 || NF != OF
	if ( vm.flags.get( VMFlag::Z ) || ( vm.flags.get( VMFlag::N ) != vm.flags.get( VMFlag::O ) ) ) vm.setIP( static_cast<addr>( vm.getIP() + offset ) );
}

void VMInst::jag( VM &vm, dispw offset ) {
	// Jump if Above or Greater: CF == 0 && ZF == 0 && NF == OF
	if ( !vm.flags.get( VMFlag::C ) && !vm.flags.get( VMFlag::Z ) && ( vm.flags.get( VMFlag::N ) == vm.flags.get( VMFlag::O ) ) )
		vm.setIP( static_cast<addr>( vm.getIP() + offset ) );
}

void VMInst::jmpfar( VM &vm, addr addr_val ) {
	vm.setIP( addr_val );
}

void VMInst::ld( VM &vm, regid dstreg, regid srcreg, dispb offset ) {
	// address = srcreg + offset (signed)
	sdword off = static_cast<sdword>( offset );
	addr address = static_cast<addr>( vm.registers.readReg( srcreg ) + off );
	dword val = vm.readMemory( address );
	vm.writeRegister( dstreg, val );
}

void VMInst::st( VM &vm, regid dstreg, regid srcreg, dispb offset ) {
	sdword off = static_cast<sdword>( offset );
	addr address = static_cast<addr>( vm.registers.readReg( dstreg ) + off );
	vm.writeMemory( address, vm.registers.readReg( srcreg ) );
}

void VMInst::ldofip( VM &vm, regid dstreg, dispw offset ) {
	sdword off = static_cast<sdword>( offset );
	addr address = static_cast<addr>( vm.getIP() + off );
	dword val = vm.readMemory( address );
	vm.writeRegister( dstreg, val );
}

void VMInst::stofip( VM &vm, regid dstreg, dispw offset ) {
	sdword off = static_cast<sdword>( offset );
	addr address = static_cast<addr>( vm.getIP() + off );
	vm.writeMemory( address, vm.registers.readReg( dstreg ) );
}

void VMInst::addsp( VM &vm, immb imm ) {
	regd sp = vm.registers.readReg( VMGPR::SP );
	sp += imm;
	vm.registers.writeReg( VMGPR::SP, sp );
}

void VMInst::subsp( VM &vm, immb imm ) {
	regd sp = vm.registers.readReg( VMGPR::SP );
	sp -= imm;
	vm.registers.writeReg( VMGPR::SP, sp );
}

void VMInst::pushimmdw( VM &vm, dword imm ) {
	vm.stpush( imm, 0 );
}

void VMInst::pushimmb( VM &vm, immb imm ) {
	vm.stpush( static_cast<immd>( imm ), 0 );
}

void VMInst::pushimmw( VM &vm, immw imm ) {
	vm.stpush( static_cast<immd>( imm ), 0 );
}

void VMInst::ldstval( VM &vm, regid dstreg, dispb offset ) {
	sdword off = static_cast<sdword>( offset );
	addr address = static_cast<addr>( vm.registers.readReg( VMGPR::SP ) + off );
	dword val = vm.readMemory( address );
	vm.writeRegister( dstreg, val );
}

void VMInst::ststval( VM &vm, regid dstreg, dispb offset ) {
	sdword off = static_cast<sdword>( offset );
	addr address = static_cast<addr>( vm.registers.readReg( VMGPR::SP ) + off );
	vm.writeMemory( address, vm.registers.readReg( dstreg ) );
}

// Logic operations
void VMInst::xorr( VM &vm, regid dstreg, regid srcreg, regid srcreg2 ) {
	dword a = vm.registers.readReg( srcreg );
	dword b = vm.registers.readReg( srcreg2 );
	dword res = a ^ b;
	vm.registers.writeReg( dstreg, res );
	// set flags: Z and N, clear C and O
	if ( res == 0 ) vm.flags.set( VMFlag::Z ); else vm.flags.clear( VMFlag::Z );
	if ( res & DWORD_SIGN ) vm.flags.set( VMFlag::N ); else vm.flags.clear( VMFlag::N );
	vm.flags.clear( VMFlag::C ); vm.flags.clear( VMFlag::O );
}

void VMInst::andr( VM &vm, regid dstreg, regid srcreg, regid srcreg2 ) {
	dword a = vm.registers.readReg( srcreg );
	dword b = vm.registers.readReg( srcreg2 );
	dword res = a & b;
	vm.registers.writeReg( dstreg, res );
	if ( res == 0 ) vm.flags.set( VMFlag::Z ); else vm.flags.clear( VMFlag::Z );
	if ( res & DWORD_SIGN ) vm.flags.set( VMFlag::N ); else vm.flags.clear( VMFlag::N );
	vm.flags.clear( VMFlag::C ); vm.flags.clear( VMFlag::O );
}

void VMInst::orr( VM &vm, regid dstreg, regid srcreg, regid srcreg2 ) {
	dword a = vm.registers.readReg( srcreg );
	dword b = vm.registers.readReg( srcreg2 );
	dword res = a | b;
	vm.registers.writeReg( dstreg, res );
	if ( res == 0 ) vm.flags.set( VMFlag::Z ); else vm.flags.clear( VMFlag::Z );
	if ( res & DWORD_SIGN ) vm.flags.set( VMFlag::N ); else vm.flags.clear( VMFlag::N );
	vm.flags.clear( VMFlag::C ); vm.flags.clear( VMFlag::O );
}

void VMInst::notr( VM &vm, regid dstreg, regid srcreg ) {
	dword a = vm.registers.readReg( srcreg );
	dword res = ~a;
	vm.registers.writeReg( dstreg, res );
	if ( res == 0 ) vm.flags.set( VMFlag::Z ); else vm.flags.clear( VMFlag::Z );
	if ( res & DWORD_SIGN ) vm.flags.set( VMFlag::N ); else vm.flags.clear( VMFlag::N );
	vm.flags.clear( VMFlag::C ); vm.flags.clear( VMFlag::O );
}

// Immediate logic
void VMInst::xori( VM &vm, regid dstreg, regid srcreg, immb imm ) {
	dword a = vm.registers.readReg( srcreg );
	dword res = a ^ static_cast<dword>( static_cast<byte>( imm ) );
	vm.registers.writeReg( dstreg, res );
	if ( res == 0 ) vm.flags.set( VMFlag::Z ); else vm.flags.clear( VMFlag::Z );
}

void VMInst::andi( VM &vm, regid dstreg, regid srcreg, immb imm ) {
	dword a = vm.registers.readReg( srcreg );
	dword res = a & static_cast<dword>( static_cast<byte>( imm ) );
	vm.registers.writeReg( dstreg, res );
	if ( res == 0 ) vm.flags.set( VMFlag::Z ); else vm.flags.clear( VMFlag::Z );
}

void VMInst::ori( VM &vm, regid dstreg, regid srcreg, immb imm ) {
	dword a = vm.registers.readReg( srcreg );
	dword res = a | static_cast<dword>( static_cast<byte>( imm ) );
	vm.registers.writeReg( dstreg, res );
	if ( res == 0 ) vm.flags.set( VMFlag::Z ); else vm.flags.clear( VMFlag::Z );
}

// Arithmetic
void VMInst::add( VM &vm, regid dstreg, regid srcreg, regid srcreg2 ) {
	dword a = vm.registers.readReg( srcreg );
	dword b = vm.registers.readReg( srcreg2 );
	dword res = a + b;
	vm.registers.writeReg( dstreg, res );
	// Zero
	if ( res == 0 ) vm.flags.set( VMFlag::Z ); else vm.flags.clear( VMFlag::Z );
	// Carry: unsigned overflow
	if ( res < a ) vm.flags.set( VMFlag::C ); else vm.flags.clear( VMFlag::C );
	// Negative
	if ( res & DWORD_SIGN ) vm.flags.set( VMFlag::N ); else vm.flags.clear( VMFlag::N );
	// Overflow: signed overflow
	bool overflow = ( ( ~( a ^ b ) & ( a ^ res ) ) & DWORD_SIGN ) != 0;
	if ( overflow ) vm.flags.set( VMFlag::O ); else vm.flags.clear( VMFlag::O );
}

void VMInst::sub( VM &vm, regid dstreg, regid srcreg, regid srcreg2 ) {
	dword a = vm.registers.readReg( srcreg );
	dword b = vm.registers.readReg( srcreg2 );
	dword res = a - b;
	vm.registers.writeReg( dstreg, res );
	if ( res == 0 ) vm.flags.set( VMFlag::Z ); else vm.flags.clear( VMFlag::Z );
	if ( a < b ) vm.flags.set( VMFlag::C ); else vm.flags.clear( VMFlag::C );
	if ( res & DWORD_SIGN ) vm.flags.set( VMFlag::N ); else vm.flags.clear( VMFlag::N );
	bool overflow = ( ( ( a ^ b ) & ( a ^ res ) ) & DWORD_SIGN ) != 0;
	if ( overflow ) vm.flags.set( VMFlag::O ); else vm.flags.clear( VMFlag::O );
}

void VMInst::inc( VM &vm, regid dstreg, regid srcreg ) {
	dword a = vm.registers.readReg( srcreg );
	dword res = a + 1;
	vm.registers.writeReg( dstreg, res );
	if ( res == 0 ) vm.flags.set( VMFlag::Z ); else vm.flags.clear( VMFlag::Z );
	if ( res & DWORD_SIGN ) vm.flags.set( VMFlag::N ); else vm.flags.clear( VMFlag::N );
}

void VMInst::dec( VM &vm, regid dstreg, regid srcreg ) {
	dword a = vm.registers.readReg( srcreg );
	dword res = a - 1;
	vm.registers.writeReg( dstreg, res );
	if ( res == 0 ) vm.flags.set( VMFlag::Z ); else vm.flags.clear( VMFlag::Z );
	if ( res & DWORD_SIGN ) vm.flags.set( VMFlag::N ); else vm.flags.clear( VMFlag::N );
}

void VMInst::neg( VM &vm, regid dstreg, regid srcreg ) {
	dword a = vm.registers.readReg( srcreg );
	dword res = static_cast<dword>( 0u - a );
	vm.registers.writeReg( dstreg, res );
	if ( res == 0 ) vm.flags.set( VMFlag::Z ); else vm.flags.clear( VMFlag::Z );
	if ( res & DWORD_SIGN ) vm.flags.set( VMFlag::N ); else vm.flags.clear( VMFlag::N );
}

void VMInst::abs( VM &vm, regid dstreg, regid srcreg ) {
	sdword a = static_cast<sdword>( vm.registers.readReg( srcreg ) );
	sdword r = a < 0 ? -a : a;
	vm.registers.writeReg( dstreg, static_cast<dword>( r ) );
	if ( r == 0 ) vm.flags.set( VMFlag::Z ); else vm.flags.clear( VMFlag::Z );
}

// Mul/Div
void VMInst::mul( VM &vm, regid dstreg, regid srcreg, regid srcreg2, regid srcreg3 ) {
	qword a = vm.registers.readReg( srcreg );
	qword b = vm.registers.readReg( srcreg2 );
	qword prod = a * b;
	vm.registers.writeReg( dstreg, static_cast<dword>( prod & DWORD_RANGE ) );
	vm.registers.writeReg( srcreg3, static_cast<dword>( ( prod >> 32 ) & DWORD_RANGE ) );
}

void VMInst::div( VM &vm, regid dstreg, regid srcreg, regid srcreg2, regid srcreg3 ) {
	dword a = vm.registers.readReg( srcreg );
	dword b = vm.registers.readReg( srcreg2 );
	if ( b == 0 ) throw std::runtime_error( "Division by zero" );
	dword q = a / b;
	dword r = a % b;
	vm.registers.writeReg( dstreg, q );
	vm.registers.writeReg( srcreg3, r );
}

// immediate double-word add/sub
void VMInst::addidw( VM &vm, regid dstreg, regid srcreg, dword imm ) {
	dword a = vm.registers.readReg( srcreg );
	dword res = a + imm;
	vm.registers.writeReg( dstreg, res );
}

void VMInst::subidw( VM &vm, regid dstreg, regid srcreg, dword imm ) {
	dword a = vm.registers.readReg( srcreg );
	dword res = a - imm;
	vm.registers.writeReg( dstreg, res );
}

void VMInst::random( VM &vm ) {
	// simple random using RA as seed
	dword seed = vm.registers.readReg( VMGPR::RA );
	dword val = ::random( seed );
	vm.registers.writeReg( VMGPR::RD, val );
}

// Helper: mask shift count to 0..31
static inline unsigned norm_count( unsigned c ) {
	return c & 31u;
}

// update basic flags after result
static inline void update_zn_flags( VM &vm, dword res ) {
	if ( res == 0 ) vm.flags.set( VMFlag::Z ); else vm.flags.clear( VMFlag::Z );
	if ( res & DWORD_SIGN ) vm.flags.set( VMFlag::N ); else vm.flags.clear( VMFlag::N );
}

// Logical left shift (immediate)
void VMInst::shl( VM &vm, regid dstreg, regid srcreg, immb imm ) {
	dword a = vm.registers.readReg( srcreg );
	unsigned cnt = norm_count( imm );
	if ( cnt == 0 ) return; // no change, CF preserved
	dword res = ( cnt < 32 ) ? static_cast<dword>( a << cnt ) : 0;
	// CF = last bit shifted out: bit (32 - cnt)
	if ( cnt <= 32 ) {
		byte cf = static_cast<byte>( ( a >> ( 32 - cnt ) ) & 1u );
		if ( cf ) vm.flags.set( VMFlag::C ); else vm.flags.clear( VMFlag::C );
	}
	// OF defined for cnt == 1: XOR of MSB before and after
	if ( cnt == 1 ) {
		bool msb_before = ( a & DWORD_SIGN );
		bool msb_after = ( res & DWORD_SIGN );
		if ( msb_before ^ msb_after ) vm.flags.set( VMFlag::O ); else vm.flags.clear( VMFlag::O );
	}
	else {
		vm.flags.clear( VMFlag::O );
	}
	vm.registers.writeReg( dstreg, res );
	update_zn_flags( vm, res );
}

// Logical right shift (immediate)
void VMInst::shr( VM &vm, regid dstreg, regid srcreg, immb imm ) {
	dword a = vm.registers.readReg( srcreg );
	unsigned cnt = norm_count( imm );
	if ( cnt == 0 ) return;
	dword res = ( cnt < 32 ) ? static_cast<dword>( a >> cnt ) : 0;
	// CF = last bit shifted out: bit (cnt-1)
	if ( cnt <= 32 ) {
		byte cf = static_cast<byte>( ( a >> ( cnt - 1 ) ) & 1u );
		if ( cf ) vm.flags.set( VMFlag::C ); else vm.flags.clear( VMFlag::C );
	}
	// OF defined for cnt == 1: MSB before
	if ( cnt == 1 ) {
		if ( a & DWORD_SIGN ) vm.flags.set( VMFlag::O ); else vm.flags.clear( VMFlag::O );
	}
	else {
		vm.flags.clear( VMFlag::O );
	}
	vm.registers.writeReg( dstreg, res );
	update_zn_flags( vm, res );
}

// Arithmetic right shift (immediate)
void VMInst::sar( VM &vm, regid dstreg, regid srcreg, immb imm ) {
	dword a = vm.registers.readReg( srcreg );
	unsigned cnt = norm_count( imm );
	if ( cnt == 0 ) return;
	sdword as = static_cast<sdword>( a );
	sdword rs = ( cnt < 32 ) ? static_cast<sdword>( as >> cnt ) : ( as < 0 ? -1 : 0 );
	dword res = static_cast<dword>( rs );
	// CF = last bit shifted out
	if ( cnt <= 32 ) {
		byte cf = static_cast<byte>( ( a >> ( cnt - 1 ) ) & 1u );
		if ( cf ) vm.flags.set( VMFlag::C ); else vm.flags.clear( VMFlag::C );
	}
	// OF cleared for arithmetic right shift
	vm.flags.clear( VMFlag::O );
	vm.registers.writeReg( dstreg, res );
	update_zn_flags( vm, res );
}

// Register-count variants: shift/rotate by amount in register (low 5 bits)
void VMInst::shlr( VM &vm, regid dstreg, regid srcreg ) {
	unsigned cnt = norm_count( vm.registers.readReg( srcreg ) );
	// reuse shl logic by passing immediate
	shl( vm, dstreg, dstreg, static_cast<immb>( cnt ) );
}

void VMInst::shrr( VM &vm, regid dstreg, regid srcreg ) {
	unsigned cnt = norm_count( vm.registers.readReg( srcreg ) );
	shr( vm, dstreg, dstreg, static_cast<immb>( cnt ) );
}

void VMInst::sarr( VM &vm, regid dstreg, regid srcreg ) {
	unsigned cnt = norm_count( vm.registers.readReg( srcreg ) );
	sar( vm, dstreg, dstreg, static_cast<immb>( cnt ) );
}

// Rotate left (immediate)
void VMInst::rol( VM &vm, regid dstreg, regid srcreg, immb imm ) {
	dword a = vm.registers.readReg( srcreg );
	unsigned cnt = norm_count( imm );
	if ( cnt == 0 ) return;
	unsigned n = cnt % 32;
	dword res = ( a << n ) | ( a >> ( 32 - n ) );
	// CF = bit (32 - n) of original
	byte cf = static_cast<byte>( ( a >> ( 32 - n ) ) & 1u );
	if ( cf ) vm.flags.set( VMFlag::C ); else vm.flags.clear( VMFlag::C );
	// OF defined for n == 1: XOR of MSB and CF
	if ( n == 1 ) {
		bool msb = ( res & DWORD_SIGN );
		if ( msb ^ static_cast<bool>( cf ) ) vm.flags.set( VMFlag::O ); else vm.flags.clear( VMFlag::O );
	}
	else vm.flags.clear( VMFlag::O );
	vm.registers.writeReg( dstreg, res );
	update_zn_flags( vm, res );
}

// Rotate right (immediate)
void VMInst::ror( VM &vm, regid dstreg, regid srcreg, immb imm ) {
	dword a = vm.registers.readReg( srcreg );
	unsigned cnt = norm_count( imm );
	if ( cnt == 0 ) return;
	unsigned n = cnt % 32;
	dword res = ( a >> n ) | ( a << ( 32 - n ) );
	// CF = bit (n-1) of original
	byte cf = static_cast<byte>( ( a >> ( n - 1 ) ) & 1u );
	if ( cf ) vm.flags.set( VMFlag::C ); else vm.flags.clear( VMFlag::C );
	// OF defined for n == 1: XOR of MSB and next MSB
	if ( n == 1 ) {
		bool msb = ( res & DWORD_SIGN );
		bool next = static_cast<bool>( ( res >> 30 ) & 1u );
		if ( msb ^ next ) vm.flags.set( VMFlag::O ); else vm.flags.clear( VMFlag::O );
	}
	else vm.flags.clear( VMFlag::O );
	vm.registers.writeReg( dstreg, res );
	update_zn_flags( vm, res );
}

void VMInst::rolr( VM &vm, regid dstreg, regid srcreg ) {
	unsigned cnt = norm_count( vm.registers.readReg( srcreg ) );
	rol( vm, dstreg, dstreg, static_cast<immb>( cnt ) );
}

void VMInst::rorr( VM &vm, regid dstreg, regid srcreg ) {
	unsigned cnt = norm_count( vm.registers.readReg( srcreg ) );
	ror( vm, dstreg, dstreg, static_cast<immb>( cnt ) );
}

// --- Additional instruction implementations (from JSON) ---
void VMInst::lea( VM &vm, regid dstreg, regid srcreg, dispb offset ) {
	sdword off = static_cast<sdword>( offset );
	addr address = static_cast<addr>( vm.registers.readReg( srcreg ) + off );
	vm.registers.writeReg( dstreg, static_cast<dword>( address ) );
}

void VMInst::leasc( VM &vm, regid dstreg, regid srcreg, factor factor, regid srcreg2, dispb offset ) {
	// Effective Address = SR1 + (SR2 * SCL) + OF8
	unsigned scale = 1u << static_cast<unsigned>( factor );
	sdword off = static_cast<sdword>( offset );
	dword base = vm.registers.readReg( srcreg );
	dword idx = vm.registers.readReg( srcreg2 );
	addr address = static_cast<addr>( base + idx * scale + off );
	vm.registers.writeReg( dstreg, static_cast<dword>( address ) );
}

void VMInst::brk( VM &vm ) {
	vm.interrupt( 0 );
}

void VMInst::intr( VM &vm, byte imm ) {
	vm.interrupt( imm );
}

void VMInst::iret( VM &vm ) {
	// Return from interrupt
	vm.sysret();
}

void VMInst::in( VM &vm, portid port ) {
	dword val = vm.in( port );
	vm.registers.writeReg( VMGPR::RI, val );
}

void VMInst::out( VM &vm, portid port ) {
	dword val = vm.registers.readReg( VMGPR::RI );
	vm.out( port, val );
}

void VMInst::syscall( VM &vm ) {
	vm.syscall();
}

// Conditional moves
void VMInst::movz( VM &vm, regid dstreg, regid srcreg ) { if ( vm.flags.get( VMFlag::Z ) ) vm.registers.writeReg( dstreg, vm.registers.readReg( srcreg ) ); }
void VMInst::movc( VM &vm, regid dstreg, regid srcreg ) { if ( vm.flags.get( VMFlag::C ) ) vm.registers.writeReg( dstreg, vm.registers.readReg( srcreg ) ); }
void VMInst::movo( VM &vm, regid dstreg, regid srcreg ) { if ( vm.flags.get( VMFlag::O ) ) vm.registers.writeReg( dstreg, vm.registers.readReg( srcreg ) ); }
void VMInst::movn( VM &vm, regid dstreg, regid srcreg ) { if ( vm.flags.get( VMFlag::N ) ) vm.registers.writeReg( dstreg, vm.registers.readReg( srcreg ) ); }
void VMInst::movnz( VM &vm, regid dstreg, regid srcreg ) { if ( !vm.flags.get( VMFlag::Z ) ) vm.registers.writeReg( dstreg, vm.registers.readReg( srcreg ) ); }
void VMInst::movnc( VM &vm, regid dstreg, regid srcreg ) { if ( !vm.flags.get( VMFlag::C ) ) vm.registers.writeReg( dstreg, vm.registers.readReg( srcreg ) ); }
void VMInst::movno( VM &vm, regid dstreg, regid srcreg ) { if ( !vm.flags.get( VMFlag::O ) ) vm.registers.writeReg( dstreg, vm.registers.readReg( srcreg ) ); }
void VMInst::movnn( VM &vm, regid dstreg, regid srcreg ) { if ( !vm.flags.get( VMFlag::N ) ) vm.registers.writeReg( dstreg, vm.registers.readReg( srcreg ) ); }
void VMInst::movl( VM &vm, regid dstreg, regid srcreg ) { if ( vm.flags.get( VMFlag::N ) != vm.flags.get( VMFlag::O ) ) vm.registers.writeReg( dstreg, vm.registers.readReg( srcreg ) ); }
void VMInst::movge( VM &vm, regid dstreg, regid srcreg ) { if ( vm.flags.get( VMFlag::N ) == vm.flags.get( VMFlag::O ) ) vm.registers.writeReg( dstreg, vm.registers.readReg( srcreg ) ); }
void VMInst::mova( VM &vm, regid dstreg, regid srcreg ) { if ( !vm.flags.get( VMFlag::C ) && !vm.flags.get( VMFlag::Z ) ) vm.registers.writeReg( dstreg, vm.registers.readReg( srcreg ) ); }
void VMInst::movbe( VM &vm, regid dstreg, regid srcreg ) { if ( vm.flags.get( VMFlag::C ) || vm.flags.get( VMFlag::Z ) ) vm.registers.writeReg( dstreg, vm.registers.readReg( srcreg ) ); }
void VMInst::movle( VM &vm, regid dstreg, regid srcreg ) { if ( vm.flags.get( VMFlag::Z ) || ( vm.flags.get( VMFlag::N ) != vm.flags.get( VMFlag::O ) ) ) vm.registers.writeReg( dstreg, vm.registers.readReg( srcreg ) ); }
void VMInst::movag( VM &vm, regid dstreg, regid srcreg ) { if ( !vm.flags.get( VMFlag::C ) && !vm.flags.get( VMFlag::Z ) && ( vm.flags.get( VMFlag::N ) == vm.flags.get( VMFlag::O ) ) ) vm.registers.writeReg( dstreg, vm.registers.readReg( srcreg ) ); }

void VMInst::pushtr( VM &vm, regid sr1, regid sr2, regid sr3 ) {
	vm.stpush3( sr1, sr2, sr3 );
}

void VMInst::poptr( VM &vm, regid dst1, regid dst2, regid dst3 ) {
	// pop in order: dst1, dst2, dst3
	vm.registers.writeReg( dst1, vm.stpop() );
	vm.registers.writeReg( dst2, vm.stpop() );
	vm.registers.writeReg( dst3, vm.stpop() );
}

void VMInst::ldstvalow( VM &vm, regid dstreg, dispw offset ) {
	sdword off = static_cast<sdword>( offset );
	addr address = static_cast<addr>( vm.registers.readReg( VMGPR::SP ) + off );
	dword val = vm.readMemory( address );
	vm.registers.writeReg( dstreg, val );
}

void VMInst::ststvalow( VM &vm, regid srcreg, dispw offset ) {
	sdword off = static_cast<sdword>( offset );
	addr address = static_cast<addr>( vm.registers.readReg( VMGPR::SP ) + off );
	vm.writeMemory( address, vm.registers.readReg( srcreg ) );
}

void VMInst::pushf( VM &vm ) {
	dword val = 0;
	if ( vm.flags.get( VMFlag::Z ) ) setBit( val, VMFlag::Z_SIGN );
	if ( vm.flags.get( VMFlag::C ) ) setBit( val, VMFlag::C_SIGN );
	if ( vm.flags.get( VMFlag::O ) ) setBit( val, VMFlag::O_SIGN );
	if ( vm.flags.get( VMFlag::N ) ) setBit( val, VMFlag::N_SIGN );
	if ( vm.flags.get( VMFlag::FLZ ) ) setBit( val, VMFlag::FLZ_SIGN );
	if ( vm.flags.get( VMFlag::FLO ) ) setBit( val, VMFlag::FLO_SIGN );
	if ( vm.flags.get( VMFlag::FLV ) ) setBit( val, VMFlag::FLV_SIGN );
	if ( vm.flags.get( VMFlag::IF ) ) setBit( val, VMFlag::IF_SIGN );
	if ( vm.flags.get( VMFlag::BE ) ) setBit( val, VMFlag::BE_SIGN );
	if ( vm.flags.get( VMFlag::AC ) ) setBit( val, VMFlag::AC_SIGN );
	vm.stpush( val, 0 );
}

void VMInst::popf( VM &vm ) {
	dword val = vm.stpop();
	if ( isBitSet( val, VMFlag::Z_SIGN ) ) vm.flags.set( VMFlag::Z ); else vm.flags.clear( VMFlag::Z );
	if ( isBitSet( val, VMFlag::C_SIGN ) ) vm.flags.set( VMFlag::C ); else vm.flags.clear( VMFlag::C );
	if ( isBitSet( val, VMFlag::O_SIGN ) ) vm.flags.set( VMFlag::O ); else vm.flags.clear( VMFlag::O );
	if ( isBitSet( val, VMFlag::N_SIGN ) ) vm.flags.set( VMFlag::N ); else vm.flags.clear( VMFlag::N );
	if ( isBitSet( val, VMFlag::FLZ_SIGN ) ) vm.flags.set( VMFlag::FLZ ); else vm.flags.clear( VMFlag::FLZ );
	if ( isBitSet( val, VMFlag::FLO_SIGN ) ) vm.flags.set( VMFlag::FLO ); else vm.flags.clear( VMFlag::FLO );
	if ( isBitSet( val, VMFlag::FLV_SIGN ) ) vm.flags.set( VMFlag::FLV ); else vm.flags.clear( VMFlag::FLV );
	if ( isBitSet( val, VMFlag::IF_SIGN ) ) vm.flags.set( VMFlag::IF ); else vm.flags.clear( VMFlag::IF );
	if ( isBitSet( val, VMFlag::BE_SIGN ) ) vm.flags.set( VMFlag::BE ); else vm.flags.clear( VMFlag::BE );
	if ( isBitSet( val, VMFlag::AC_SIGN ) ) vm.flags.set( VMFlag::AC ); else vm.flags.clear( VMFlag::AC );
}

void VMInst::clr_ra( VM &vm ) {
	vm.registers.writeReg( VMGPR::RA, 0 );
}

void VMInst::xchg( VM &vm, regid dstreg, regid srcreg ) {
	dword a = vm.registers.readReg( dstreg );
	dword b = vm.registers.readReg( srcreg );
	vm.registers.writeReg( dstreg, b );
	vm.registers.writeReg( srcreg, a );
}

void VMInst::addib( VM &vm, regid dstreg, regid srcreg, immb imm ) {
	dword a = vm.registers.readReg( srcreg );
	dword b = static_cast<dword>( static_cast<byte>( imm ) );
	dword res = a + b;
	vm.registers.writeReg( dstreg, res );
	if ( res == 0 ) vm.flags.set( VMFlag::Z ); else vm.flags.clear( VMFlag::Z );
	if ( res < a ) vm.flags.set( VMFlag::C ); else vm.flags.clear( VMFlag::C );
	if ( res & DWORD_SIGN ) vm.flags.set( VMFlag::N ); else vm.flags.clear( VMFlag::N );
	bool overflow = ( ( ~( a ^ b ) & ( a ^ res ) ) & DWORD_SIGN ) != 0;
	if ( overflow ) vm.flags.set( VMFlag::O ); else vm.flags.clear( VMFlag::O );
}

void VMInst::subib( VM &vm, regid dstreg, regid srcreg, immb imm ) {
	dword a = vm.registers.readReg( srcreg );
	dword b = static_cast<dword>( static_cast<byte>( imm ) );
	dword res = a - b;
	vm.registers.writeReg( dstreg, res );
	if ( res == 0 ) vm.flags.set( VMFlag::Z ); else vm.flags.clear( VMFlag::Z );
	if ( a < b ) vm.flags.set( VMFlag::C ); else vm.flags.clear( VMFlag::C );
	if ( res & DWORD_SIGN ) vm.flags.set( VMFlag::N ); else vm.flags.clear( VMFlag::N );
	bool overflow = ( ( ( a ^ b ) & ( a ^ res ) ) & DWORD_SIGN ) != 0;
	if ( overflow ) vm.flags.set( VMFlag::O ); else vm.flags.clear( VMFlag::O );
}

void VMInst::smul( VM &vm, regid dstreg, regid srcreg, regid srcreg2, regid srcreg3 ) {
	sqword a = static_cast<sqword>( static_cast<sdword>( vm.registers.readReg( srcreg ) ) );
	sqword b = static_cast<sqword>( static_cast<sdword>( vm.registers.readReg( srcreg2 ) ) );
	sqword prod = a * b;
	vm.registers.writeReg( dstreg, static_cast<dword>( prod & DWORD_RANGE ) );
	vm.registers.writeReg( srcreg3, static_cast<dword>( ( prod >> 32 ) & DWORD_RANGE ) );
}

void VMInst::sdiv( VM &vm, regid dstreg, regid srcreg, regid srcreg2, regid srcreg3 ) {
	sdword a = static_cast<sdword>( vm.registers.readReg( srcreg ) );
	sdword b = static_cast<sdword>( vm.registers.readReg( srcreg2 ) );
	if ( b == 0 ) throw std::runtime_error( "Division by zero" );
	sdword q = a / b;
	sdword r = a % b;
	vm.registers.writeReg( dstreg, static_cast<dword>( q ) );
	vm.registers.writeReg( srcreg3, static_cast<dword>( r ) );
}

void VMInst::inc_rc( VM &vm ) {
	dword a = vm.registers.readReg( VMGPR::RC );
	dword res = a + 1;
	vm.registers.writeReg( VMGPR::RC, res );
	if ( res == 0 ) vm.flags.set( VMFlag::Z ); else vm.flags.clear( VMFlag::Z );
	if ( res & DWORD_SIGN ) vm.flags.set( VMFlag::N ); else vm.flags.clear( VMFlag::N );
	if ( res < a ) vm.flags.set( VMFlag::C ); else vm.flags.clear( VMFlag::C );
	bool overflow = ( ( ~( a ^ 1u ) & ( a ^ res ) ) & DWORD_SIGN ) != 0;
	if ( overflow ) vm.flags.set( VMFlag::O ); else vm.flags.clear( VMFlag::O );
}

void VMInst::dec_rc( VM &vm ) {
	dword a = vm.registers.readReg( VMGPR::RC );
	dword res = a - 1;
	vm.registers.writeReg( VMGPR::RC, res );
	if ( res == 0 ) vm.flags.set( VMFlag::Z ); else vm.flags.clear( VMFlag::Z );
	if ( res & DWORD_SIGN ) vm.flags.set( VMFlag::N ); else vm.flags.clear( VMFlag::N );
	if ( a < 1u ) vm.flags.set( VMFlag::C ); else vm.flags.clear( VMFlag::C );
	bool overflow = ( ( ( a ^ 1u ) & ( a ^ res ) ) & DWORD_SIGN ) != 0;
	if ( overflow ) vm.flags.set( VMFlag::O ); else vm.flags.clear( VMFlag::O );
}

void VMInst::xoridw( VM &vm, regid dstreg, regid srcreg, dword imm ) {
	dword a = vm.registers.readReg( srcreg );
	dword res = a ^ imm;
	vm.registers.writeReg( dstreg, res );
	if ( res == 0 ) vm.flags.set( VMFlag::Z ); else vm.flags.clear( VMFlag::Z );
	if ( res & DWORD_SIGN ) vm.flags.set( VMFlag::N ); else vm.flags.clear( VMFlag::N );
}

void VMInst::andidw( VM &vm, regid dstreg, regid srcreg, dword imm ) {
	dword a = vm.registers.readReg( srcreg );
	dword res = a & imm;
	vm.registers.writeReg( dstreg, res );
	if ( res == 0 ) vm.flags.set( VMFlag::Z ); else vm.flags.clear( VMFlag::Z );
	if ( res & DWORD_SIGN ) vm.flags.set( VMFlag::N ); else vm.flags.clear( VMFlag::N );
}

void VMInst::oridw( VM &vm, regid dstreg, regid srcreg, dword imm ) {
	dword a = vm.registers.readReg( srcreg );
	dword res = a | imm;
	vm.registers.writeReg( dstreg, res );
	if ( res == 0 ) vm.flags.set( VMFlag::Z ); else vm.flags.clear( VMFlag::Z );
	if ( res & DWORD_SIGN ) vm.flags.set( VMFlag::N ); else vm.flags.clear( VMFlag::N );
}

void VMInst::xnoridw( VM &vm, regid dstreg, regid srcreg, dword imm ) {
	dword a = vm.registers.readReg( srcreg );
	dword res = ~( a ^ imm );
	vm.registers.writeReg( dstreg, res );
	if ( res == 0 ) vm.flags.set( VMFlag::Z ); else vm.flags.clear( VMFlag::Z );
}

void VMInst::nandidw( VM &vm, regid dstreg, regid srcreg, dword imm ) {
	dword a = vm.registers.readReg( srcreg );
	dword res = ~( a & imm );
	vm.registers.writeReg( dstreg, res );
	if ( res == 0 ) vm.flags.set( VMFlag::Z ); else vm.flags.clear( VMFlag::Z );
}

void VMInst::noridw( VM &vm, regid dstreg, regid srcreg, dword imm ) {
	dword a = vm.registers.readReg( srcreg );
	dword res = ~( a | imm );
	vm.registers.writeReg( dstreg, res );
	if ( res == 0 ) vm.flags.set( VMFlag::Z ); else vm.flags.clear( VMFlag::Z );
}

// NOP variants
void VMInst::nop2( VM &vm ) {}
void VMInst::nop3( VM &vm ) {}
void VMInst::nop4( VM &vm ) {}
void VMInst::nop5( VM &vm ) {}
void VMInst::nop6( VM &vm ) {}
void VMInst::nop7( VM &vm ) {}
void VMInst::nop8( VM &vm ) {}
void VMInst::nop9( VM &vm ) {}
void VMInst::nop10( VM &vm ) {}
void VMInst::nop11( VM &vm ) {}
void VMInst::nop12( VM &vm ) {}
void VMInst::nop13( VM &vm ) {}
void VMInst::nop14( VM &vm ) {}
void VMInst::nop15( VM &vm ) {}

void VMInst::halt( VM &vm ) {
	vm.halt();
}

void VMInst::ldidt( VM &vm ) {
	// Load IDT register to RB (use control register index 3 as IDT)
	vm.registers.writeReg( VMGPR::RB, vm.control_registers.readCtrlReg( 3 ) );
}

void VMInst::modidt( VM &vm, dispb offset, dword imm ) {
	// Read IDT value from control register 3, add unsigned offset, and write imm to that address
	dword base = vm.control_registers.readCtrlReg( 3 );
	addr address = static_cast<addr>( base + static_cast<unsigned>( offset ) );
	vm.writeMemory( address, imm );
}

void VMInst::setidt( VM &vm, addr addr_val ) {
	vm.control_registers.writeCtrlReg( 3, static_cast<dword>( addr_val ) );
}

void VMInst::sti( VM &vm ) { vm.flags.set( VMFlag::IF ); }
void VMInst::cli( VM &vm ) { vm.flags.clear( VMFlag::IF ); }

void VMInst::movk( VM &vm, crid dstreg, regid srcreg ) {
	vm.control_registers.writeCtrlReg( dstreg, vm.registers.readReg( srcreg ) );
}

void VMInst::copk( VM &vm, regid dstreg, crid srcreg ) {
	vm.registers.writeReg( dstreg, vm.control_registers.readCtrlReg( srcreg ) );
}

void VMInst::sysret( VM &vm ) {
	vm.sysret();
}

sdword distrubite( VM &vm ) {
	// placeholder distribution helper
	return 0;
}