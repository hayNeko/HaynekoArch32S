#include <stdexcept>

#include "general.hpp"
#include "vmreg.hpp"

IP::IP() {
	this->ip = 0xFFFFFFFA; // JMP .program_entry  3E XX XX XX XX
}

IP::IP( addr ip_addr ) {
	this->ip = ip_addr;
}


void IP::modIp( addr ip_addr ) {
	this->ip = ip_addr;
}
addr IP::getIp() const {
	return this->ip;
}

GPR::GPR() {
	for ( int i = 0; i <= 31; ++i ) regs[i] = 0;
}
void GPR::writeReg( byte reg_num, dword data ) {
	if ( reg_num < 0 || reg_num >= 32 )
		throw std::out_of_range( "Invalid register number" );
	
	this->regs[reg_num] = data;
}

dword GPR::readReg( byte reg_num ) const {
	if ( reg_num < 0 || reg_num >= 32 )
		throw std::out_of_range( "Invalid register number" );

	return this->regs[reg_num];
}


CR::CR() {
	for ( int i = 0; i <= 3; ++i ) crs[i] = 0;
}

void CR::writeCtrlReg( byte reg_num, dword data ) {
	if ( reg_num < 0 || reg_num >= 3 )
		throw std::out_of_range( "Invalid register number" );

	this->crs[reg_num] = data;
}

dword CR::readCtrlReg( byte reg_num ) const {
	if ( reg_num < 0 || reg_num >= 3 )
		throw std::out_of_range( "Invalid register number" );

	return this->crs[reg_num];
}