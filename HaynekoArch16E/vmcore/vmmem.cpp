#include <stdexcept>

#include "vmmem.hpp"
#include "general.hpp"

VMMem::VMMem(dword mem_size) : mem_size(mem_size)  {
	#ifndef VMMEM_CREATE_NO_WARNING
	if ( mem_size >= 1048576 )
		warn( "VMMem size is too large, it may cause performance issues" );
	#endif
	if ( mem_size <= 32768 )
		throw std::invalid_argument( "VMMem size must be greater than 32768" );
	mem_ptr = new byte[mem_size]();
}

VMMem::~VMMem() {
	delete[] mem_ptr;
}

void VMMem::writeq( addr address, qword data ) {
	// bounds check
	if ( address + 7 >= mem_size )
		throw std::out_of_range( "VMMem::writeq address out of range" );

	#ifdef VMENDIAN_LITTLE
	mem_ptr[address] = static_cast<byte>( data );
	mem_ptr[address + 1] = static_cast<byte>( data >> 8 );
	mem_ptr[address + 2] = static_cast<byte>( data >> 16 );
	mem_ptr[address + 3] = static_cast<byte>( data >> 24 );
	mem_ptr[address + 4] = static_cast<byte>( data >> 32 );
	mem_ptr[address + 5] = static_cast<byte>( data >> 40 );
	mem_ptr[address + 6] = static_cast<byte>( data >> 48 );
	mem_ptr[address + 7] = static_cast<byte>( data >> 56 );
	#else
	mem_ptr[address] = static_cast<byte>( data >> 56 );
	mem_ptr[address + 1] = static_cast<byte>( data >> 48 );
	mem_ptr[address + 2] = static_cast<byte>( data >> 40 );
	mem_ptr[address + 3] = static_cast<byte>( data >> 32 );
	mem_ptr[address + 4] = static_cast<byte>( data >> 24 );
	mem_ptr[address + 5] = static_cast<byte>( data >> 16 );
	mem_ptr[address + 6] = static_cast<byte>( data >> 8 );
	mem_ptr[address + 7] = static_cast<byte>( data );
	#endif
}

void VMMem::writed( addr address, dword data ) {
	// bounds check
	if ( address + 3 >= mem_size )
		throw std::out_of_range( "VMMem::writed address out of range" );

	#ifdef VMENDIAN_LITTLE
	mem_ptr[address] = static_cast<byte>( data );
	mem_ptr[address + 1] = static_cast<byte>( data >> 8 );
	mem_ptr[address + 2] = static_cast<byte>( data >> 16 );
	mem_ptr[address + 3] = static_cast<byte>( data >> 24 );
	#else
	mem_ptr[address] = static_cast<byte>( data >> 24 );
	mem_ptr[address + 1] = static_cast<byte>( data >> 16 );
	mem_ptr[address + 2] = static_cast<byte>( data >> 8 );
	mem_ptr[address + 3] = static_cast<byte>( data );
	#endif

}

void VMMem::writew( addr address, word data ) {
	// bounds check
	if ( address + 1 >= mem_size )
		throw std::out_of_range( "VMMem::writew address out of range" );

	#ifdef VMENDIAN_LITTLE
	mem_ptr[address] = static_cast<byte>( data );
	mem_ptr[address + 1] = static_cast<byte>( data >> 8 );
	#else
	mem_ptr[address] = static_cast<byte>( data >> 8 );
	mem_ptr[address + 1] = static_cast<byte>( data );
	#endif
}

void VMMem::writeb( addr address, byte data ) {
	// bounds check
	if ( address >= mem_size )
		throw std::out_of_range( "VMMem::writeb address out of range" );

	mem_ptr[address] = static_cast<byte>( data );
}

qword VMMem::readq( addr address ) {
	// bounds check
	if ( address + 7 >= mem_size )
		throw std::out_of_range( "VMMem::readq address out of range" );

	#ifdef VMENDIAN_LITTLE
	return
		static_cast<qword>( mem_ptr[address] ) |
		( static_cast<qword>( mem_ptr[address + 1] ) << 8 ) |
		( static_cast<qword>( mem_ptr[address + 2] ) << 16 ) |
		( static_cast<qword>( mem_ptr[address + 3] ) << 24 ) |
		( static_cast<qword>( mem_ptr[address + 4] ) << 32 ) |
		( static_cast<qword>( mem_ptr[address + 5] ) << 40 ) |
		( static_cast<qword>( mem_ptr[address + 6] ) << 48 ) |
		( static_cast<qword>( mem_ptr[address + 7] ) << 56 );
	#else
	return
		( static_cast<qword>( mem_ptr[address] ) << 56 ) |
		( static_cast<qword>( mem_ptr[address + 1] ) << 48 ) |
		( static_cast<qword>( mem_ptr[address + 2] ) << 40 ) |
		( static_cast<qword>( mem_ptr[address + 3] ) << 32 ) |
		( static_cast<qword>( mem_ptr[address + 4] ) << 24 ) |
		( static_cast<qword>( mem_ptr[address + 5] ) << 16 ) |
		( static_cast<qword>( mem_ptr[address + 6] ) << 8 ) |
		static_cast<qword>( mem_ptr[address + 7] );
	#endif
}

dword VMMem::readd( addr address ) {
	// bounds check
	if ( address + 3 >= mem_size )
		throw std::out_of_range( "VMMem::readd address out of range" );

	#ifdef VMENDIAN_LITTLE
	return
		static_cast<dword>( mem_ptr[address] ) |
		( static_cast<dword>( mem_ptr[address + 1] ) << 8 ) |
		( static_cast<dword>( mem_ptr[address + 2] ) << 16 ) |
		( static_cast<dword>( mem_ptr[address + 3] ) << 24 );
	#else
	return
		static_cast<dword>( mem_ptr[address] ) << 24 |
		( static_cast<dword>( mem_ptr[address + 1] ) << 16 ) |
		( static_cast<dword>( mem_ptr[address + 2] ) << 8 ) |
		static_cast<dword>( mem_ptr[address + 3] );
	#endif
}

word VMMem::readw( addr address ) {
	// bounds check
	if ( address + 1 >= mem_size )
		throw std::out_of_range( "VMMem::readw address out of range" );

	#ifdef VMENDIAN_LITTLE
	return
		static_cast<word>( mem_ptr[address] ) |
		( static_cast<word>( mem_ptr[address + 1] ) << 8 );
	#else
	return
		( static_cast<word>( mem_ptr[address] ) << 8 ) |
		static_cast<word>( mem_ptr[address + 1] );
	#endif
}

byte VMMem::readb( addr address ) {
	// bounds check
	if ( address >= mem_size )
		throw std::out_of_range( "VMMem::readb address out of range" );

	return static_cast<byte>( mem_ptr[address] );
}

